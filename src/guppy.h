// See bottom for license information.

#ifndef GUPPY_H
#define GUPPY_H

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    size_t count;
    const char *data;
} Gup_String_View;

/**************************************************************************************************
 * Public API                                                                                     *
 **************************************************************************************************/

// Assert ------------------------------------------------------------------------------------------
void gup_assert(bool pass_condition, const char *failure_explanation);

// File operations ---------------------------------------------------------------------------------
bool   gup_file_create(const char *file_path);
bool   gup_file_delete(const char *file_path);
bool   gup_file_is_empty(const char *file_path);
int    gup_file_line_count(const char *file_path);
void   gup_file_print(const char *file_path);
char  *gup_file_read(const char *file_path);
char **gup_file_read_lines(const char *file_path);
char **gup_file_read_lines_keep_newlines(const char *file_path);
bool   gup_file_write(const char *file_path, const char *text_to_write);

// Print -------------------------------------------------------------------------------------------
void gup_print_string(const char *string);

// Print null terminated arrays -------------------------------------------------------------------------------
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
char *gup_settings_get_from(const char *key, const char *file_path);
int   gup_settings_get_int(const char *key);
bool  gup_settings_set(const char *key, const char *value);
bool  gup_settings_set_to(const char *key, const char *value, const char *file_path);
bool  gup_settings_set_int(const char *key, int value);

// String view -------------------------------------------------------------------------------------
Gup_String_View  gup_sv();
Gup_String_View  gup_sv_from_parts(const char *data, size_t count);
Gup_String_View  gup_sv_from_cstr(const char *cstr);
char            *gup_sv_to_cstr(Gup_String_View sv);
Gup_String_View  gup_sv_trim_left(Gup_String_View sv);
Gup_String_View  gup_sv_trim_right(Gup_String_View sv);
Gup_String_View  gup_sv_trim(Gup_String_View sv);
Gup_String_View  gup_sv_take_left_while(Gup_String_View sv, bool (*predicate)(char x));
Gup_String_View  gup_sv_chop_by_delim(Gup_String_View *sv, char delim);
Gup_String_View  gup_sv_chop_by_sv(Gup_String_View *sv, Gup_String_View thicc_delim);
bool             gup_sv_try_chop_by_delim(Gup_String_View *sv, char delim, Gup_String_View *chunk);
Gup_String_View  gup_sv_chop_left(Gup_String_View *sv, size_t n);
Gup_String_View  gup_sv_chop_right(Gup_String_View *sv, size_t n);
Gup_String_View  gup_sv_chop_left_while(Gup_String_View *sv, bool (*predicate)(char x));
int              gup_sv_index_of(Gup_String_View sv, char c);
bool             gup_sv_eq(Gup_String_View a, Gup_String_View b);
bool             gup_sv_eq_ignorecase(Gup_String_View a, Gup_String_View b);
bool             gup_sv_eq_cstr(Gup_String_View sv, const char *cstr);
bool             gup_sv_starts_with(Gup_String_View sv, Gup_String_View prefix);
bool             gup_sv_ends_with(Gup_String_View sv, Gup_String_View suffix);
bool             gup_sv_is_empty(Gup_String_View sv);

// C-string utilities --------------------------------------------------------------------------------
char *gup_string_trim_double_quotes(const char *string);
char *gup_string_trim_whitespace(const char *string);
char *gup_string_without_whitespace(const char *string);
char *gup_flatten_strings(char **strings, int count);
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

// Memory ------------------------------------------------------------------------------------------

/*
 * Thanks to Eskil Steenberg for his explanation of using these custom memory macros for debugging.
 * Check out his masterclass on programming in C: https://youtu.be/443UNeGrFoM
 */
#ifdef GUPPY_DEBUG_MEMORY

static uint      _gup_allocation_count = 0;
static long long _gup_bytes_allocated = 0;
static uint      _gup_free_count = 0;

void _gup_memory_print(void) {
    printf("\n============\n");
    printf("Memory usage:\n");
    printf("Allocations: %u (%lld bytes)\n", _gup_allocation_count, _gup_bytes_allocated);
    printf("Frees:       %u\n", _gup_free_count);
    printf("Leaks:       %d\n", _gup_allocation_count - _gup_free_count);
    printf("============\n");
}

void _gup_free(void *ptr, const char *file_path, const int line_number) {
    if (ptr == NULL) {
        printf("[%s:%d] ", file_path, line_number);
        printf("Tried to free a null pointer\n");
        exit(1);
    }

    #ifdef GUPPY_DEBUG_MEMORY
    printf("[%s:%d] Freed memory at %p\n", file_path, line_number, ptr);
    #endif

    free(ptr);
    _gup_free_count++;
}

void *_gup_malloc(size_t bytes, const char *file_path, const int line_number) {
    void *ptr = malloc(bytes);

    if (ptr == NULL) {
        printf("[%s:%d] ", file_path, line_number);
        printf("Failed to allocate %zu bytes\n", bytes);
        exit(1);
    }

    #ifdef GUPPY_DEBUG_MEMORY
    printf("[%s:%d] Allocated %zu bytes at %p\n", file_path, line_number, bytes, ptr);
    #endif

    _gup_allocation_count++;
    _gup_bytes_allocated += bytes;

    return ptr;
}

#define free(ptr) _gup_free(ptr, __FILE__, __LINE__)
#define malloc(bytes) _gup_malloc(bytes, __FILE__, __LINE__)

#endif

// File operations ---------------------------------------------------------------------------------

const char *GUP_DEFAULT_FILE_ERROR_MESSAGE = "Weird... a guppy file operation failed.\nYou should probably double check that you:\n1) spelled the file name correctly\n2) are creating the file in the directory you think you are\n3) have permissions to create a file in that directory\n";

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
    gup_assert(line_count == -1, "gup_file_line_count had an issue while opening the file.");

    return line_count == 0;
}

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
    char **file_lines = gup_file_read_lines(file_path);
    gup_assert(file_lines != NULL, GUP_DEFAULT_FILE_ERROR_MESSAGE);

    printf("[%s]\n", file_path);
    for (size_t i = 0; file_lines[i] != NULL; i++) {
        printf("%s\n", file_lines[i]);
    }

    free(file_lines);
}

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
    if (buffer == NULL) {
        #ifdef GUPPY_VERBOSE
        printf("Failed to allocate memory for file %s\n", file_path);
        #endif
        gup_defer_return(NULL);
    }

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

defer:
    if (line) free(line);
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
        printf("Failed to open file %s\n", file_path);
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
    if (line) free(line);
    if (fp) fclose(fp);
    return result;
}

bool gup_file_write(const char *file_path, const char *text_to_write) {
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

// Print -------------------------------------------------------------------------------------------

void gup_print_string(const char *string) {
    printf("\"%s\"\n", string);
}

// Print null terminated arrays -------------------------------------------------------------------------------

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
    for (size_t i = 0; array[i] != '\0'; i++) {
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

char *gup_settings_get(const char *key) {
    return gup_settings_get_from(key, GUP_DEFAULT_SETTINGS_FILE_PATH);
}

char *gup_settings_get_from(const char *key, const char *file_path) {
    char *result = NULL;
    
    int line_count = gup_file_line_count(file_path);
    gup_assert(line_count != -1, GUP_DEFAULT_FILE_ERROR_MESSAGE);
    gup_assert(line_count != 0, "The settings file is empty. You should probably add some settings to it.");

    char **settings_lines = gup_file_read_lines(file_path);
    gup_assert(settings_lines != NULL, GUP_DEFAULT_FILE_ERROR_MESSAGE);

    for (int i = 0; i < line_count; i++) {
        Gup_String_View line = gup_sv_from_cstr(settings_lines[i]);

        // Skip comments.
        if (gup_sv_index_of(line, '#') != -1) continue;
        // Skip section headers.
        if (gup_sv_index_of(line, '[') != -1) continue;

        Gup_String_View line_key;
        const bool line_has_an_equals_sign = gup_sv_try_chop_by_delim(&line, '=', &line_key);
        // Skip lines without an equals sign.
        if (!line_has_an_equals_sign) continue; 
        
        line_key = gup_sv_trim(line_key);
        // Skip lines that don't match the key.
        if (!gup_sv_eq(line_key, gup_sv_trim(gup_sv_from_cstr(key)))) continue; 

        char *value_cstr = gup_sv_to_cstr(gup_sv_trim(line));
        gup_defer_return(gup_string_trim_double_quotes(value_cstr));
    }

    // If we get here, we didn't find the key.
defer:
    for (int i = 0; i < line_count; i++) {
        if (settings_lines[i]) {
            free(settings_lines[i]);
        }
    }
    free(settings_lines);
    return result;
}

int gup_settings_get_int(const char *key) {
    const char *value = gup_settings_get(key);
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

    return (int) result;
}

bool gup_settings_set(const char *key, const char *value) {
    return gup_settings_set_to(key, value, GUP_DEFAULT_SETTINGS_FILE_PATH);
}

// First, we read the file into memory. Then, we iterate through the lines, looking for the key.
// If we find the key, we replace the value. If we don't find the key, we append the key-value pair
// to the end of the file.
/*
bool gup_settings_set_to(const char *key, const char *value, const char *file_path) {
    bool result = true;
    bool found = false;
    
    int line_count = gup_file_line_count(file_path);
    gup_assert(line_count != -1, GUP_DEFAULT_FILE_ERROR_MESSAGE);
    gup_assert(line_count != 0, "The settings file is empty. You should probably add some settings to it.");

    char **settings_lines = gup_file_read_lines(file_path);
    gup_assert(settings_lines != NULL, GUP_DEFAULT_FILE_ERROR_MESSAGE);

    char **new_settings_lines = malloc((line_count + 1) * sizeof(char *));

    for (int i = 0; i < line_count; i++) {
        if (settings_lines[i] == NULL) continue;

        Gup_String_View line = gup_sv_from_cstr(settings_lines[i]);

        // Skip comments.
        if (gup_sv_index_of(line, '#') != -1) {
            new_settings_lines[i] = malloc(strlen(settings_lines[i]) + 1);
            strcpy(new_settings_lines[i], settings_lines[i]);
            continue;
        }
        // Skip section headers.
        if (gup_sv_index_of(line, '[') != -1) {
            new_settings_lines[i] = malloc(strlen(settings_lines[i]) + 1);
            strcpy(new_settings_lines[i], settings_lines[i]);
            continue;
        }

        Gup_String_View line_key;
        const bool line_has_an_equals_sign = gup_sv_try_chop_by_delim(&line, '=', &line_key);
        // Skip lines without an equals sign.
        if (!line_has_an_equals_sign) {
            new_settings_lines[i] = malloc(strlen(settings_lines[i]) + 1);
            strcpy(new_settings_lines[i], settings_lines[i]);
            continue;
        }
        
        line_key = gup_sv_trim(line_key);
        // Skip lines that don't match the key.
        if (!gup_sv_eq(line_key, gup_sv_trim(gup_sv_from_cstr(key)))) {
            new_settings_lines[i] = malloc(strlen(settings_lines[i]) + 1);
            strcpy(new_settings_lines[i], settings_lines[i]);
            continue;
        } 

        // If we get here, we found the key. Replace the value.
        found = true;
        char *new_line = malloc(strlen(key) + strlen(value) + 3);
        sprintf(new_line, "%s = \"%s\"", key, value);
        strcpy(new_settings_lines[i], new_line);
    }

    char *new_settings;
    if (!found) {
        char *new_line = malloc(strlen(key) + strlen(value) + 3);
        sprintf(new_line, "%s = \"%s\"", key, value);
        // Allocate room for one more line in the settings lines with realloc
        // TODO: with realloc?
        new_settings_lines = malloc((line_count + 2) * sizeof(char *));

        strcpy(new_settings_lines[line_count], new_line);
        new_settings_lines[line_count + 1] = NULL;

        new_settings = gup_flatten_strings(new_settings_lines, line_count + 1);
    } else {
        new_settings_lines[line_count] = NULL;

        new_settings = gup_flatten_strings(new_settings_lines, line_count);
    }

    // Write the new settings lines to the file.
    
    gup_file_write(file_path, new_settings);

defer:
    for (int i = 0; i < line_count; i++) {
        if (settings_lines[i]) {
            free(settings_lines[i]);
        }
    }
    free(settings_lines);

    return result;
}
*/
bool gup_settings_set_to(const char *key, const char *value, const char *file_path) {
    printf("gup_settings_set_to is not implemented yet.\n");
    printf("key: %s\n", key);
    printf("value: %s\n", value);
    printf("file_path: %s\n", file_path);
    return false;
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
#define SV_Arg(sv) (int) (sv).count, (sv).data
/* 
 * USAGE:
 *   String_View name = ...;
 *   printf("Name: "SV_Fmt"\n", SV_Arg(name));
 */

Gup_String_View gup_sv() {
    Gup_String_View sv;
    sv.count = 0;
    sv.data = NULL;
    return sv;
}

Gup_String_View gup_sv_from_parts(const char *data, size_t count) {
    Gup_String_View sv;
    sv.count = count;
    sv.data = data;
    return sv;
}

Gup_String_View gup_sv_from_cstr(const char *cstr) {
    return gup_sv_from_parts(cstr, strlen(cstr));
}

char *gup_sv_to_cstr(Gup_String_View sv) {
    char *cstr = malloc(sv.count + 1);
    memcpy(cstr, sv.data, sv.count);
    cstr[sv.count] = '\0';
    return cstr;
}

Gup_String_View gup_sv_trim_left(Gup_String_View sv) {
    size_t i = 0;
    while (i < sv.count && isspace(sv.data[i])) {
        i += 1;
    }

    return gup_sv_from_parts(sv.data + i, sv.count - i);
}

Gup_String_View gup_sv_trim_right(Gup_String_View sv) {
    size_t i = 0;
    while (i < sv.count && isspace(sv.data[sv.count - 1 - i])) {
        i += 1;
    }

    return gup_sv_from_parts(sv.data, sv.count - i);
}

Gup_String_View gup_sv_trim(Gup_String_View sv) {
    return gup_sv_trim_right(gup_sv_trim_left(sv));
}

Gup_String_View gup_sv_chop_left(Gup_String_View *sv, size_t n) {
    if (n > sv->count) {
        n = sv->count;
    }

    Gup_String_View result = gup_sv_from_parts(sv->data, n);

    sv->data  += n;
    sv->count -= n;

    return result;
}

Gup_String_View gup_sv_chop_right(Gup_String_View *sv, size_t n) {
    if (n > sv->count) {
        n = sv->count;
    }

    Gup_String_View result = gup_sv_from_parts(sv->data + sv->count - n, n);

    sv->count -= n;

    return result;
}

int gup_sv_index_of(Gup_String_View sv, char c) {
    int i = 0;
    while (i < (int)sv.count && sv.data[i] != c) {
        i += 1;
    }

    return i < (int)sv.count ? i : -1;
}

bool gup_sv_try_chop_by_delim(Gup_String_View *sv, char delim, Gup_String_View *chunk) {
    size_t i = 0;
    while (i < sv->count && sv->data[i] != delim) {
        i += 1;
    }

    Gup_String_View result = gup_sv_from_parts(sv->data, i);

    if (i < sv->count) {
        sv->count -= i + 1;
        sv->data  += i + 1;
        if (chunk) {
            *chunk = result;
        }
        return true;
    }

    return false;
}

Gup_String_View gup_sv_chop_by_delim(Gup_String_View *sv, char delim) {
    size_t i = 0;
    while (i < sv->count && sv->data[i] != delim) {
        i += 1;
    }

    Gup_String_View result = gup_sv_from_parts(sv->data, i);

    if (i < sv->count) {
        sv->count -= i + 1;
        sv->data  += i + 1;
    } else {
        sv->count -= i;
        sv->data  += i;
    }

    return result;
}

Gup_String_View gup_sv_chop_by_sv(Gup_String_View *sv, Gup_String_View thicc_delim) {
    Gup_String_View window = gup_sv_from_parts(sv->data, thicc_delim.count);
    size_t i = 0;
    while (i + thicc_delim.count < sv->count
        && !(gup_sv_eq(window, thicc_delim)))
    {
        i++;
        window.data++;
    }

    Gup_String_View result = gup_sv_from_parts(sv->data, i);

    if (i + thicc_delim.count == sv->count) {
        // include last <thicc_delim.count> characters if they aren't
        //  equal to thicc_delim
        result.count += thicc_delim.count;
    }

    // Chop!
    sv->data  += i + thicc_delim.count;
    sv->count -= i + thicc_delim.count;

    return result;
}

bool gup_sv_starts_with(Gup_String_View sv, Gup_String_View expected_prefix) {
    if (expected_prefix.count <= sv.count) {
        Gup_String_View actual_prefix = gup_sv_from_parts(sv.data, expected_prefix.count);
        return gup_sv_eq(expected_prefix, actual_prefix);
    }

    return false;
}

bool gup_sv_ends_with(Gup_String_View sv, Gup_String_View expected_suffix) {
    if (expected_suffix.count <= sv.count) {
        Gup_String_View actual_suffix = gup_sv_from_parts(sv.data + sv.count - expected_suffix.count, expected_suffix.count);
        return gup_sv_eq(expected_suffix, actual_suffix);
    }

    return false;
}

bool gup_sv_is_empty(Gup_String_View sv) {
    return sv.count == 0;
}

bool gup_sv_eq(Gup_String_View a, Gup_String_View b) {
    if (a.count != b.count) {
        return false;
    } else {
        return memcmp(a.data, b.data, a.count) == 0;
    }
}

bool gup_sv_eq_ignorecase(Gup_String_View a, Gup_String_View b) {
    if (a.count != b.count) {
        return false;
    }

    char x, y;
    for (size_t i = 0; i < a.count; i++) {
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

bool gup_sv_eq_cstr(Gup_String_View sv, const char *cstr) {
    if (cstr == NULL) return false;

    return gup_sv_eq(sv, gup_sv_from_cstr(cstr));
}

Gup_String_View gup_sv_chop_left_while(Gup_String_View *sv, bool (*predicate)(char x)) {
    size_t i = 0;
    while (i < sv->count && predicate(sv->data[i])) {
        i += 1;
    }
    return gup_sv_chop_left(sv, i);
}

Gup_String_View gup_sv_take_left_while(Gup_String_View sv, bool (*predicate)(char x)) {
    size_t i = 0;
    while (i < sv.count && predicate(sv.data[i])) {
        i += 1;
    }
    return gup_sv_from_parts(sv.data, i);
}

// C-string utilities --------------------------------------------------------------------------------

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

char *gup_flatten_strings(char **strings, int count) {
    // Calculate the total length of all the strings.
    int total_length = 0;
    for (int i = 0; i < count; i++) {
        total_length += strlen(strings[i]);
    }

    // Allocate a new buffer to hold the flattened string.
    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    // Copy each string into the buffer.
    int offset = 0;
    for (int i = 0; i < count; i++) {
        strcpy(result + offset, strings[i]);
        offset += strlen(strings[i]);
    }

    // Add a null terminator to the end of the buffer.
    result[total_length] = '\0';

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
