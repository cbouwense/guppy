#ifndef GUPPY_H_
#define GUPPY_H_

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    const char *data;
    size_t length;
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

typedef GupArrayChar GupString;

typedef struct {
    int     capacity;
    int     count;
    double *data;
} GupArrayDouble;

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

typedef struct {
    int   capacity;
    int   count;
    long *data;
} GupArrayLong;

typedef struct {
    int    capacity;
    int    count;
    short *data;
} GupArrayShort;

typedef struct {
    int capacity;
    int count;
    GupArrayChar *data;
} GupArrayString;

typedef struct {
    int capacity;
    int count;
    void **data;
} GupArrayPtr;

typedef GupArrayPtr GupArena;

/**************************************************************************************************
 * Public API                                                                                     *
 **************************************************************************************************/

// Arena -------------------------------------------------------------------------------------------
GupArena  gup_arena_create();
void      gup_arena_destroy(GupArena a); // Free all the allocated memory and the arena itself
void     *gup_arena_alloc(GupArena *a, size_t bytes);
void      gup_arena_free(GupArena a); // Free all the allocated memory, but not the arena itself

// Dynamic arrays ----------------------------------------------------------------------------------
GupArrayBool   gup_array_bool();
void           gup_array_bool_free(GupArrayBool xs);
GupArrayBool   gup_array_bool_from(bool xs[], const int size);
GupArrayBool   gup_array_bool_copy(GupArrayBool xs);
bool           gup_array_bool_eq(GupArrayBool xs, GupArrayBool ys);
void           gup_array_bool_print(GupArrayBool xs);
void           gup_array_bool_append(GupArrayBool *xs, bool x);
void           gup_array_bool_prepend(GupArrayBool *xs, bool x);
GupArrayBool   gup_array_bool_map(GupArrayBool xs, bool (*fn)(bool));
void           gup_array_bool_map_in_place(GupArrayBool xs, bool (*fn)(bool));
GupArrayBool   gup_array_bool_filter(GupArrayBool xs, bool (*fn)(bool));
void           gup_array_bool_filter_in_place(GupArrayBool *xs, bool (*fn)(bool));
bool           gup_array_bool_reduce(GupArrayBool xs, bool (*fn)(bool, bool), bool start);
   
GupArrayChar   gup_array_char();
void           gup_array_char_free(GupArrayChar xs);
GupArrayChar   gup_array_char_from(char xs[], const int size);
GupArrayChar   gup_array_char_copy(GupArrayChar xs);
bool           gup_array_char_eq(GupArrayChar xs, GupArrayChar ys);
bool           gup_array_char_eq_cstr(GupArrayChar xs, const char *cstr, int cstr_length);
void           gup_array_char_print(GupArrayChar xs);
void           gup_array_char_append(GupArrayChar *xs, char x);
void           gup_array_char_prepend(GupArrayChar *xs, char x);
GupArrayChar   gup_array_char_map(GupArrayChar xs, char (*fn)(char));
void           gup_array_char_map_in_place(GupArrayChar xs, char (*fn)(char));
GupArrayChar   gup_array_char_filter(GupArrayChar xs, bool (*fn)(char));
void           gup_array_char_filter_in_place(GupArrayChar *xs, bool (*fn)(char));
char           gup_array_char_reduce(GupArrayChar xs, char (*fn)(char, char), char start);
   
GupArrayDouble gup_array_double();
void           gup_array_double_free(GupArrayDouble xs);
GupArrayDouble gup_array_double_from(double xs[], const int size);
GupArrayDouble gup_array_double_copy(GupArrayDouble xs);
bool           gup_array_double_eq(GupArrayDouble xs, GupArrayDouble ys);
void           gup_array_double_print(GupArrayDouble xs);
void           gup_array_double_append(GupArrayDouble *xs, double x);
void           gup_array_double_prepend(GupArrayDouble *xs, double x);
GupArrayDouble gup_array_double_map(GupArrayDouble xs, double (*fn)(double));
void           gup_array_double_map_in_place(GupArrayDouble xs, double (*fn)(double));
GupArrayDouble gup_array_double_filter(GupArrayDouble xs, bool (*fn)(double));
void           gup_array_double_filter_in_place(GupArrayDouble *xs, bool (*fn)(double));
double         gup_array_double_reduce(GupArrayDouble xs, double (*fn)(double, double), double start);
   
GupArrayFloat  gup_array_float();
void           gup_array_float_free(GupArrayFloat xs);
GupArrayFloat  gup_array_float_from(float xs[], const int size);
GupArrayFloat  gup_array_float_copy(GupArrayFloat xs);
bool           gup_array_float_eq(GupArrayFloat xs, GupArrayFloat ys);
void           gup_array_float_print(GupArrayFloat xs);
void           gup_array_float_append(GupArrayFloat *xs, float x);
void           gup_array_float_prepend(GupArrayFloat *xs, float x);
GupArrayFloat  gup_array_float_map(GupArrayFloat xs, float (*fn)(float));
void           gup_array_float_map_in_place(GupArrayFloat xs, float (*fn)(float));
GupArrayFloat  gup_array_float_filter(GupArrayFloat xs, bool (*fn)(float));
void           gup_array_float_filter_in_place(GupArrayFloat *xs, bool (*fn)(float));
float          gup_array_float_reduce(GupArrayFloat xs, float (*fn)(float, float), float start);

GupArrayInt    gup_array_int();
void           gup_array_int_free(GupArrayInt xs);
GupArrayInt    gup_array_int_from(int xs[], const int size);
GupArrayInt    gup_array_int_copy(GupArrayInt xs);
bool           gup_array_int_eq(GupArrayInt xs, GupArrayInt ys);
void           gup_array_int_print(GupArrayInt xs);
void           gup_array_int_append(GupArrayInt *xs, int x);
void           gup_array_int_prepend(GupArrayInt *xs, int x);
GupArrayInt    gup_array_int_map(GupArrayInt xs, int (*fn)(int));
void           gup_array_int_map_in_place(GupArrayInt xs, int (*fn)(int));
GupArrayInt    gup_array_int_filter(GupArrayInt xs, bool (*fn)(int));
void           gup_array_int_filter_in_place(GupArrayInt *xs, bool (*fn)(int));
int            gup_array_int_reduce(GupArrayInt xs, int (*fn)(int, int), int start);

GupArrayLong   gup_array_long();
void           gup_array_short_free(GupArrayShort xs);
GupArrayLong   gup_array_long_from(long xs[], const int size);
GupArrayLong   gup_array_long_copy(GupArrayLong xs);
bool           gup_array_long_eq(GupArrayLong xs, GupArrayLong ys);
void           gup_array_long_print(GupArrayLong xs);
void           gup_array_long_append(GupArrayLong *xs, long x);
void           gup_array_long_prepend(GupArrayLong *xs, long x);
GupArrayLong   gup_array_long_map(GupArrayLong xs, long (*fn)(long));
void           gup_array_long_map_in_place(GupArrayLong xs, long (*fn)(long));
GupArrayLong   gup_array_long_filter(GupArrayLong xs, bool (*fn)(long));
void           gup_array_long_filter_in_place(GupArrayLong *xs, bool (*fn)(long));
long           gup_array_long_reduce(GupArrayLong xs, long (*fn)(long, long), long start);

GupArrayPtr    gup_array_ptr();
void           gup_array_short_free(GupArrayShort xs);
GupArrayPtr    gup_array_ptr_from(void* xs[], const int size);
GupArrayPtr    gup_array_ptr_copy(GupArrayPtr xs);
bool           gup_array_ptr_eq(GupArrayPtr xs, GupArrayPtr ys);
void           gup_array_ptr_print(GupArrayPtr xs);
void           gup_array_ptr_append(GupArrayPtr *xs, void* x);
void           gup_array_ptr_prepend(GupArrayPtr *xs, void* x);
GupArrayPtr    gup_array_ptr_map(GupArrayPtr xs, void* (*fn)(void*));
void           gup_array_ptr_map_in_place(GupArrayPtr xs, void* (*fn)(void*));
GupArrayPtr    gup_array_ptr_filter(GupArrayPtr xs, bool (*fn)(void*));
void           gup_array_ptr_filter_in_place(GupArrayPtr *xs, bool (*fn)(void*));
void*          gup_array_ptr_reduce(GupArrayPtr xs, void* (*fn)(void*, void*), void* start);

GupArrayShort  gup_array_short();
void           gup_array_short_free(GupArrayShort xs);
GupArrayShort  gup_array_short_from(short xs[], const int size);
GupArrayShort  gup_array_short_copy(GupArrayShort xs);
bool           gup_array_short_eq(GupArrayShort xs, GupArrayShort ys);
void           gup_array_short_print(GupArrayShort xs);
void           gup_array_short_append(GupArrayShort *xs, short x);
void           gup_array_short_prepend(GupArrayShort *xs, short x);
GupArrayShort  gup_array_short_map(GupArrayShort xs, short (*fn)(short));
void           gup_array_short_map_in_place(GupArrayShort xs, short (*fn)(short));
GupArrayShort  gup_array_short_filter(GupArrayShort xs, bool (*fn)(short));
void           gup_array_short_filter_in_place(GupArrayShort *xs, bool (*fn)(short));
short          gup_array_short_reduce(GupArrayShort xs, short (*fn)(short, short), short start);

GupArrayString gup_array_string();
void           gup_array_string_free(GupArrayString xs);
GupArrayString gup_array_string_from(GupArrayChar xs[], const int size);
GupArrayString gup_array_string_copy(GupArrayString xs);
bool           gup_array_string_eq(GupArrayString xs, GupArrayString ys);
void           gup_array_string_print(GupArrayString xs);
void           gup_array_string_append(GupArrayString *xs, GupArrayChar x);
void           gup_array_string_prepend(GupArrayString *xs, GupArrayChar x);
GupArrayString gup_array_string_map(GupArrayString xs, GupArrayChar (*fn)(GupArrayChar));
void           gup_array_string_map_in_place(GupArrayString xs, GupArrayChar (*fn)(GupArrayChar));
GupArrayString gup_array_string_filter(GupArrayString xs, bool (*fn)(GupArrayChar));
void           gup_array_string_filter_in_place(GupArrayString *xs, bool (*fn)(GupArrayChar));
GupArrayChar   gup_array_string_reduce(GupArrayString xs, GupArrayChar (*fn)(GupArrayChar, GupArrayChar), GupArrayChar start);

// Assert ------------------------------------------------------------------------------------------
void gup_assert(bool pass_condition, const char *failure_explanation);

// File operations ---------------------------------------------------------------------------------
bool           gup_file_create(const char *file_path);
bool           gup_file_delete(const char *file_path);
bool           gup_file_is_empty(const char *file_path);
int            gup_file_line_count(const char *file_path);
void           gup_file_print(const char *file_path);
void           gup_file_print_lines(const char *file_path);
GupString      gup_file_read(const char *file_path);
char *         gup_file_read_as_cstr(const char *file_path);
GupArrayString gup_file_read_lines(const char *file_path);
char **        gup_file_read_lines_as_cstrs(const char *file_path);
GupArrayString gup_file_read_lines_keep_newlines(const char *file_path);
char **        gup_file_read_lines_as_cstrs_keep_newlines(const char *file_path);
long           gup_file_size(const char *file_path);
bool           gup_file_write(const char *text_to_write, const char *file_path);
bool           gup_file_write_lines(const char **lines_to_write, const int line_count, const char *file_path);

// Print -------------------------------------------------------------------------------------------
void gup_print_cwd(void);
void gup_print_string(const char *string);

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
GupStringView  gup_sv();
GupStringView  gup_sv_from_parts(const char *data, size_t count);
GupStringView  gup_sv_from_cstr(const char *cstr);
char          *gup_sv_to_cstr(GupStringView sv);
GupStringView  gup_sv_trim_left(GupStringView sv);
GupStringView  gup_sv_trim_right(GupStringView sv);
GupStringView  gup_sv_trim(GupStringView sv);
GupStringView  gup_sv_trim_char_left(GupStringView *sv, char c);
GupStringView  gup_sv_trim_char_right(GupStringView *sv, char c);
GupStringView  gup_sv_trim_char(GupStringView *sv, char c);
GupStringView  gup_sv_take_left_while(GupStringView sv, bool (*predicate)(char x));
GupStringView  gup_sv_chop_by_delim(GupStringView *sv, char delim);
GupStringView  gup_sv_chop_by_sv(GupStringView *sv, GupStringView thicc_delim);
bool           gup_sv_try_chop_by_delim(GupStringView *sv, char delim, GupStringView *chunk);
GupStringView  gup_sv_chop_left(GupStringView *sv, size_t n);
GupStringView  gup_sv_chop_right(GupStringView *sv, size_t n);
int            gup_sv_index_of(GupStringView sv, char c);
bool           gup_sv_eq(GupStringView a, GupStringView b);
bool           gup_sv_eq_ignorecase(GupStringView a, GupStringView b);
bool           gup_sv_eq_cstr(GupStringView sv, const char *cstr);
bool           gup_sv_starts_with(GupStringView sv, GupStringView prefix);
bool           gup_sv_ends_with(GupStringView sv, GupStringView suffix);
bool           gup_sv_is_empty(GupStringView sv);
void           gup_sv_print(GupStringView sv);

// XML ---------------------------------------------------------------------------------------------

typedef struct {
    GupStringView key;
    GupStringView value;
} GupXMLAttribute;

typedef struct {
    char        *name;       // XML tag name
    char        *data;       // Text inside of the open and close tags
    GupArrayPtr  attributes; // Dynamic array of attributes as key value pairs
    GupArrayPtr  children;   // Dynamic array of children XML tags  
} GupXMLTag;

GupXMLTag gup_xml_parse(const char *xml);

// C-string utilities ------------------------------------------------------------------------------
char *gup_string_trim_double_quotes(const char *string);
char *gup_string_trim_whitespace(const char *string);
char *gup_string_without_whitespace(const char *string);
char *gup_string_array_flatten(char **strings);
char  gup_cstr_eq(const char *a, const char *b);

// Miscellaneous
double gup_operation_seconds(void (*fn)());
#define gup_array_size(a) sizeof(a)/sizeof(a[0]) 
typedef unsigned int uint;
#define gup_defer_return(r) do { result = (r); goto defer; } while (0)

/**************************************************************************************************
 * Internal implementation                                                                        *
 **************************************************************************************************/

#define GUP_ARRAY_DEFAULT_CAPACITY 256

// Arena -------------------------------------------------------------------------------------------

GupArena gup_arena_create() {
    return (GupArena) {
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,
        .count = 0,
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(void *)),
    };
}

void gup_arena_destroy(GupArena a) {
    gup_arena_free(a);
    free(a.data);
}

void *gup_arena_alloc(GupArena *a, size_t bytes) {
    if (a->count == a->capacity) {
        const int new_capacity = a->capacity == 0 ? 1 : a->capacity * 2;
        a->data = realloc(a->data, new_capacity * sizeof(void *));
        a->capacity = new_capacity;
    }

    void *ptr = malloc(bytes);
    assert(ptr != NULL);

    a->data[a->count] = ptr;
    a->count++;

    return ptr;
}

void gup_arena_free(GupArena a) {
    for (int i = 0; i < a.count; i++) {
        free(a.data[i]);
    }
}

// TODO: Can I move this up to the Public API section
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

// Default constructors
#define GUP_DEFINE_ARRAY(U, l, t) GupArray##U gup_array_##l() {\
    GupArray##U xs = {                                         \
        .capacity = GUP_ARRAY_DEFAULT_CAPACITY,                \
        .count = 0,                                            \
        .data = malloc(GUP_ARRAY_DEFAULT_CAPACITY * sizeof(t)) \
    };                                                         \
    return xs;                                                 \
}                                                              \

GUP_DEFINE_ARRAY(Bool, bool, bool)
GUP_DEFINE_ARRAY(Char, char, char)
GUP_DEFINE_ARRAY(Double, double, double)
GUP_DEFINE_ARRAY(Float, float, float)
GUP_DEFINE_ARRAY(Int, int, int)
GUP_DEFINE_ARRAY(Long, long, long)
GUP_DEFINE_ARRAY(Ptr, ptr, void*)
GUP_DEFINE_ARRAY(Short, short, short)
GUP_DEFINE_ARRAY(String, string, GupArrayChar)

// Destructors
#define GUP_DEFINE_ARRAY_FREE(U, l, t) void gup_array_##l##_free(GupArray##U xs) {\
    free(xs.data);                                                                \
}                                                                                 \

GUP_DEFINE_ARRAY_FREE(Bool, bool, bool)
GUP_DEFINE_ARRAY_FREE(Char, char, char)
GUP_DEFINE_ARRAY_FREE(Double, double, double)
GUP_DEFINE_ARRAY_FREE(Float, float, float)
GUP_DEFINE_ARRAY_FREE(Int, int, int)
GUP_DEFINE_ARRAY_FREE(Long, long, long)
GUP_DEFINE_ARRAY_FREE(Short, short, short)

void gup_array_ptr_free(GupArrayPtr xs) {
    for (int i = 0; i < xs.count; i++) {
        free(xs.data[i]);
    }
    free(xs.data);
}

void gup_array_string_free(GupArrayString xs) {
    for (int i = 0; i < xs.count; i++) {
        free(xs.data[i].data);
    }
    free(xs.data);
}

// From constructors
#define GUP_DEFINE_ARRAY_FROM(U, l, t) GupArray##U gup_array_##l##_from(t xs[], const int size) {\
    GupArray##U new = gup_array_##l();                                                           \
                                                                                                 \
    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;        \
    new.count = size;                                                                            \
    new.data = realloc(new.data, new.capacity * sizeof(t));                                      \
    for (int i = 0; i < size; i++) {                                                             \
       new.data[i] = xs[i];                                                                      \
    }                                                                                            \
                                                                                                 \
    return new;                                                                                  \
}                                                                                                \

GUP_DEFINE_ARRAY_FROM(Bool, bool, bool)
GUP_DEFINE_ARRAY_FROM(Char, char, char)
GUP_DEFINE_ARRAY_FROM(Double, double, double)
GUP_DEFINE_ARRAY_FROM(Float, float, float)
GUP_DEFINE_ARRAY_FROM(Int,  int, int)
GUP_DEFINE_ARRAY_FROM(Long, long, long)
GUP_DEFINE_ARRAY_FROM(Ptr, ptr, void*)
GUP_DEFINE_ARRAY_FROM(Short, short, short)

GupArrayChar gup_array_char_from_cstr(char *cstr) {
    GupArrayChar new = gup_array_char();
    
    for (char *cstr_ptr = cstr; *cstr_ptr != '\0'; cstr_ptr++) {
        gup_array_char_append(&new, *cstr_ptr);
    }

    return new;
}

GupArrayString gup_array_string_from(GupArrayChar xs[], const int size) {
    GupArrayString new = gup_array_string();

    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    new.count = size;
    new.data = realloc(new.data, new.capacity * sizeof(GupArrayChar));
    for (int i = 0; i < size; i++) {
       new.data[i] = gup_array_char_copy(xs[i]);
    }

    return new;
}

GupArrayString gup_array_string_from_cstrs(char **xs, const int size) {
    GupArrayString new = gup_array_string();

    new.capacity = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    new.count = size;
    new.data = realloc(new.data, new.capacity * sizeof(char **));
    for (int i = 0; i < size; i++) {
       new.data[i] = gup_array_char_from_cstr(xs[i]);
    }

    return new;
}

// TODO: probably move this
char * gup_array_char_to_cstr(GupArrayChar chars) {
    // count + 1 for null terminator
    char *result = malloc((chars.count + 1) * sizeof(char));
    
    for (int i = 0; i < chars.count; i++) {
        result[i] = chars.data[i];
    }
    result[chars.count] = '\0';

    return result;
}

// TODO: probably move this
char ** gup_array_string_to_cstrs(GupArrayString strs) {
    // count + 1 for null terminator
    char **result = malloc((strs.count + 1) * sizeof(char *));

    for (int i = 0; i < strs.count; i++) {
        result[i] = gup_array_char_to_cstr(strs.data[i]);
    }
    result[strs.count] = NULL;

    return result;
}

// Copy constructors
#define GUP_DEFINE_ARRAY_COPY(U, l, t) GupArray##U gup_array_##l##_copy(GupArray##U xs) {\
    GupArray##U new = {                                                                \
        .capacity = xs.capacity,                                                       \
        .count = xs.count,                                                             \
        .data = malloc(xs.capacity * sizeof(t)),                                       \
                                                                                       \
    };                                                                                 \
    memcpy(new.data, xs.data, xs.count * sizeof(t));                                   \
                                                                                       \
    return new;                                                                        \
}                                                                                      \

GUP_DEFINE_ARRAY_COPY(Bool, bool, bool)
GUP_DEFINE_ARRAY_COPY(Char, char, char)
GUP_DEFINE_ARRAY_COPY(Double, double, double)
GUP_DEFINE_ARRAY_COPY(Float, float, float)
GUP_DEFINE_ARRAY_COPY(Int, int, int)
GUP_DEFINE_ARRAY_COPY(Long, long, long)
GUP_DEFINE_ARRAY_COPY(Short, short, short)

GupArrayPtr gup_array_ptr_copy(GupArrayPtr xs) {
    GupArrayPtr new = {
        .capacity = xs.capacity,
        .count = 0,
        .data = malloc(xs.capacity * sizeof(void *)),
    };
    for (int i = 0; i < xs.count; i++) {
        gup_array_ptr_append(&new, xs.data[i]);
    }

    return new;
}

GupArrayString gup_array_string_copy(GupArrayString xs) {
    GupArrayString new = {
        .capacity = xs.capacity,
        .count = 0,
        .data = malloc(xs.capacity * sizeof(GupString)),
    };
    for (int i = 0; i < xs.count; i++) {
        gup_array_string_append(&new, xs.data[i]);
    }

    return new;
}

// Equals
#define GUP_DEFINE_ARRAY_EQ(U, l, t) bool gup_array_##l##_eq(GupArray##U xs, GupArray##U ys) {\
    if (xs.count != ys.count) return false;                                                 \
                                                                                            \
    for (int i = 0; i < xs.count; i++) {                                                    \
        if (xs.data[i] != ys.data[i]) return false;                                         \
    }                                                                                       \
                                                                                            \
    return true;                                                                            \
}                                                                                           \

GUP_DEFINE_ARRAY_EQ(Bool, bool, bool)
GUP_DEFINE_ARRAY_EQ(Char, char, char)
GUP_DEFINE_ARRAY_EQ(Double, double, double)
GUP_DEFINE_ARRAY_EQ(Float, float, float)
GUP_DEFINE_ARRAY_EQ(Int, int, int)
GUP_DEFINE_ARRAY_EQ(Long, long, long)
GUP_DEFINE_ARRAY_EQ(Ptr, ptr, void*) // TODO: is shallow check ok?
GUP_DEFINE_ARRAY_EQ(Short, short, short)

#define gup_array_char_eq_cstr(xs, cstr) _gup_array_char_eq_cstr(xs, cstr, strlen(cstr))
bool _gup_array_char_eq_cstr(GupArrayChar xs, const char *cstr, int cstr_length) {
    if (xs.count != cstr_length) return false;
    
    return strncmp(xs.data, cstr, xs.count) == 0;
}

bool gup_array_string_eq(GupArrayString xs, GupArrayString ys) {
    if (xs.count != ys.count) return false;                     

    for (int i = 0; i < xs.count; i++) {
        if (!gup_array_char_eq(xs.data[i], ys.data[i])) return false;
    }                                                               

    return true;
}

// Print
#define gup_array_bool_print(xs) _gup_array_bool_print(xs, #xs)
void _gup_array_bool_print(GupArrayBool xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        if (xs.data[i] == true) printf("true");
        else printf("false");

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_char_print(xs) _gup_array_char_print(xs, #xs)
void _gup_array_char_print(GupArrayChar xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("'%c'", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_double_print(xs) _gup_array_double_print(xs, #xs)
void _gup_array_double_print(GupArrayDouble xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%f", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_float_print(xs) _gup_array_float_print(xs, #xs)
void _gup_array_float_print(GupArrayFloat xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%f", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_int_print(xs) _gup_array_int_print(xs, #xs)
void _gup_array_int_print(GupArrayInt xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%d", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_long_print(xs) _gup_array_long_print(xs, #xs)
void _gup_array_long_print(GupArrayLong xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%ld", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_ptr_print(xs) _gup_array_ptr_print(xs, #xs)
void _gup_array_ptr_print(GupArrayPtr xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%p", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_short_print(xs) _gup_array_short_print(xs, #xs)
void _gup_array_short_print(GupArrayShort xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        printf("%d", xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_string_print(xs) _gup_array_string_print(xs, #xs)
void _gup_array_string_print(GupArrayString xs, const char *xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs.count; i++) {
        gup_array_char_print(xs.data[i]);

        if (i != xs.count-1) printf(", ");
    }
    printf("]\n");
}

// Append
#define GUP_DEFINE_ARRAY_APPEND(U, l, t) void gup_array_##l##_append(GupArray##U *xs, t x) {\
    if (xs->count == xs->capacity) {                                                        \
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;                  \
        xs->data = realloc(xs->data, new_capacity * sizeof(t));                             \
        xs->capacity = new_capacity;                                                        \
    }                                                                                       \
                                                                                            \
    xs->data[xs->count] = x;                                                                \
    xs->count++;                                                                            \
}                                                                                           \

GUP_DEFINE_ARRAY_APPEND(Bool, bool, bool)
GUP_DEFINE_ARRAY_APPEND(Char, char, char)
GUP_DEFINE_ARRAY_APPEND(Double, double, double)
GUP_DEFINE_ARRAY_APPEND(Float, float, float)
GUP_DEFINE_ARRAY_APPEND(Int, int, int)
GUP_DEFINE_ARRAY_APPEND(Long, long, long)
GUP_DEFINE_ARRAY_APPEND(Ptr, ptr, void*)
GUP_DEFINE_ARRAY_APPEND(Short, short, short)

void gup_array_string_append(GupArrayString *xs, GupArrayChar x) {
    if (xs->count == xs->capacity) {
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;
        xs->data = realloc(xs->data, new_capacity * sizeof(GupArrayChar));
        xs->capacity = new_capacity;
    }

    xs->data[xs->count] = gup_array_char_copy(x);
    xs->count++;
}

// Prepend
#define GUP_DEFINE_ARRAY_PREPEND(U, l, t) void gup_array_##l##_prepend(GupArray##U *xs, t x) {\
    if (xs->count == xs->capacity) {                                                        \
        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;                  \
        xs->data = realloc(xs->data, new_capacity * sizeof(t));                             \
        xs->capacity = new_capacity;                                                        \
    }                                                                                       \
                                                                                            \
    for (int i = xs->count; i > 0; i--) {                                                   \
        xs->data[i] = xs->data[i-1];                                                        \
    }                                                                                       \
    xs->data[0] = x;                                                                        \
    xs->count++;                                                                            \
}                                                                                           \

GUP_DEFINE_ARRAY_PREPEND(Bool, bool, bool)
GUP_DEFINE_ARRAY_PREPEND(Char, char, char)
GUP_DEFINE_ARRAY_PREPEND(Double, double, double)
GUP_DEFINE_ARRAY_PREPEND(Float, float, float)
GUP_DEFINE_ARRAY_PREPEND(Int, int, int)
GUP_DEFINE_ARRAY_PREPEND(Long, long, long)
GUP_DEFINE_ARRAY_PREPEND(Short, short, short)
GUP_DEFINE_ARRAY_PREPEND(Ptr, ptr, void*)
GUP_DEFINE_ARRAY_PREPEND(String, string, GupArrayChar)

#define GUP_DEFINE_ARRAY_MAP(U, l, t) GupArray##U gup_array_##l##_map(GupArray##U xs, t (*fn)(t)) {\
    GupArray##U new = gup_array_##l##_from(xs.data, xs.count);                                     \
                                                                                                 \
    for (int i = 0; i < xs.count; i++) {                                                         \
        new.data[i] = fn(xs.data[i]);                                                            \
    }                                                                                            \
                                                                                                 \
    return new;                                                                                  \
}                                                                                                \

GUP_DEFINE_ARRAY_MAP(Bool, bool, bool)
GUP_DEFINE_ARRAY_MAP(Char, char, char)
GUP_DEFINE_ARRAY_MAP(Double, double, double)
GUP_DEFINE_ARRAY_MAP(Float, float, float)
GUP_DEFINE_ARRAY_MAP(Int, int, int)
GUP_DEFINE_ARRAY_MAP(Long, long, long)
GUP_DEFINE_ARRAY_MAP(Short, short, short)
GUP_DEFINE_ARRAY_MAP(Ptr, ptr, void*)
GUP_DEFINE_ARRAY_MAP(String, string, GupArrayChar)

#define GUP_DEFINE_ARRAY_MAP_IN_PLACE(U, l, t) void gup_array_##l##_map_in_place(GupArray##U xs, t (*fn)(t)) {\
    for (int i = 0; i < xs.count; i++) {                                                                    \
        xs.data[i] = fn(xs.data[i]);                                                                        \
    }                                                                                                       \
}                                                                                                           \

GUP_DEFINE_ARRAY_MAP_IN_PLACE(Bool, bool, bool)
GUP_DEFINE_ARRAY_MAP_IN_PLACE(Char, char, char)
GUP_DEFINE_ARRAY_MAP_IN_PLACE(Double, double, double)
GUP_DEFINE_ARRAY_MAP_IN_PLACE(Float, float, float)
GUP_DEFINE_ARRAY_MAP_IN_PLACE(Int, int, int)
GUP_DEFINE_ARRAY_MAP_IN_PLACE(Long, long, long)
GUP_DEFINE_ARRAY_MAP_IN_PLACE(Ptr, ptr, void*)
GUP_DEFINE_ARRAY_MAP_IN_PLACE(Short, short, short)
GUP_DEFINE_ARRAY_MAP_IN_PLACE(String, string, GupArrayChar)

#define GUP_DEFINE_ARRAY_FILTER(U, l, t) GupArray##U gup_array_##l##_filter(GupArray##U xs, bool (*fn)(t)) {\
    GupArray##U new = gup_array_##l();                                                                      \
                                                                                                            \
    for (int i = 0; i < xs.count; i++) {                                                                    \
        if (fn(xs.data[i])) {                                                                               \
            gup_array_##l##_append(&new, xs.data[i]);                                                       \
        }                                                                                                   \
    }                                                                                                       \
                                                                                                            \
    return new;                                                                                             \
}                                                                                                           \

GUP_DEFINE_ARRAY_FILTER(Bool, bool, bool)
GUP_DEFINE_ARRAY_FILTER(Char, char, char)
GUP_DEFINE_ARRAY_FILTER(Double, double, double)
GUP_DEFINE_ARRAY_FILTER(Float, float, float)
GUP_DEFINE_ARRAY_FILTER(Int, int, int)
GUP_DEFINE_ARRAY_FILTER(Long, long, long)
GUP_DEFINE_ARRAY_FILTER(Ptr, ptr, void*)
GUP_DEFINE_ARRAY_FILTER(Short, short, short)
GUP_DEFINE_ARRAY_FILTER(String, string, GupArrayChar)

#define GUP_DEFINE_ARRAY_FILTER_IN_PLACE(U, l, t) void gup_array_##l##_filter_in_place(GupArray##U *xs, bool (*fn)(t)) {\
    GupArray##U new = gup_array_##l##_filter(*xs, fn);                                                                  \
                                                                                                                        \
    free(xs->data);                                                                                                     \
    *xs = gup_array_##l##_from(new.data, new.count);                                                                    \
                                                                                                                        \
    free(new.data);                                                                                                     \
}                                                                                                                       \

GUP_DEFINE_ARRAY_FILTER_IN_PLACE(Bool, bool, bool)
GUP_DEFINE_ARRAY_FILTER_IN_PLACE(Char, char, char)
GUP_DEFINE_ARRAY_FILTER_IN_PLACE(Double, double, double)
GUP_DEFINE_ARRAY_FILTER_IN_PLACE(Float, float, float)
GUP_DEFINE_ARRAY_FILTER_IN_PLACE(Int, int, int)
GUP_DEFINE_ARRAY_FILTER_IN_PLACE(Long, long, long)
GUP_DEFINE_ARRAY_FILTER_IN_PLACE(Ptr, ptr, void*)
GUP_DEFINE_ARRAY_FILTER_IN_PLACE(Short, short, short)
GUP_DEFINE_ARRAY_FILTER_IN_PLACE(String, string, GupArrayChar)

#define GUP_DEFINE_ARRAY_REDUCE(U, l, t) t gup_array_reduce_##l(GupArray##U xs, t (*fn)(t, t), t start) {\
    t result = start;                                                                                    \
    for (int i = 0; i < xs.count; i++) {                                                                 \
        result = fn(result, xs.data[i]);                                                                 \
    }                                                                                                    \
    return result;                                                                                       \
}                                                                                                        \

GUP_DEFINE_ARRAY_REDUCE(Bool, bool, bool)
GUP_DEFINE_ARRAY_REDUCE(Char, char, char)
GUP_DEFINE_ARRAY_REDUCE(Double, double, double)
GUP_DEFINE_ARRAY_REDUCE(Float, float, float)
GUP_DEFINE_ARRAY_REDUCE(Int, int, int)
GUP_DEFINE_ARRAY_REDUCE(Long, long, long)
GUP_DEFINE_ARRAY_REDUCE(Ptr, ptr, void*)
GUP_DEFINE_ARRAY_REDUCE(Short, short, short)
GUP_DEFINE_ARRAY_REDUCE(String, string, GupArrayChar)

// Memory ------------------------------------------------------------------------------------------

/*
 * Thanks to Eskil Steenberg for his explanation of using these custom memory macros for debugging.
 * Check out his masterclass on programming in C: https://youtu.be/443UNeGrFoM
 */

static long long   _gup_bytes_allocated = 0;
static GupArrayInt _gup_allocation_sites;

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
    gup_array_int_append(&_gup_allocation_sites, line_number);

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
    char **file_lines = gup_file_read_lines_as_cstrs(file_path);
    if (file_lines == NULL) return;

    const int line_count = gup_file_line_count(file_path);
    for (int i = 0; i < line_count; i++) {
        if (file_lines[i] != NULL) {
            printf("%s\n", file_lines[i]);
            free(file_lines[i]);
        } else { // if there is an empty last line
            printf("\n");
        }
    }
}

void gup_file_print_lines(const char *file_path) {
     printf("[%s]\n", file_path);
    char **file_lines = gup_file_read_lines_as_cstrs(file_path);
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

GupString gup_file_read(const char *file_path) {
    GupString result = {0};

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s: %s\n", file_path, strerror(errno));
        #endif
        return result;
    }

    long file_size = gup_file_size(file_path);
    char *buffer = (char *) malloc(file_size + 1);
    size_t bytes_read = fread(buffer, sizeof(char), file_size, fp);

    gup_assert((long)bytes_read == file_size, "Failed to read file");

    buffer[file_size] = '\0';
    result = gup_array_char_from_cstr(buffer);
    gup_defer_return(result);

defer:
    if (fp) fclose(fp);
    free(buffer);
    return result;
}

char *gup_file_read_as_cstr(const char *file_path) {
    char *result;
    char *buffer;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        return NULL;
    }

    long file_size = gup_file_size(file_path);
    buffer = (char *) malloc(file_size + 1);

    size_t bytes_read = fread(buffer, sizeof(char), file_size, fp);
    if ((long)bytes_read != file_size) {
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

GupString _remove_trailing_newline(GupString str) {
    if (str.data[str.count-1] == '\n') {
        str.count--;
    }
    return str;
}

GupArrayString gup_file_read_lines(const char *file_path) {
    GupArrayString result = gup_file_read_lines_keep_newlines(file_path);
    gup_array_string_map_in_place(result, _remove_trailing_newline);
    return result;
}

GupArrayString gup_file_read_lines_keep_newlines(const char *file_path) {
    GupArrayString result = {0};
    char *line_buffer = NULL;
    size_t line_size = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to open file %s\n", file_path);
        #endif
        
        gup_defer_return(result);
    }

    int line_count = gup_file_line_count(file_path);
    if (line_count == 0) {
        #ifdef GUPPY_VERBOSE
        printf("No lines found in file %s\n", file_path);
        #endif
        
        gup_defer_return(result);
    }

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line_buffer, &line_size, fp);

        if (read == EOF) break;

        GupArrayChar line = gup_array_char_from_cstr(line_buffer);
        gup_array_string_append(&result, line);
        free(line.data);
    }

defer:
    free(line_buffer);
    if (fp) fclose(fp);

    return result;
}

char **gup_file_read_lines_as_cstrs(const char *file_path) {
    GupArrayString lines = gup_array_string();
    char **result = NULL;
    char *line_buffer = NULL;
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

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line_buffer, &line_size, fp);

        if (read == EOF) {
            gup_defer_return(gup_array_string_to_cstrs(lines));
        }

        // In normal gup_read_file_lines we don't want to keep newlines.
        line_buffer[read-1] = '\0';
        GupArrayChar line = gup_array_char_from_cstr(line_buffer);
        gup_array_string_append(&lines, line);
        free(line.data);
    }

    gup_defer_return(gup_array_string_to_cstrs(lines));

defer:
    gup_array_string_free(lines);
    free(line_buffer);
    if (fp) fclose(fp);

    return result;
}

char **gup_file_read_lines_as_cstrs_keep_newlines(const char *file_path) {
    GupArrayString lines = {0};
    char **result = NULL;
    char *line_buffer = NULL;
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

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line_buffer, &line_size, fp);

        if (read == EOF) {
            gup_defer_return(gup_array_string_to_cstrs(lines));
        }

        GupArrayChar line = gup_array_char_from_cstr(line_buffer);
        gup_array_string_append(&lines, line);
        free(line.data);
    }

    gup_defer_return(gup_array_string_to_cstrs(lines));

defer:
    gup_array_string_free(lines);
    free(line_buffer);
    if (fp) fclose(fp);

    return result;
}

long gup_file_size(const char *file_path) {
    FILE *fp = fopen(file_path, "rb");
    char failure_reason[1024];
    sprintf(failure_reason, "Failed to open %s: %s", file_path, strerror(errno));
    gup_assert(fp != NULL, failure_reason);

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fclose(fp);

    return file_size;
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

    char **settings_lines = gup_file_read_lines_as_cstrs(file_path);
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
    char **settings_lines = gup_file_read_lines_as_cstrs_keep_newlines(file_path);
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
        // TODO: this is horrendous
        char *new_line = malloc(strlen(key) + strlen(value) + 3 + 5 + 1);
        sprintf(new_line, "%s = \"%s\"\n", key, value);

        free(settings_lines[i]);
        settings_lines[i] = new_line;
        found = true;
    }

    // If we didn't find the key, increase the memory allocated for the array and add the new key
    // value pair to the end.
    if (!found) {
        settings_lines = realloc(settings_lines, (line_count + 2) * sizeof(char *));

        // TODO: This is horrendous
        char *new_line = malloc(strlen(key) + strlen(value) + 3 + 5 + 1);
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
    for (int i = 0; i < line_count; i++) {
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

#define SV(cstr_lit) gup_sv_from_parts(cstr_lit, sizeof(cstr_lit) - 1)
#define SV_NULL gup_sv_from_parts(NULL, 0)

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
    while (i + thicc_delim.length < sv->length && !(gup_sv_eq(window, thicc_delim))) {
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

void gup_sv_print(GupStringView sv) {
    // TODO: no more size_t please
    for (int i = 0; i < (int)sv.length; i++) {
        printf("%c", sv.data[i]);
    }
    printf("\n");
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

// XML ---------------------------------------------------------------------------------------------

GupStringView _gup_xml_get_tag_name(const char *xml) {
    GupStringView sv = gup_sv_from_cstr(xml);

    // Remove the left bracket
    sv = gup_sv_trim_char_left(&sv, '<');

    // Remove the right bracket
    sv = gup_sv_trim_char_right(&sv, '>');
    
    // Remove the trailing forward slash
    sv = gup_sv_trim_char_right(&sv, '/');

    // Trim the whitespace
    sv = gup_sv_trim(sv);

    gup_sv_print(sv);

    return sv;
}

typedef enum {
    _GUP_XML_PARSE_BEGIN = 0,
    _GUP_XML_TAG_BEGIN = 1,
    _GUP_XML_TAG_END = 2,
} GupXMLParseState;

GupXMLTag gup_xml_parse(const char *xml) {
    GupXMLTag result = {0};
    GupString tag = gup_array_char();
    GupString data = gup_array_char();
    GupXMLParseState parse_state = _GUP_XML_PARSE_BEGIN;

    for (int i = 0; xml[i] != '\0'; i++) {
        const char c = xml[i];
    
        // If cursor is on a letter (ASCII only currently).
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            switch (parse_state) {
                case _GUP_XML_TAG_BEGIN: {
                    gup_array_char_append(&tag, c);
                    break;
                }
                case _GUP_XML_TAG_END: {
                    gup_array_char_append(&data, c);
                    break;
                }
                default: {
                    continue;
                }
            }
        } else if (c == '<') {
            switch (parse_state) {
                case _GUP_XML_TAG_END: {
                    result.data = gup_array_char_to_cstr(data);
                    data.count = 0;
                    break;
                }
                default: {
                    break;
                }
            }
            parse_state = _GUP_XML_TAG_BEGIN;
        } else if (c == '>') {
            switch (parse_state) {
                case _GUP_XML_PARSE_BEGIN: {
                    // Really, this could probably be seen as some kind of parsing error.
                    // Maybe at least a warning?
                    continue;
                }
                case _GUP_XML_TAG_BEGIN: {
                    result.name = gup_array_char_to_cstr(tag);
                    tag.count = 0;
                    break;
                }
                default: {
                    break;
                }
            }

            parse_state = _GUP_XML_TAG_END;
        }
    }

    gup_array_char_free(tag);
    gup_array_char_free(data);
    return result;
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

#endif // GUPPY_H_
