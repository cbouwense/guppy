#ifndef GUPPY_H
#define GUPPY_H

#include <stdbool.h>
#include <stdio.h>

/**************************************************************************************************
 * Public API                                                                                     *
 **************************************************************************************************/

// Print full arrays -------------------------------------------------------------------------------
void guppy_print_bool_array(bool array[], size_t length, const char* array_name);
void guppy_print_char_array(char array[], size_t length, const char* array_name);
void guppy_print_double_array(double array[], size_t length, const char* array_name);
void guppy_print_float_array(float array[], size_t length, const char* array_name);
void guppy_print_int_array(int array[], size_t length, const char* array_name);
void guppy_print_long_array(long array[], size_t length, const char* array_name);

// Print array slices [start, end) -----------------------------------------------------------------
void guppy_print_bool_array_slice(bool array[], size_t start, size_t end, const char* array_name);
void guppy_print_char_array_slice(char array[], size_t start, size_t end, const char* array_name);
void guppy_print_double_array_slice(double array[], size_t start, size_t end, const char* array_name);
void guppy_print_float_array_slice(float array[], size_t start, size_t end, const char* array_name);
void guppy_print_int_array_slice(int array[], size_t start, size_t end, const char* array_name);
void guppy_print_long_array_slice(long array[], size_t start, size_t end, const char* array_name);



/**************************************************************************************************
 * Internal implementation                                                                        *
 **************************************************************************************************/

// TODO: DRY this up a bit perhaps. Most of this is duplication with different print formats.

// Print full arrays -------------------------------------------------------------------------------

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

// Print array slices ------------------------------------------------------------------------------

void guppy_print_bool_array_slice(bool array[], size_t start, size_t end, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = start; i < end; i++) {
        if (array[i] == true) {
            printf("true");
        } else {
            printf("false");
        }

        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_char_array_slice(char array[], size_t start, size_t end, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = start; i < end; i++) {
        printf("%c", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_double_array_slice(double array[], size_t start, size_t end, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = start; i < end; i++) {
        printf("%.17f", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_float_array_slice(float array[], size_t start, size_t end, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = start; i < end; i++) {
        printf("%f", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_int_array_slice(int array[], size_t start, size_t end, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = start; i < end; i++) {
        printf("%d", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_long_array_slice(long array[], size_t start, size_t end, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = start; i < end; i++) {
        printf("%ld", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

#endif // GUPPY_H
