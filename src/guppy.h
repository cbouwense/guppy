// See bottom for license information.

#ifndef GUPPY_H
#define GUPPY_H

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    size_t length;
    const char *data;
} GupStringView;

typedef struct {
    int   capacity;
    int   count;
    bool *data;
} GupArrayBool;

typedef struct {
    int   capacity;
    int   count;
    char *data;
} GupArrayChar;

typedef struct {
    int    capacity;
    int    count;
    float *data;
} GupArrayFloat;

typedef struct {
    int  capacity;
    int  count;
    int *data;
} GupArrayInt;

/**************************************************************************************************
 * Public API                                                                                     *
 **************************************************************************************************/

// Dynamic arrays ----------------------------------------------------------------------------------
GupArrayBool  *gup_array_bool();
void           gup_array_bool_append(GupArrayBool *xs, bool x);
bool           gup_array_bool_eq(GupArrayBool *xs, GupArrayBool *ys);
GupArrayBool  *gup_array_bool_from(const bool xs[], const int size);
void           gup_array_bool_prepend(GupArrayBool *xs, bool x);
void           gup_array_bool_print(GupArrayBool *xs);
int            gup_array_bool_remove_all(GupArrayBool *xs, bool x);
bool           gup_array_bool_remove_first(GupArrayBool *xs, bool x);
bool           gup_array_bool_remove_last(GupArrayBool *xs, bool x);

GupArrayChar  *gup_array_char();
void           gup_array_char_append(GupArrayChar *xs, char x);
bool           gup_array_char_eq(GupArrayChar *xs, GupArrayChar *ys);
GupArrayChar  *gup_array_char_from(const char xs[], const int size);
void           gup_array_char_prepend(GupArrayChar *xs, char x);
void           gup_array_char_print(GupArrayChar *xs);
int            gup_array_char_remove_all(GupArrayChar *xs, char x);
bool           gup_array_char_remove_first(GupArrayChar *xs, char x);
bool           gup_array_char_remove_last(GupArrayChar *xs, char x);

GupArrayFloat *gup_array_float();
void           gup_array_float_append(GupArrayFloat *xs, float x);
bool           gup_array_float_eq(GupArrayFloat *xs, GupArrayFloat *ys);
GupArrayFloat *gup_array_float_from(const float xs[], const int size);
void           gup_array_float_prepend(GupArrayFloat *xs, float x);
void           gup_array_float_print(GupArrayFloat *xs);
int            gup_array_float_remove_all(GupArrayFloat *xs, float x);
bool           gup_array_float_remove_first(GupArrayFloat *xs, float x);
bool           gup_array_float_remove_last(GupArrayFloat *xs, float x);

GupArrayInt *gup_array_int();
void         gup_array_int_append(GupArrayInt *xs, int i);
bool         gup_array_int_eq(GupArrayInt *xs, GupArrayInt *ys);
GupArrayInt *gup_array_int_from(const int xs[], const int size);
void         gup_array_int_prepend(GupArrayInt *xs, int i);
void         gup_array_int_print(GupArrayInt *xs);
int          gup_array_int_remove_all(GupArrayInt *xs, int x);
bool         gup_array_int_remove_first(GupArrayInt *xs, int x);
bool         gup_array_int_remove_last(GupArrayInt *xs, int x);

// Assert ------------------------------------------------------------------------------------------
void gup_assert(bool pass_condition, const char *failure_explanation);

// File operations ---------------------------------------------------------------------------------
bool   gup_file_create(const char *file_path);
bool   gup_file_delete(const char *file_path);
bool   gup_file_is_empty(const char *file_path);
int    gup_file_line_count(const char *file_path);
void   gup_file_print(const char *file_path);
void   gup_file_print_lines(const char *file_path);
char  *gup_file_read(const char *file_path);
char **gup_file_read_lines(const char *file_path);
char **gup_file_read_lines_keep_newlines(const char *file_path);
bool   gup_file_write(const char *text_to_write, const char *file_path);
bool   gup_file_write_lines(const char **lines_to_write, const int line_count, const char *file_path);

// Print -------------------------------------------------------------------------------------------
void gup_print_cwd(void);
void gup_print_string(const char *string);

// Print null terminated arrays --------------------------------------------------------------------
void gup_print_array_bool(bool array[]);
void gup_print_array_char(char array[]);
void gup_print_array_double(double array[]);
void gup_print_array_float(float array[]);
void gup_print_array_int(int array[]);
void gup_print_array_long(long array[]);
void gup_print_array_string(char *array[]);

// Print array slices [start, end) -----------------------------------------------------------------
void gup_print_array_slice_bool(bool array[], size_t start, size_t end);
void gup_print_array_slice_char(char array[], size_t start, size_t end);
void gup_print_array_slice_double(double array[], size_t start, size_t end);
void gup_print_array_slice_float(float array[], size_t start, size_t end);
void gup_print_array_slice_int(int array[], size_t start, size_t end);
void gup_print_array_slice_long(long array[], size_t start, size_t end);

// Settings ----------------------------------------------------------------------------------------
char *gup_settings_get(const char *key);
char *gup_settings_get_from_file(const char *key, const char *file_path);
int   gup_settings_get_int(const char *key);
bool  gup_settings_set(const char *key, const char *value);
bool  gup_settings_set_to_file(const char *key, const char *value, const char *file_path);
bool  gup_settings_set_int(const char *key, int value);

// String view -------------------------------------------------------------------------------------
GupStringView   gup_sv();
GupStringView   gup_sv_from_parts(const char *data, size_t count);
GupStringView   gup_sv_from_cstr(const char *cstr);
char           *gup_sv_to_cstr(GupStringView sv);
GupStringView   gup_sv_trim_left(GupStringView sv);
GupStringView   gup_sv_trim_right(GupStringView sv);
GupStringView   gup_sv_trim(GupStringView sv);
GupStringView   gup_sv_trim_char_left(GupStringView *sv, char c);
GupStringView   gup_sv_trim_char_right(GupStringView *sv, char c);
GupStringView   gup_sv_trim_char(GupStringView *sv, char c);
GupStringView   gup_sv_take_left_while(GupStringView sv, bool (*predicate)(char x));
GupStringView   gup_sv_chop_by_delim(GupStringView *sv, char delim);
GupStringView   gup_sv_chop_by_sv(GupStringView *sv, GupStringView thicc_delim);
bool            gup_sv_try_chop_by_delim(GupStringView *sv, char delim, GupStringView *chunk);
GupStringView   gup_sv_chop_left(GupStringView *sv, size_t n);
GupStringView   gup_sv_chop_right(GupStringView *sv, size_t n);
int             gup_sv_index_of(GupStringView sv, char c);
bool            gup_sv_eq(GupStringView a, GupStringView b);
bool            gup_sv_eq_ignorecase(GupStringView a, GupStringView b);
bool            gup_sv_eq_cstr(GupStringView sv, const char *cstr);
bool            gup_sv_starts_with(GupStringView sv, GupStringView prefix);
bool            gup_sv_ends_with(GupStringView sv, GupStringView suffix);
bool            gup_sv_is_empty(GupStringView sv);

// C-string utilities ------------------------------------------------------------------------------
char *gup_string_trim_double_quotes(const char *string);
char *gup_string_trim_whitespace(const char *string);
char *gup_string_without_whitespace(const char *string);
char *gup_string_array_flatten(char **strings);
char  gup_cstr_eq(const char *a, const char *b);

// Miscellaneous
double gup_operation_seconds(void (*fn)());

/**************************************************************************************************
 * Internal implementation                                                                        *
 **************************************************************************************************/

typedef unsigned int uint;
#define gup_defer_return(r) do { result = (r); goto defer; } while (0)

// Assert ------------------------------------------------------------------------------------------

void _gup_assert(bool pass_condition, const char *failure_explanation, const char *readable_pass_condition, const char *file_path, int line_number) {
    if (!pass_condition) {
        printf("[%s:%d] Failed assertion!\n", file_path, line_number);
        printf("---> %s <---\n", readable_pass_condition);
        printf("%s\n", failure_explanation);
        exit(1);
    }
}
#define gup_assert(pass_condition, failure_explanation) _gup_assert(pass_condition, failure_explanation, #pass_condition, __FILE__, __LINE__)

// Dynamic Arrays ----------------------------------------------------------------------------------

// Bool
GupArrayBool *gup_array_bool() {
    GupArrayBool *xs = malloc(sizeof(GupArrayBool));
    
    xs->capacity = 0;
    xs->count = 0;
    xs->data = NULL;

    return xs;
}

bool gup_array_bool_eq(GupArrayBool *xs, GupArrayBool *ys) {
    gup_assert(xs != NULL && ys != NULL, "Tried comparing two null `GupArrayBool`s.");
    gup_assert(xs != NULL || ys != NULL, "Tried comparing a null `GupArrayBool` with a defined one.");

    if (xs->count != ys->count) return false;
    
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

GupArrayBool *gup_array_bool_from(const bool xs[], const int size)  {
    GupArrayBool *bools = gup_array_bool();
    bools->data = malloc(size * sizeof(bool));

    bools->capacity = size;
    bools->count = size;
    for (int i = 0; i < size; i++) {
        bools->data[i] = xs[i];
    }

    return bools;
}

void gup_array_bool_append(GupArrayBool *xs, bool x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(bool));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_bool_prepend(GupArrayBool *xs, bool x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(bool));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

#define gup_array_bool_print(xs) _gup_array_bool_print(xs, #xs)
void _gup_array_bool_print(GupArrayBool *xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == true) printf("true");
        else printf("false");

        if (i != xs->count-1) printf(", ");
    }
    printf("]\n"); 
}

int gup_array_bool_remove_all(GupArrayBool *xs, bool x) {
    int remaining = 0;
    int original_count = xs->count;
    bool *new_xs_data = malloc(xs->count * sizeof(bool));

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != x) {
            new_xs_data[remaining] = xs->data[i];
            remaining++;
        }
    }

    free(xs->data);
    xs->data = new_xs_data;
    xs->data = realloc(xs->data, remaining * sizeof(bool));
    xs->capacity = remaining;
    xs->count = remaining;

    return original_count - remaining;
}

bool gup_array_bool_remove_first(GupArrayBool *xs, bool x) {
    bool found = false;

    for (int i = 0; i < xs->count; i++) {
        if (found) {
            xs->data[i] = xs->data[i+1];
            if (i == xs->count - 2) break;
        } else {
            if (xs->data[i] == x) {
                found = true;
            }
        }
    }

    if (found) {
        xs->count--;
        xs->capacity = xs->count;
        xs->data = realloc(xs->data, xs->capacity * sizeof(bool));
    }

    return found;
}

bool gup_array_bool_remove_last(GupArrayBool *xs, bool x) {
    bool found = false;

    for (int i = xs->count-1; i > 0; i--) {
        if (found) {
            xs->data[i] = xs->data[i-1];
            if (i == 1) break;
        } else {
            if (xs->data[i] == x) {
                found = true;
                xs->data[i] = xs->data[i-1];
            }
        }
    }

    if (found) {
        xs->count--;
        xs->capacity = xs->count;
        // If we found and removed an element, then we will need to move each
        // element of the array to the left. The first element will be garbage.
        // e.g. 
        // [1, 2, 3, 2, 4, 2, 5] (remove last 2) ->
        // [1, 1, 2, 3, 2, 4, 5] ->
        //    [1, 2, 3, 2, 4, 5]
        for (int i = 0; i < xs->count; i++) {
            xs->data[i] = xs->data[i+1];
        }
        xs->data = realloc(xs->data, xs->count * sizeof(bool));
    }

    return found;
}

// Char
GupArrayChar *gup_array_char() {
    GupArrayChar *xs = malloc(sizeof(GupArrayChar));
    
    xs->capacity = 0;
    xs->count = 0;
    xs->data = NULL;

    return xs;
}

bool gup_array_char_eq(GupArrayChar *xs, GupArrayChar *ys) {
    gup_assert(xs != NULL && ys != NULL, "Tried comparing two null `GupArrayChar`s.");
    gup_assert(xs != NULL || ys != NULL, "Tried comparing a null `GupArrayChar` with a defined one.");

    if (xs->count != ys->count) return false;
    
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

GupArrayChar *gup_array_char_from(const char xs[], const int size)  {
    GupArrayChar *chars = gup_array_char();
    chars->data = malloc(size * sizeof(char));

    chars->capacity = size;
    chars->count = size;
    for (int i = 0; i < size; i++) {
        chars->data[i] = xs[i];
    }

    return chars;
}

void gup_array_char_append(GupArrayChar *xs, char x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(char));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_char_prepend(GupArrayChar *xs, char x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(char));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

#define gup_array_char_print(xs) _gup_array_char_print(xs, #xs)
void _gup_array_char_print(GupArrayChar *xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
        printf("'%c'", xs->data[i]);
        if (i != xs->count-1) printf(", ");
    }
    printf("]\n"); 
}

int gup_array_char_remove_all(GupArrayChar *xs, char x) {
    int remaining = 0;
    int original_count = xs->count;
    char *new_xs_data = malloc(xs->count * sizeof(char));

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != x) {
            new_xs_data[remaining] = xs->data[i];
            remaining++;
        }
    }

    free(xs->data);
    xs->data = new_xs_data;
    xs->data = realloc(xs->data, remaining * sizeof(char));
    xs->capacity = remaining;
    xs->count = remaining;

    return original_count - remaining;
}

bool gup_array_char_remove_first(GupArrayChar *xs, char x) {
    bool found = false;

    for (int i = 0; i < xs->count; i++) {
        if (found) {
            xs->data[i] = xs->data[i+1];
            if (i == xs->count - 2) break;
        } else {
            if (xs->data[i] == x) {
                found = true;
            }
        }
    }

    if (found) {
        xs->count--;
        xs->capacity = xs->count;
        xs->data = realloc(xs->data, xs->capacity * sizeof(char));
    }

    return found;
}

bool gup_array_char_remove_last(GupArrayChar *xs, char x) {
    bool found = false;

    for (int i = xs->count-1; i > 0; i--) {
        if (found) {
            xs->data[i] = xs->data[i-1];
            if (i == 1) break;
        } else {
            if (xs->data[i] == x) {
                found = true;
                xs->data[i] = xs->data[i-1];
            }
        }
    }

    if (found) {
        xs->count--;
        xs->capacity = xs->count;
        // If we found and removed an element, then we will need to move each
        // element of the array to the left. The first element will be garbage.
        // e.g. 
        // [1, 2, 3, 2, 4, 2, 5] (remove last 2) ->
        // [1, 1, 2, 3, 2, 4, 5] ->
        //    [1, 2, 3, 2, 4, 5]
        for (int i = 0; i < xs->count; i++) {
            xs->data[i] = xs->data[i+1];
        }
        xs->data = realloc(xs->data, xs->count * sizeof(char));
    }

    return found;
}

// Float
GupArrayFloat *gup_array_float() {
    GupArrayFloat *xs = malloc(sizeof(GupArrayFloat));
    
    xs->capacity = 0;
    xs->count = 0;
    xs->data = NULL;

    return xs;
}

bool gup_array_float_eq(GupArrayFloat *xs, GupArrayFloat *ys) {
    gup_assert(xs != NULL && ys != NULL, "Tried comparing two null `GupArrayFloat`s.");
    gup_assert(xs != NULL || ys != NULL, "Tried comparing a null `GupArrayFloat` with a defined one.");

    if (xs->count != ys->count) return false;
    
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

GupArrayFloat *gup_array_float_from(const float xs[], const int size)  {
    GupArrayFloat *floats = gup_array_float();
    floats->data = malloc(size * sizeof(float));

    floats->capacity = size;
    floats->count = size;
    for (int i = 0; i < size; i++) {
        floats->data[i] = xs[i];
    }

    return floats;
}

void gup_array_float_append(GupArrayFloat *xs, float x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(float));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_float_prepend(GupArrayFloat *xs, float x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(float));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

#define gup_array_float_print(xs) _gup_array_float_print(xs, #xs)
void _gup_array_float_print(GupArrayFloat *xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
        printf("%f", xs->data[i]);
        if (i != xs->count-1) printf(", ");
    }
    printf("]\n"); 
}

int gup_array_float_remove_all(GupArrayFloat *xs, float x) {
    int remaining = 0;
    int original_count = xs->count;
    float *new_xs_data = malloc(xs->count * sizeof(float));

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != x) {
            new_xs_data[remaining] = xs->data[i];
            remaining++;
        }
    }

    free(xs->data);
    xs->data = new_xs_data;
    xs->data = realloc(xs->data, remaining * sizeof(float));
    xs->capacity = remaining;
    xs->count = remaining;

    return original_count - remaining;
}

bool gup_array_float_remove_first(GupArrayFloat *xs, float x) {
    bool found = false;

    for (int i = 0; i < xs->count; i++) {
        if (found) {
            xs->data[i] = xs->data[i+1];
            if (i == xs->count - 2) break;
        } else {
            if (xs->data[i] == x) {
                found = true;
            }
        }
    }

    if (found) {
        xs->count--;
        xs->capacity = xs->count;
        xs->data = realloc(xs->data, xs->capacity * sizeof(float));
    }

    return found;
}

bool gup_array_float_remove_last(GupArrayFloat *xs, float x) {
    bool found = false;

    for (int i = xs->count-1; i > 0; i--) {
        if (found) {
            xs->data[i] = xs->data[i-1];
            if (i == 1) break;
        } else {
            if (xs->data[i] == x) {
                found = true;
                xs->data[i] = xs->data[i-1];
            }
        }
    }

    if (found) {
        xs->count--;
        xs->capacity = xs->count;
        // If we found and removed an element, then we will need to move each
        // element of the array to the left. The first element will be garbage.
        // e.g. 
        // [1, 2, 3, 2, 4, 2, 5] (remove last 2) ->
        // [1, 1, 2, 3, 2, 4, 5] ->
        //    [1, 2, 3, 2, 4, 5]
        for (int i = 0; i < xs->count; i++) {
            xs->data[i] = xs->data[i+1];
        }
        xs->data = realloc(xs->data, xs->count * sizeof(float));
    }

    return found;
}

// Int
GupArrayInt *gup_array_int() {
    GupArrayInt *ints = malloc(sizeof(GupArrayInt));
    
    ints->capacity = 0;
    ints->count = 0;
    ints->data = NULL;

    return ints;
}

bool gup_array_int_eq(GupArrayInt *xs, GupArrayInt *ys) {
    gup_assert(xs != NULL && ys != NULL, "Tried comparing two null `GupArrayInt`s.");
    gup_assert(xs != NULL || ys != NULL, "Tried comparing a null `GupArrayInt` with a defined one.");

    if (xs->count != ys->count) return false;
    
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

GupArrayInt *gup_array_int_from(const int xs[], const int size)  {
    GupArrayInt *ints = malloc(sizeof(GupArrayInt));
    ints->data = malloc(size * sizeof(int));

    ints->capacity = size;
    ints->count = size;
    for (int i = 0; i < size; i++) {
        ints->data[i] = xs[i];
    }

    return ints;
}

void gup_array_int_append(GupArrayInt *xs, int x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(int));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_int_prepend(GupArrayInt *xs, int x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(int));
        xs->capacity = new_capacity;
    }

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

#define gup_array_int_print(xs) _gup_array_int_print(xs, #xs)
void _gup_array_int_print(GupArrayInt *xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
        printf("%d", xs->data[i]);
        if (i != xs->count-1) printf(", ");
    }
    printf("]\n"); 
}

int gup_array_int_remove_all(GupArrayInt *xs, int x) {
    int remaining = 0;
    int original_count = xs->count;
    int *new_xs_data = malloc(xs->count * sizeof(int));

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != x) {
            new_xs_data[remaining] = xs->data[i];
            remaining++;
        }
    }

    free(xs->data);
    xs->data = new_xs_data;
    xs->data = realloc(xs->data, remaining * sizeof(int));
    xs->capacity = remaining;
    xs->count = remaining;

    return original_count - remaining;
}

bool gup_array_int_remove_first(GupArrayInt *xs, int x) {
    bool found = false;

    for (int i = 0; i < xs->count; i++) {
        if (found) {
            xs->data[i] = xs->data[i+1];
            if (i == xs->count - 2) break;
        } else {
            if (xs->data[i] == x) {
                found = true;
            }
        }
    }

    if (found) {
        xs->count--;
        xs->capacity = xs->count;
        xs->data = realloc(xs->data, xs->capacity * sizeof(int));
    }

    return found;
}

bool gup_array_int_remove_last(GupArrayInt *xs, int x) {
    bool found = false;

    for (int i = xs->count-1; i > 0; i--) {
        if (found) {
            xs->data[i] = xs->data[i-1];
            if (i == 1) break;
        } else {
            if (xs->data[i] == x) {
                found = true;
                xs->data[i] = xs->data[i-1];
            }
        }
    }

    if (found) {
        xs->count--;
        xs->capacity = xs->count;
        // If we found and removed an element, then we will need to move each
        // element of the array to the left. The first element will be garbage.
        // e.g. 
        // [1, 2, 3, 2, 4, 2, 5] (remove last 2) ->
        // [1, 1, 2, 3, 2, 4, 5] ->
        //    [1, 2, 3, 2, 4, 5]
        for (int i = 0; i < xs->count; i++) {
            xs->data[i] = xs->data[i+1];
        }
        xs->data = realloc(xs->data, xs->count * sizeof(int));
    }

    return found;
}

// Memory ------------------------------------------------------------------------------------------

/*
 * Thanks to Eskil Steenberg for his explanation of using these custom memory macros for debugging.
 * Check out his masterclass on programming in C: https://youtu.be/443UNeGrFoM
 */

static long long      _gup_bytes_allocated = 0;
static GupArrayInt *_gup_allocation_sites = NULL;

void gup_memory_init(void) {
    _gup_allocation_sites = gup_array_int();
}

void gup_memory_print(void) {
    #ifdef GUPPY_DEBUG_MEMORY
        printf("\n============\n");
        printf("Memory usage:\n");
        for (int i = 0; i < _gup_allocation_sites->count; i++) {
            printf("%d, ", _gup_allocation_sites->data[i]);
        }
        printf("\n============\n");
    #else
        printf("GUPPY_DEBUG_MEMORY not enabled!\n");
    #endif // GUPPY_DEBUG_MEMORY
}

void _gup_free(void *ptr, const char *file_path, const int line_number) {
    if (ptr == NULL) {
        printf("[%s:%d] ", file_path, line_number);
        printf("Tried to free a null pointer\n");
        exit(1);
    }

    #ifdef GUPPY_VERBOSE
    printf("[%s:%d] Freed memory at %p\n", file_path, line_number, ptr);
    #endif

    free(ptr);
    
    // gup_array_int_remove(_gup_allocation_sites, line_number);
}

void *_gup_malloc(size_t bytes, const char *file_path, const int line_number) {
    void *ptr = malloc(bytes);

    if (ptr == NULL) {
        printf("[%s:%d] ", file_path, line_number);
        #ifdef GUPPY_VERBOSE
        printf("Failed to allocate %zu bytes\n", bytes);
        #endif // GUPPY_VERBOSE
        exit(1);
    }

    #ifdef GUPPY_VERBOSE
    printf("[%s:%d] Allocated %zu bytes at %p\n", file_path, line_number, bytes, ptr);
    #endif // GUPPY_VERBOSE

    _gup_bytes_allocated += bytes;
    // TODO: filepath : line number
    // char file_path_as_chars[] = gup_string 
    if (_gup_allocation_sites != NULL) {
        gup_array_int_append(_gup_allocation_sites, line_number);
    }

    return ptr;
}

#ifdef GUPPY_DEBUG_MEMORY

#define free(ptr) _gup_free(ptr, __FILE__, __LINE__)
#define malloc(bytes) _gup_malloc(bytes, __FILE__, __LINE__)

#endif // GUPPY_DEBUG_MEMORY


// File operations ---------------------------------------------------------------------------------

const char *GUP_DEFAULT_FILE_ERROR_MESSAGE = "File operation failed.\nYou should probably double check that you:\n1) spelled the file name correctly\n2) are creating the file in the directory you think you are\n3) have permissions to create a file in that directory\n";

bool gup_file_create(const char *file_path) {
    bool result = true;
    
    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        printf("Failed to create file %s\n", file_path);
        gup_defer_return(false);
    }

defer:
    fclose(fp);
    return result;
}

bool gup_file_delete(const char *file_path) {
    const bool result = remove(file_path);

    #ifdef GUPPY_VERBOSE
    if (!result) {    
        printf("Failed to delete file %s\n", file_path);
    }
    #endif // GUPPY_VERBOSE

    return result;
}

bool gup_file_is_empty(const char *file_path) {
    int line_count = gup_file_line_count(file_path);
    gup_assert(line_count != -1, "gup_file_line_count had an issue while opening the file.");

    return line_count == 0;
}

/*
 * This will basically tell you what number you would see in a text editor on the last line.
 * So, if you have a file with 5 lines, the line count will be 5.
 * If you have a file with 5 lines, but the last line is empty, the line count will be 6.
 * If you have an absolutely empty file, the line count will be 0.
 */
int gup_file_line_count(const char *file_path) {
    int c = 0;
    int line_count = 0;
    int result = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Error opening file %s\n", file_path);
        #endif

        return -1;
    }

    // If the very first character of the file is the end of the file, then we can say the line
    // count is 0.
    c = fgetc(fp);
    if (c == EOF) {
        #ifdef GUPPY_VERBOSE
        printf("The file you're trying to open (\"%s\") is empty\n", file_path);
        #endif

        gup_defer_return(0);
    }

    // If the first character is anything other than the end of the file, then we can say there is
    // at least one line in the file (even if it is a newline).
    line_count++;

    do {
        if (c == '\n') {
            line_count++;
        }
    } while ((c = fgetc(fp)) != EOF);
    gup_defer_return(line_count);

defer:
    fclose(fp);
    return result;
}

void gup_file_print(const char *file_path) {
    printf("[%s]\n", file_path);
    char **file_lines = gup_file_read_lines(file_path);
    if (file_lines == NULL) return;

    const int line_count = gup_file_line_count(file_path);
    for (int i = 0; i < line_count; i++) {
        if (file_lines[i] != NULL) {
            printf("%s\n", file_lines[i]);
            free(file_lines[i]);
        } else {
            // if there is an empty last line
            printf("\n");
        }
    }
}

void gup_file_print_lines(const char *file_path) {
     printf("[%s]\n", file_path);
    char **file_lines = gup_file_read_lines(file_path);
    if (file_lines == NULL) return;

    const int line_count = gup_file_line_count(file_path);
    for (int i = 0; i < line_count; i++) {
        if (file_lines[i] != NULL) { // 
            printf("%d %s\n", i+1, file_lines[i]);
            free(file_lines[i]);
        } else {
            // if there is an empty last line
            printf("%d", i+1);
        }
    }
    printf("\n");
}

// TODO: Do I actually just want to return a result code for each function?
// I should maybe research some other libraries to see what they do.
char *gup_file_read(const char *file_path) {
    char *result;
    char *buffer;
    size_t file_size;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        return NULL;
    }

    // TODO: This is not portable. Make a function.
    // Determine how many bytes are in the file.
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    buffer = (char*) malloc(file_size + 1);

    size_t bytes_read = fread(buffer, sizeof(char), file_size, fp);
    if (bytes_read != file_size) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to read file %s\n", file_path);
        #endif
        gup_defer_return(NULL);
    }
    buffer[file_size] = '\0';
    gup_defer_return(buffer);

defer:
    fclose(fp);
    return result;
}

char **gup_file_read_lines(const char *file_path) {
    char **result = NULL;
    char **lines = NULL;
    char *line = NULL;
    size_t line_size = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        
        gup_defer_return(NULL);
    }

    int line_count = gup_file_line_count(file_path);
    if (line_count == 0) {
        #ifdef GUPPY_VERBOSE
        printf("No lines found in file %s\n", file_path);
        #endif
        
        gup_defer_return(NULL);
    }

    lines = malloc(line_count * sizeof(char *));
    assert(lines != NULL);

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line, &line_size, fp);

        if (read == EOF) {
            lines[i] = NULL;
            gup_defer_return(lines);
        }

        // Only allocate the exact amount of memory needed for the line text excluding the newline.
        lines[i] = (char *) malloc(read * sizeof(char));
        strncpy(lines[i], line, read-1);
        lines[i][read-1] = '\0';
    }
    lines[line_count] = NULL;
    gup_defer_return(lines);

defer:
    free(line);
    if (fp) fclose(fp);

    return result;
}

char **gup_file_read_lines_keep_newlines(const char *file_path) {
    char **lines = NULL;
    char **result = NULL;
    char *line = NULL;
    size_t line_size = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif

        gup_defer_return(NULL);
    }

    int line_count = gup_file_line_count(file_path);
    if (line_count == 0) {
        #ifdef GUPPY_VERBOSE
        printf("No lines found in file %s\n", file_path);
        #endif
        
        gup_defer_return(NULL);
    }

    lines = malloc(line_count * sizeof(char *));
    assert(lines != NULL);

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line, &line_size, fp);

        if (read == EOF) {
            lines[i] = NULL;
            gup_defer_return(lines);
        }
        
        // Add an extra byte for null termination.
        lines[i] = (char *) malloc(read * sizeof(char) + 1);
        strcpy(lines[i], line);
    }
    lines[line_count] = NULL;
    gup_defer_return(lines);

defer:
    free(line);
    if (fp) fclose(fp);
    return result;
}

bool gup_file_write(const char *text_to_write, const char *file_path) {
    bool result = true;

    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        printf("Failed to open file %s\n", file_path);
        gup_defer_return(false);
    }

    fprintf(fp, "%s", text_to_write);

defer:
    fclose(fp);
    return result;
}

bool gup_file_write_lines(const char **lines_to_write, const int line_count, const char *file_path) {
    bool result = true;

    if (!gup_file_delete(file_path)) {
        return false;
    }
    
    FILE *fp = fopen(file_path, "a");
    if (fp == NULL) {
        printf("Failed to open file %s\n", file_path);
        gup_defer_return(false);
    }

    for (int i = 0; i < line_count; i++) {
        fputs(lines_to_write[i], fp);
        fputs("\n", fp);
    }

defer:
    fclose(fp);
    return result;
}

// Print -------------------------------------------------------------------------------------------

void gup_print_cwd(void) {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
}

void gup_print_string(const char *string) {
    printf("\"%s\"\n", string);
}

// Print null terminated arrays --------------------------------------------------------------------

void gup_print_array_bool(bool array[]) {
    printf("[");

    for (size_t i = 0; array[i] != '\0'; i++) {
        if (array[i] == true) {
            printf("true");
        } else {
            printf("false");
        }

        if (array[i+1] != '\0') {
            printf(", ");
        }
    }
    printf("]\n");
}

void gup_print_array_char(char array[]) {
    printf("[");

    for (size_t i = 0; array[i] != '\0'; i++) {
        switch (array[i]) {
            case '\n':
                printf("'\\n'");
                break;
            case '\t':
                printf("'\\t'");
                break;
            case '\r':
                printf("'\\r'");
                break;
            case '\v':
                printf("'\\v'");
                break;
            case '\b':
                printf("'\\b'");
                break;
            case '\f':
                printf("'\\f'");
                break;
            case '\a':
                printf("'\\a'");
                break;
            case '\\':
                printf("'\\\\'");
                break;
            case '\'':
                printf("'\\''");
                break;
            case '\"':
                printf("'\\\"'");
                break;
            default:
                printf("'%c'", array[i]);
                break;
        }
        
        if (array[i+1] != '\0') {
            printf(", ");
        }
    }
    printf("]\n");
}

void gup_print_array_double(double array[]) {
    printf("[");

    for (size_t i = 0; array[i] != '\0'; i++) {
        printf("%.17f", array[i]);
        if (array[i+1] != '\0') {
            printf(", ");
        }
    }
    printf("]\n");
}

void gup_print_array_float(float array[]) {
    printf("[");
    for (size_t i = 0; array[i] != '\0'; i++) {
        printf("%f", array[i]);
        if (array[i+1] != '\0') {
            printf(", ");
        }
    }
    printf("]\n");
}

void gup_print_array_int(int array[]) {
    printf("[");
    for (size_t i = 0; array[i] != '\0'; i++) {
        printf("%d", array[i]);
        if (array[i+1] != '\0') {
            printf(", ");
        }
    }
    printf("]\n");
}

void gup_print_array_long(long array[]) {
    printf("[");
    for (int i = 0; array[i] != '\0'; i++) {
        printf("%ld", array[i]);
        if (array[i+1] != '\0') {
            printf(", ");
        }
    }
    printf("]\n");
}

void gup_print_array_string(char *array[]) {
    gup_assert(array != NULL, "You tried to print an array of strings, but you sent in a null ptr.");
    
    printf("[");
    for (size_t i = 0; array[i] != NULL; i++) {
        printf("\"%s\"", array[i]);
        if (array[i+1] != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Print array slices ------------------------------------------------------------------------------

void gup_print_array_slice_bool(bool array[], size_t start, size_t end) {
    printf("[");
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

void gup_print_array_slice_char(char array[], size_t start, size_t end) {
    printf("[");
    for (size_t i = start; i < end; i++) {
        printf("'%c'", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void gup_print_array_slice_double(double array[], size_t start, size_t end) {
    printf("[");
    for (size_t i = start; i < end; i++) {
        printf("%.17f", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void gup_print_array_slice_float(float array[], size_t start, size_t end) {
    printf("[");
    for (size_t i = start; i < end; i++) {
        printf("%f", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void gup_print_array_slice_int(int array[], size_t start, size_t end) {
    printf("[");
    for (size_t i = start; i < end; i++) {
        printf("%d", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void gup_print_array_slice_long(long array[], size_t start, size_t end) {
    printf("[");
    for (size_t i = start; i < end; i++) {
        printf("%ld", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

// Settings ----------------------------------------------------------------------------------------

const char *GUP_DEFAULT_SETTINGS_FILE_PATH = "./resources/settings.toml";

bool _gup_does_setting_file_line_contain_key(GupStringView line, GupStringView key) {
    if (gup_sv_index_of(line, '#') != -1) return false; // Ignore comments.
    if (gup_sv_index_of(line, '[') != -1) return false; // Ignore section headers.

    GupStringView line_key;
    const bool line_has_an_equals_sign = gup_sv_try_chop_by_delim(&line, '=', &line_key);
    if (!line_has_an_equals_sign) return false; // Ignore lines without equals signs.
    
    return gup_sv_eq(gup_sv_trim(line_key), gup_sv_trim(key));
}

bool _gup_char_is_doublequote(char x) { return x == '"'; }

char *gup_settings_get(const char *key) {
    return gup_settings_get_from_file(key, GUP_DEFAULT_SETTINGS_FILE_PATH);
}

char *gup_settings_get_from_file(const char *key, const char *file_path) {
    char *result = NULL;
    
    int line_count = gup_file_line_count(file_path);
    gup_assert(line_count != -1, GUP_DEFAULT_FILE_ERROR_MESSAGE);
    gup_assert(line_count != 0, "The settings file is empty. You should probably add some settings to it.");

    char **settings_lines = gup_file_read_lines(file_path);
    gup_assert(settings_lines != NULL, GUP_DEFAULT_FILE_ERROR_MESSAGE);

    for (int i = 0; i < line_count; i++) {
        const char* line = settings_lines[i];
        if (_gup_does_setting_file_line_contain_key(gup_sv_from_cstr(line), gup_sv_from_cstr(key))) {
            GupStringView line = gup_sv_from_cstr(settings_lines[i]);

            gup_sv_chop_by_delim(&line, '='); // Chop off the key.

            GupStringView line_value = gup_sv_trim(line);

            line_value = gup_sv_trim_char(&line_value, '"');

            gup_defer_return(gup_sv_to_cstr(line_value));
        }
    }

    #ifdef GUPPY_VERBOSE
    printf("Failed to find key \"%s\" in settings file \"%s\"\n", key, file_path);
    #endif
    gup_defer_return(NULL);

defer:
    for (int i = 0; i < line_count; i++) {
        free(settings_lines[i]);
    }
    free(settings_lines);

    return result;
}

int gup_settings_get_int(const char *key) {
    char *value = gup_settings_get(key);
    if (value == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to get value for key \"%s\"\n", key);
        #endif
        return -1;
    }

    char *endptr = NULL;
    long result = strtol(value, &endptr, 10);
    if (*endptr != '\0') {
        printf("Invalid value for key \"%s\". Are you sure it's an int?\n.", key);
    }

    free(value);
    return (int) result;
}

bool gup_settings_set(const char *key, const char *value) {
    return gup_settings_set_to_file(key, value, GUP_DEFAULT_SETTINGS_FILE_PATH);
}

bool gup_settings_set_to_file(const char *key, const char *value, const char *file_path) {
    bool result = false;

    // Read the file into memory
    char **settings_lines = gup_file_read_lines_keep_newlines(file_path);
    gup_assert(settings_lines != NULL, GUP_DEFAULT_FILE_ERROR_MESSAGE);

    // TODO: This block of code is duplicated a couple times. Make a function.
    // Find the line with the key. If found, replace with the new key value pair.
    bool found = false;
    const int line_count = gup_file_line_count(file_path);
    for (int i = 0; i < line_count; i++) {
        // Find the line with the key.
        GupStringView line = gup_sv_from_cstr(settings_lines[i]);

        if (gup_sv_index_of(line, '#') != -1) continue; // Skip comments.
        if (gup_sv_index_of(line, '[') != -1) continue; // Skip section headers.

        GupStringView line_key;
        const bool line_has_an_equals_sign = gup_sv_try_chop_by_delim(&line, '=', &line_key);
        if (!line_has_an_equals_sign) continue; // Skip lines without an equals sign.
        
        line_key = gup_sv_trim(line_key);
        if (!gup_sv_eq(line_key, gup_sv_trim(gup_sv_from_cstr(key)))) continue; // Skip lines that don't match the key.

        // Replace the line with the key with the new value
        char *new_line = malloc(strlen(key) + strlen(value) + 3);
        sprintf(new_line, "%s = \"%s\"\n", key, value);

        free(settings_lines[i]);
        settings_lines[i] = new_line;
        found = true;
    }

    // If we didn't find the key, increase the memory allocated for the array and add the new key
    // value pair to the end.
    if (!found) {
        settings_lines = realloc(settings_lines, (line_count + 2) * sizeof(char *));

        char *new_line = malloc(strlen(key) + strlen(value) + 3);
        sprintf(new_line, "%s = \"%s\"\n", key, value);
        
        settings_lines[line_count-1] = new_line;
        settings_lines[line_count] = NULL;

        // Flatten the lines into a single string
        char *new_settings_text = gup_string_array_flatten(settings_lines);

        // Write to the file
        gup_file_write(new_settings_text, file_path);

        // free(new_line);
        free(new_settings_text);
        gup_defer_return(true);
    }

    // Flatten the lines into a single string
    char *settings_text = gup_string_array_flatten(settings_lines);

    // Write to the file
    gup_file_write(settings_text, file_path);
    
    free(settings_text);

defer:
    for (int i = 0; i < line_count + 2; i++) {
        free(settings_lines[i]);
    }
    free(settings_lines);

    return result;
}

// String view -------------------------------------------------------------------------------------

/*
 * This string view code is inspired by (aka, straight-up copied from) sv.h by Alexey Kutepov.
 * He uses the MIT license, so it's all good. Check out his repo here: https://github.com/tsoding/sv
 */

#define SV(cstr_lit) sv_from_parts(cstr_lit, sizeof(cstr_lit) - 1)
#define SV_STATIC(cstr_lit)   \
    {                         \
        sizeof(cstr_lit) - 1, \
        (cstr_lit)            \
    }

#define SV_NULL sv_from_parts(NULL, 0)

// printf macros for String_View
#define SV_Fmt "%.*s"
#define SV_Arg(sv) (int) (sv).length, (sv).data
/* 
 * USAGE:
 *   String_View name = ...;
 *   printf("Name: "SV_Fmt"\n", SV_Arg(name));
 */

GupStringView gup_sv() {
    GupStringView sv;
    sv.length = 0;
    sv.data = "";
    return sv;
}

GupStringView gup_sv_from_parts(const char *data, size_t count) {
    GupStringView sv;
    sv.length = count;
    sv.data = data;
    return sv;
}

GupStringView gup_sv_from_cstr(const char *cstr) {
    if (cstr == NULL) return gup_sv();
    
    return gup_sv_from_parts(cstr, strlen(cstr));
}

char *gup_sv_to_cstr(GupStringView sv) {
    char *cstr = malloc(sv.length + 1);
    memcpy(cstr, sv.data, sv.length);
    cstr[sv.length] = '\0';
    return cstr;
}

GupStringView gup_sv_trim_left(GupStringView sv) {
    size_t i = 0;
    while (i < sv.length && isspace(sv.data[i])) {
        i += 1;
    }

    return gup_sv_from_parts(sv.data + i, sv.length - i);
}

GupStringView gup_sv_trim_right(GupStringView sv) {
    size_t i = 0;
    while (i < sv.length && isspace(sv.data[sv.length - 1 - i])) {
        i += 1;
    }

    return gup_sv_from_parts(sv.data, sv.length - i);
}

GupStringView gup_sv_trim(GupStringView sv) {
    return gup_sv_trim_right(gup_sv_trim_left(sv));
}

GupStringView gup_sv_trim_char_left(GupStringView *sv, char c) {
    if (sv->length == 0) return *sv;
    
    size_t i = 0;
    // Increment i until we find a character that doesn't match the predicate.
    while (i < sv->length && sv->data[i] == c) i++;

    sv->data += i;
    sv->length -= i;
    return *sv;
}

GupStringView gup_sv_trim_char_right(GupStringView *sv, char c) {
    size_t i = sv->length;

    // Decrement i until we find a character that doesn't match the predicate.
    while (i > 0 && sv->data[i-1] == c) i--;

    sv->length = i;
    return *sv;
}

GupStringView gup_sv_trim_char(GupStringView *sv, char c) {
    *sv = gup_sv_trim_char_left(sv, c);
    *sv = gup_sv_trim_char_right(sv, c);

    return *sv;
}

GupStringView gup_sv_chop_left(GupStringView *sv, size_t n) {
    if (n > sv->length) {
        n = sv->length;
    }

    GupStringView result = gup_sv_from_parts(sv->data, n);

    sv->data  += n;
    sv->length -= n;

    return result;
}

GupStringView gup_sv_chop_right(GupStringView *sv, size_t n) {
    if (n > sv->length) {
        n = sv->length;
    }

    GupStringView result = gup_sv_from_parts(sv->data + sv->length - n, n);

    sv->length -= n;

    return result;
}

int gup_sv_index_of(GupStringView sv, char c) {
    int i = 0;
    while (i < (int)sv.length && sv.data[i] != c) {
        i += 1;
    }

    return i < (int)sv.length ? i : -1;
}

bool gup_sv_try_chop_by_delim(GupStringView *sv, char delim, GupStringView *chunk) {
    size_t i = 0;
    while (i < sv->length && sv->data[i] != delim) {
        i += 1;
    }

    GupStringView result = gup_sv_from_parts(sv->data, i);

    if (i < sv->length) {
        sv->length -= i + 1;
        sv->data  += i + 1;
        if (chunk) {
            *chunk = result;
        }
        return true;
    }

    return false;
}

GupStringView gup_sv_chop_by_delim(GupStringView *sv, char delim) {
    size_t i = 0;
    while (i < sv->length && sv->data[i] != delim) {
        i += 1;
    }

    GupStringView result = gup_sv_from_parts(sv->data, i);

    if (i < sv->length) {
        sv->length -= i + 1;
        sv->data  += i + 1;
    } else {
        sv->length -= i;
        sv->data  += i;
    }

    return result;
}

GupStringView gup_sv_chop_by_sv(GupStringView *sv, GupStringView thicc_delim) {
    GupStringView window = gup_sv_from_parts(sv->data, thicc_delim.length);
    size_t i = 0;
    while (i + thicc_delim.length < sv->length
        && !(gup_sv_eq(window, thicc_delim)))
    {
        i++;
        window.data++;
    }

    GupStringView result = gup_sv_from_parts(sv->data, i);

    if (i + thicc_delim.length == sv->length) {
        // include last <thicc_delim.length> characters if they aren't
        //  equal to thicc_delim
        result.length += thicc_delim.length;
    }

    // Chop!
    sv->data  += i + thicc_delim.length;
    sv->length -= i + thicc_delim.length;

    return result;
}

bool gup_sv_starts_with(GupStringView sv, GupStringView expected_prefix) {
    if (expected_prefix.length <= sv.length) {
        GupStringView actual_prefix = gup_sv_from_parts(sv.data, expected_prefix.length);
        return gup_sv_eq(expected_prefix, actual_prefix);
    }

    return false;
}

bool gup_sv_ends_with(GupStringView sv, GupStringView expected_suffix) {
    if (expected_suffix.length <= sv.length) {
        GupStringView actual_suffix = gup_sv_from_parts(sv.data + sv.length - expected_suffix.length, expected_suffix.length);
        return gup_sv_eq(expected_suffix, actual_suffix);
    }

    return false;
}

bool gup_sv_is_empty(GupStringView sv) {
    return sv.length == 0;
}

bool gup_sv_eq(GupStringView a, GupStringView b) {
    if (a.length != b.length) {
        return false;
    } else {
        return memcmp(a.data, b.data, a.length) == 0;
    }
}

bool gup_sv_eq_ignorecase(GupStringView a, GupStringView b) {
    if (a.length != b.length) {
        return false;
    }

    char x, y;
    for (size_t i = 0; i < a.length; i++) {
        x = 'A' <= a.data[i] && a.data[i] <= 'Z'
              ? a.data[i] + 32
              : a.data[i];

        y = 'A' <= b.data[i] && b.data[i] <= 'Z'
              ? b.data[i] + 32
              : b.data[i];

        if (x != y) return false;
    }
    return true;
}

bool gup_sv_eq_cstr(GupStringView sv, const char *cstr) {
    if (cstr == NULL) return false;

    return gup_sv_eq(sv, gup_sv_from_cstr(cstr));
}

GupStringView gup_sv_take_left_while(GupStringView sv, bool (*predicate)(char x)) {
    size_t i = 0;
    while (i < sv.length && predicate(sv.data[i])) {
        i += 1;
    }
    return gup_sv_from_parts(sv.data, i);
}

// C-string utilities ------------------------------------------------------------------------------

char *gup_string_trim_double_quotes(const char *string) {
    char *str = (char *) malloc(strlen(string) * sizeof(char));
    strcpy(str, string);

    size_t len = strlen(str);
    if (str[0] == '\"') {
        memmove(str, str + 1, len - 1);
        len--;
    }

    if (str[len - 1] == '\"') {
        len--;
        str[len] = '\0';
    }

    return str;
}

char *gup_string_trim_whitespace(const char *string) {
    char *str = (char *) malloc(strlen(string) * sizeof(char));
    strcpy(str, string);

    size_t len = strlen(str);
    size_t i = 0;
    while (i < len && isspace(str[i])) {
        i++;
    }
    memmove(str, str + i, len - i + 1);

    len = strlen(str);
    while (len > 0 && isspace(str[len - 1])) {
        len--;
        str[len] = '\0';
    }

    return str;
}

char *gup_string_without_whitespace(const char *string) {
    char *new_string = malloc(strlen(string) * sizeof(char));
    assert(new_string != NULL);

    int new_string_index = 0;
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (isspace(string[i])) continue;

        new_string[new_string_index] = string[i];
        new_string_index++;
    }

    new_string[new_string_index] = '\0';
    return new_string;
}

// Assumes a null terminated array of strings.
char *gup_string_array_flatten(char **strings) {
    // Calculate the total length of all the strings.
    int total_length = 0;
    for (int i = 0; strings[i] != NULL; i++) {
        total_length += strlen(strings[i]);
    }

    // Allocate a new buffer to hold the flattened string.
    char *result = malloc(total_length + 1);
    if (result == NULL) return NULL;

    // Copy each string into the buffer.
    int offset = 0;
    for (int i = 0; strings[i] != NULL; i++) {
        strcpy(result + offset, strings[i]);
        offset += strlen(strings[i]);
    }

    // Add a null terminator to the end of the buffer.
    result[total_length] = '\0';

    return result;
}

// I can't stand strcmp. Its API is exactly backwards as far as I'm concerned.
char gup_cstr_eq(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}


// Miscellaneous -----------------------------------------------------------------------------------

double gup_operation_seconds(void (*fn)()) {
    clock_t start, end;
    double cpu_seconds_used;

    start = clock();

    fn();

    end = clock();
    
    cpu_seconds_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    #ifdef GUPPY_VERBOSE
    printf("The operation took %f seconds to execute.\n", cpu_seconds_used);
    #endif // GUPPY_VERBOSE

    return cpu_seconds_used;
}

double gup_operation_seconds_verbose(void (*fn)()) {
    double result = gup_operation_seconds(fn);
    printf("The operation took %f seconds to execute.\n", result);

    return result;
}

#endif // GUPPY_H

// Copyright 2023 Christian Bouwense <cbouwense@proton.me>

// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
