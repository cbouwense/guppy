#include <stdio.h>
#include "../src/guppy.h"

int main(void) {
    printf("\n==========\n");
    printf("Guppy Test\n");
    printf("==========\n\n");

    bool bool_array[] = {true, false, true};
    printf("Expected: bool_array: [true, false, true]\n");
    printf("Actual:   ");
    guppy_print_bool_array(bool_array, 3, "bool_array");
    printf("\n");

    char char_array[] = {'a', 'b', 'c'};
    printf("Expected: char_array: [a, b, c]\n");
    printf("Actual:   ");
    guppy_print_char_array(char_array, 3, "char_array");
    printf("\n");

    double double_array[] = {0.00000000000000001, 654321, 0.123456789012345};
    printf("Expected: double_array: [0.00000000000000001, 654321.00000000000000000, 0.12345678901234500]\n");
    printf("Actual:   ");
    guppy_print_double_array(double_array, 3, "double_array");
    printf("\n");

    float float_array[] = {1.10001, 0.000002, 9999999};
    printf("Expected: float_array: [1.100010, 0.000002, 9999999.000000]\n");
    printf("Actual:   ");
    guppy_print_float_array(float_array, 3, "float_array");
    printf("\n");

    int int_array[] = {1, 2, 3};
    printf("Expected: int_array: [1, 2, 3]\n");
    printf("Actual:   ");
    guppy_print_int_array(int_array, 3, "int_array");
    printf("\n");

    return 0;
}
