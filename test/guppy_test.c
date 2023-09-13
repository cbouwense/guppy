#include <stdio.h>
#include "../src/guppy.h"

int main(void) {
    bool bool_array[] = {true, false, true};
    printf("Expected: bool_array: [true, false, true]\n");
    printf("Actual:   ");
    guppy_print_bool_array(bool_array, 3, "bool_array");
    printf("\n");

    int int_array[] = {1, 2, 3};
    printf("Expected: int_array: [1, 2, 3]\n");
    printf("Actual:   ");
    guppy_print_int_array(int_array, 3, "int_array");
    printf("\n");

    char char_array[] = {'a', 'b', 'c'};
    printf("Expected: char_array: [a, b, c]\n");
    printf("Actual:   ");
    guppy_print_char_array(bool_array, 3, "char_array");
    printf("\n");

    return 0;
}
