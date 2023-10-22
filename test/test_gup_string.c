#include "../src/guppy.h"

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
    test_gup_string_array_flatten();
}