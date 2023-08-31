#pragma once

#include <stdbool.h>
#include <stdio.h>

//--------------------------------------------------------------------------------------------------
// Macros
//--------------------------------------------------------------------------------------------------

#define guppy_print_bool_array(array) guppy_print_bool_array_internal(array, sizeof(array), #array)
#define guppy_print_char_array(array) guppy_print_char_array_internal(array, sizeof(array), #array)
#define guppy_print_int_array(array) guppy_print_int_array_internal(array, sizeof(array), #array)

//--------------------------------------------------------------------------------------------------
// Internal functions
//--------------------------------------------------------------------------------------------------

void guppy_print_bool_array_internal(bool array[], size_t length, const char* array_name);
void guppy_print_char_array_internal(char array[], size_t length, const char* array_name);
void guppy_print_int_array_internal(int array[], size_t length, const char* array_name);
