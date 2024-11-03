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

void test_gup_cstr_eq(GupArena *a) {
    { // Stack allocated
        gup_assert(true == gup_cstr_eq("", ""));
        gup_assert(true == gup_cstr_eq("Hello", "Hello"));
        gup_assert(true == gup_cstr_eq("", "\0"));
        gup_assert(true == gup_cstr_eq("\0", "\0"));
        gup_assert(true == gup_cstr_eq("foo\0bar", "foo\0baz"));
        gup_assert(false == gup_cstr_eq("", "\n"));
        gup_assert(false == gup_cstr_eq("", " "));
        gup_assert(false == gup_cstr_eq("Hello", "World"));
    }
    
    { // Heap allocated
        { // Empty strings are equal.
            char *x = gup_arena_alloc(a, 1);
            char *y = gup_arena_alloc(a, 1);

            gup_cstr_copy(x, "\0");
            gup_cstr_copy(y, "\0");
            
            gup_assert(gup_cstr_eq(x, y));
        }

        { // Equivalent strings should be considered equal.
            char *x = gup_arena_alloc(a, 6);
            char *y = gup_arena_alloc(a, 6);

            gup_cstr_copy(x, "Hello");
            gup_cstr_copy(y, "Hello");
            
            gup_assert(gup_cstr_eq(x, y));
        }

        { // Different strings should not be considered equal.
            char *x = gup_arena_alloc(a, 6);
            char *y = gup_arena_alloc(a, 6);

            gup_cstr_copy(x, "Hello");
            gup_cstr_copy(y, "World");
            
            gup_assert(gup_cstr_eq(x, y) == false);
        }

        { // Different source strings, but the same slices are equal.
            char *x = gup_arena_alloc(a, 6);
            char *y = gup_arena_alloc(a, 6);

            gup_cstr_copy(x, "Hello");
            gup_cstr_copy_n(y, "Hello World", 5);

            gup_assert(gup_cstr_eq(x, y) == true);
        }
    }
}

void test_gup_cstr(void) {
    GupArena a = gup_arena_create();

    test_gup_cstr_array_flatten(&a);
    test_gup_cstr_length(&a);
    test_gup_cstr_eq(&a);

    gup_arena_destroy(&a);
}
