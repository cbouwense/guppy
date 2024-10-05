#include "../src/guppy.h"

void test_gup_string_creates_an_empty_string(void) {
    GupString str = gup_string_create();

    gup_assert(gup_string_eq_cstr(str, ""));

    gup_string_destroy(str);
}

void test_creating_a_gup_string_from_a_cstr_equals_that_cstr(void) {
    GupString str = gup_string_create_from_cstr("Hello World!");
    
    gup_assert(gup_string_eq_cstr(str, "Hello World!"));

    gup_string_destroy(str);
}

void test_gup_string_array_flatten(void) {
    { // Empty array
        char *array[] = {NULL};
        char *string = gup_string_array_flatten(array);

        assert(strcmp(string, "") == 0);

        free(string);
    }

    { // One element
        char *array[] = {"one", NULL};
        char *string = gup_string_array_flatten(array);

        assert(strcmp(string, "one") == 0);

        free(string);
    }

    { // Multiple elements
        char *array[] = {"one", "two", "three", NULL};
        char *string = gup_string_array_flatten(array);

        assert(strcmp(string, "onetwothree") == 0);

        free(string);
    }
}

void test_gup_string(void) {
    test_gup_string_creates_an_empty_string();
    test_creating_a_gup_string_from_a_cstr_equals_that_cstr();
    test_gup_string_array_flatten();
}
