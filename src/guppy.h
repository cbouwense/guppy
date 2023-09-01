#pragma once

#include <stdbool.h>
#include <stdio.h>

/***************************************************************************************************
 ** Public API
 ****************************************************************************************************/

#define guppy_print_bool_array(array) guppy_print_bool_array_internal(array, sizeof(array), #array)
#define guppy_print_char_array(array) guppy_print_char_array_internal(array, sizeof(array), #array)
#define guppy_print_int_array(array) guppy_print_int_array_internal(array, sizeof(array), #array)

/***************************************************************************************************
 ** Internal implementation
 ****************************************************************************************************/

void guppy_print_bool_array_internal(bool array[], size_t size_of_array, const char* array_name) {
    const size_t length = size_of_array / sizeof(bool);
    
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        if (array[i]) printf("true");
        else          printf("false");

        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_char_array_internal(char array[], size_t size_of_array, const char* array_name) {
    const size_t length = size_of_array / sizeof(char);
    
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%c", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_int_array_internal(int array[], size_t size_of_array, const char* array_name) {
    const size_t length = size_of_array / sizeof(int);
    
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%d", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}
