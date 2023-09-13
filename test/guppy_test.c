#include <float.h>
#include <limits.h>
#include <stdio.h>
#include "../src/guppy.h"

int main(void) {
    bool bool_array[] = {true, false, true};

    printf("Expected: empty array: []\n");
    printf("Actual:   ");
    guppy_print_bool_array(bool_array, 0, "empty array");
    printf("\n");

    printf("Expected: normal boolean array: [true, false, true]\n");
    printf("Actual:   ");
    guppy_print_bool_array(bool_array, 3, "normal boolean array");
    printf("\n");

    char char_array[] = {'a', '1', '$'};
    printf("Expected: char_array: [a, 1, $]\n");
    printf("Actual:   ");
    guppy_print_char_array(char_array, 3, "char_array");
    printf("\n");

    double double_array[] = {DBL_MIN, DBL_EPSILON, 0.123456789012345};
    printf("Expected: double_array: [0.00000000000000000, 0.00000000000000022, 0.12345678901234500]\n");
    printf("Actual:   ");
    guppy_print_double_array(double_array, 3, "double_array");
    printf("\n");

    float float_array[] = {FLT_MIN, 17.380001, FLT_MAX};
    printf("Expected: float_array: [0.000000, 17.380001, 340282346638528859811704183484516925440.000000]\n");
    printf("Actual:   ");
    guppy_print_float_array(float_array, 3, "float_array");
    printf("\n");

    int int_array[] = {INT_MIN, 1, 7, 38, INT_MAX};
    printf("Expected: int_array: [-2147483648, 1, 7, 38, 2147483647]\n");
    printf("Actual:   ");
    guppy_print_int_array(int_array, 5, "int_array");
    printf("\n");

    // int long_array[] = {123412341234123412341234, 2, 3};

    return 0;
}
