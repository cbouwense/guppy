#ifndef GUPPY_H
#define GUPPY_H

#include <stdbool.h>
#include <stdio.h>

/*************************************************************************************************\
|* Public API                                                                                     |
\*************************************************************************************************/

void guppy_print_bool_array(bool array[], size_t length, const char* array_name);
void guppy_print_char_array(char array[], size_t length, const char* array_name);
void guppy_print_float_array(float array[], size_t length, const char* array_name);
void guppy_print_int_array(int array[], size_t length, const char* array_name);

/*************************************************************************************************\
|* Internal implementation                                                                        |
\*************************************************************************************************/

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

void guppy_print_int_array(int array[], size_t length, const char* array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%d", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

#endif // GUPPY_H
