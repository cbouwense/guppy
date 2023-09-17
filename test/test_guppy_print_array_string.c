#include "../src/guppy.h"

void test_gup_print_array_string() {
    char **array_null = NULL;
    gup_print_array_string(array_null);

    char *array_empty[] = {NULL, NULL, NULL};
    gup_print_array_string(array_empty);

    char *array[] = {"Hello", "World", "!", NULL};
    gup_print_array_string(array);

    char *array_cut_short[] = {"Hello", "World", "!", NULL, "Hello", "World", "!"};
    gup_print_array_string(array_cut_short);
}
