#include "../src/guppy.h"

// I'm not really bothering to spy on the output of stdout or whatever, I'm just going to actually
// look at the output and make sure it looks right.
void test_gup_print_array_string() {
    char *array_empty[] = {NULL, NULL, NULL};
    gup_print_array_string(array_empty);

    char *array[] = {"Hello", "World", "!", NULL};
    gup_print_array_string(array);

    char *array_cut_short[] = {"Hello", "World", "!", NULL, "Hello", "World", "!"};
    gup_print_array_string(array_cut_short);
}
