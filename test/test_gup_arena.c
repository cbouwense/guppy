#include "../src/guppy.h"

void test_gup_arena_create(void) {
    GupArena a = gup_arena_create();

    assert(a.capacity == 256);
    assert(a.count == 0);
    assert(a.data != NULL);

    gup_arena_destroy(a);
}

// The real test here is that AddressSanitzer doesn't say there's a leak
// when this is run.
void test_gup_arena_can_allocate_stuff_and_not_need_to_free_it(void) {
    GupArena a = gup_arena_create();

    char *foo = gup_arena_alloc(&a, strlen("foo") + 1);
    char *bar = gup_arena_alloc(&a, strlen("bar") + 1);
    char *foobar = gup_arena_alloc(&a, strlen("foo") + strlen("bar") + 1);
    
    strcpy(foo, "foo");
    strcpy(bar, "bar");
    strcpy(foobar, foo);
    strcat(foobar, bar);
    
    // Make sure that room was actually allocated properly for these.
    assert(strcmp(foo, "foo") == 0);
    assert(strcmp(bar, "bar") == 0);
    assert(strcmp(foobar, "foobar") == 0);

    gup_arena_destroy(a);
}

// The real test here is that AddressSanitzer doesn't say there's a leak
// when this is run.
void test_gup_arena_can_be_freed_and_not_leak_memory(void) {
    GupArena a = gup_arena_create();

    const int count = 9001;
    int **lots_of_ints = gup_arena_alloc(&a, sizeof(int *) * count);
    for (int i = 0; i < count; i++) {
        lots_of_ints[i] = gup_arena_alloc(&a, sizeof(int));
        *lots_of_ints[i] = i;
    }

    gup_arena_free(a);
    free(a.data);
}

void test_gup_arena(void) {
    test_gup_arena_create();
    test_gup_arena_can_allocate_stuff_and_not_need_to_free_it();
    test_gup_arena_can_be_freed_and_not_leak_memory();
}
