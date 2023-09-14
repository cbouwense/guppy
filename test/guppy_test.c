#include <float.h>
#include <limits.h>
#include <stdio.h>
#include "../src/guppy.h"

int main(void) {
    char *file_contents = guppy_file_read("./test/foo.txt");
    assert(file_contents != NULL);
    printf("file contents:\n%s\n", file_contents);

    return 0;
}

/*
int main(void) {
    bool bool_array[] = {true, false, true};
    char char_array[] = {'a', '1', '$'};
    double double_array[] = {DBL_MIN, DBL_EPSILON, 0.123456789012345};
    float float_array[] = {FLT_MIN, 17.380001, FLT_MAX};
    int int_array[] = {INT_MIN, 1, 7, 38, INT_MAX};
    long long_array[] = {LONG_MIN, 1, 7, 38, LONG_MAX};

    // Print entire arrays

    printf("Expected: empty array: []\n");
    printf("Actual:   ");
    guppy_print_bool_array(bool_array, 0, "empty array");
    printf("\n");

    printf("Expected: normal boolean array: [true, false, true]\n");
    printf("Actual:   ");
    guppy_print_bool_array(bool_array, 3, "normal boolean array");
    printf("\n");

    printf("Expected: char_array: [a, 1, $]\n");
    printf("Actual:   ");
    guppy_print_char_array(char_array, 3, "char_array");
    printf("\n");
    
    printf("Expected: double_array: [0.00000000000000000, 0.00000000000000022, 0.12345678901234500]\n");
    printf("Actual:   ");
    guppy_print_double_array(double_array, 3, "double_array");
    printf("\n");
    
    printf("Expected: float_array: [0.000000, 17.380001, 340282346638528859811704183484516925440.000000]\n");
    printf("Actual:   ");
    guppy_print_float_array(float_array, 3, "float_array");
    printf("\n");

    printf("Expected: int_array: [-2147483648, 1, 7, 38, 2147483647]\n");
    printf("Actual:   ");
    guppy_print_int_array(int_array, 5, "int_array");
    printf("\n");

    printf("Expected: long_array: [-9223372036854775808, 1, 7, 38, 9223372036854775807]\n");
    printf("Actual:   ");
    guppy_print_long_array(long_array, 5, "long_array");
    printf("\n");

    // Print array slices

    printf("Expected: empty array: []\n");
    printf("Actual:   ");
    guppy_print_bool_array_slice(bool_array, 0, 0, "empty array");
    printf("\n");

    printf("Expected: normal boolean array: [false, true]\n");
    printf("Actual:   ");
    guppy_print_bool_array_slice(bool_array, 1, 3, "normal boolean array");
    printf("\n");

    printf("Expected: out of bounds boolean array: []\n");
    printf("Actual:   ");
    guppy_print_bool_array_slice(bool_array, 3, 3, "out of bounds boolean array");
    printf("\n");

    return 0;
}
*/