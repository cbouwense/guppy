#include "../src/guppy.h"

void test_gup_arena_create(void) {
    GupArena a = gup_arena_create();

    gup_assert(a.capacity == 256);
    gup_assert(a.count == 0);
    gup_assert(a.data != NULL);

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
    gup_assert(strcmp(foo, "foo") == 0);
    gup_assert(strcmp(bar, "bar") == 0);
    gup_assert(strcmp(foobar, "foobar") == 0);

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

void test_gup_arena_can_allocate_a_bunch_of_strings(void) {
    GupArena a = gup_arena_create();

    GupString str = gup_string_create_from_cstr_arena(&a, "foo");
    gup_string_append(&str, 'b');
    gup_string_append(&str, 'a');
    gup_string_append(&str, 'r');

    gup_arena_destroy(a);
}

// The file stuff was like spewing leaks so I put this test here
void test_gup_arena_with_file_stuff(void) {
    GupArena a = gup_arena_create();

    GupArrayString tokens;
    const char *key = "foo";
    GupArrayString file_lines = gup_file_read_lines_arena(&a, "./src/settings.txt");

    for (int i = 0; i < file_lines.count; i++) {
        GupString line = file_lines.data[i];
        tokens = gup_string_split_arena(&a, line, '=');

        // If we have two tokens, we define that as a key-value pair.
        if (tokens.count == 2) {
            GupString line_key = tokens.data[0];
            GupString line_value = tokens.data[1];

            if (gup_string_eq_cstr(line_key, key)) {
                gup_string_copy_arena(&a, line_value);
            }
        }
    }
    
    gup_arena_destroy(a);
}

void test_gup_arena(void) {
    test_gup_arena_create();
    test_gup_arena_can_allocate_stuff_and_not_need_to_free_it();
    test_gup_arena_can_be_freed_and_not_leak_memory();
    test_gup_arena_can_allocate_a_bunch_of_strings();
    test_gup_arena_with_file_stuff();
}
