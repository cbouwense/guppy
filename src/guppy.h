#ifndef GUPPY_H
#define GUPPY_H

#include <stdbool.h>
#include <stdio.h>

/*************************************************************************************************\
|* Public API                                                                                     |
\*************************************************************************************************/

void guppy_print_bool_array(bool array[], size_t length, const char* array_name);
void guppy_print_char_array(char array[], size_t length, const char* array_name);
void guppy_print_double_array(double array[], size_t length, const char* array_name);
void guppy_print_float_array(float array[], size_t length, const char* array_name);
void guppy_print_int_array(int array[], size_t length, const char* array_name);
void guppy_print_long_array(long array[], size_t length, const char* array_name);

/*************************************************************************************************\
|* Internal implementation                                                                        |
\*************************************************************************************************/

/*
 * TODO:
 * 1) Slices of arrays.
 * 2) Print arrays of arrays.
 * 3) Print arrays of structs.
 * 4) DRY this up a bit perhaps. Most of this is duplication with different print formats.
 */
void guppy_print_bool_array(bool array[], size_t length, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        if (array[i] == true) {
            printf("true");
        } else {
            printf("false");
        }

        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_char_array(char array[], size_t length, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%c", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_double_array(double array[], size_t length, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%.17f", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_float_array(float array[], size_t length, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%f", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_int_array(int array[], size_t length, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%d", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_long_array(long array[], size_t length, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%ld", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

#endif // GUPPY_H
