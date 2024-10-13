#include "../src/guppy.h"

void test_gup_cstr_array_flatten(GupArena *a) {
    { // Empty array
        char *array[] = {NULL};
        char *string = gup_cstr_array_flatten_arena(a, array);

        gup_assert(strcmp(string, "") == 0);
    }

    { // One element
        char *array[] = {"one", NULL};
        char *string = gup_cstr_array_flatten_arena(a, array);

        gup_assert(strcmp(string, "one") == 0);
    }

    { // Multiple elements
        char *array[] = {"one", "two", "three", NULL};
        char *string = gup_cstr_array_flatten_arena(a, array);

        gup_assert(strcmp(string, "onetwothree") == 0);
    }
}

void test_gup_cstr_length(GupArena *a) {
    { // Stack allocated cstrs
        gup_assert(gup_cstr_length("") == 0);
        gup_assert(gup_cstr_length("a") == 1);
        gup_assert(gup_cstr_length("Hello, World!") == 13);
    }

    {
        char *empty_heap_cstr = gup_arena_alloc(a, 1);
        empty_heap_cstr[0] = '\0';
        gup_assert(gup_cstr_length(empty_heap_cstr) == 0);

        char *heap_str = gup_arena_alloc(a, 5 * sizeof(char));
        heap_str[0] = 'a';
        heap_str[1] = 'b';
        heap_str[2] = 'c';
        heap_str[3] = 'd';
        heap_str[4] = '\0';
        gup_assert(gup_cstr_length(heap_str) == 4);
    }
}

void test_gup_cstr(void) {
    GupArena a = gup_arena_create();

    test_gup_cstr_array_flatten(&a);
    test_gup_cstr_length(&a);

    gup_arena_destroy(a);
}
