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
bool   gup_file_create(const char *file_name);
bool   gup_file_delete(const char *file_name);
bool   gup_file_is_empty(const char *file_name);
int    gup_file_line_count(const char *file_name);
void   gup_file_print(const char *file_name);
char  *gup_file_read(const char *file_name);
char **gup_file_read_lines(const char *file_name);
char **gup_file_read_lines_keep_newlines(const char *file_name);
bool   gup_file_write(const char *file_name, const char *text_to_write);

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

// String view -------------------------------------------------------------------------------------
Gup_String_View gup_sv_from_parts(const char *data, size_t count);
Gup_String_View gup_sv_from_cstr(const char *cstr);
Gup_String_View gup_sv_trim_left(Gup_String_View sv);
Gup_String_View gup_sv_trim_right(Gup_String_View sv);
Gup_String_View gup_sv_trim(Gup_String_View sv);
Gup_String_View gup_sv_take_left_while(Gup_String_View sv, bool (*predicate)(char x));
Gup_String_View gup_sv_chop_by_delim(Gup_String_View *sv, char delim);
Gup_String_View gup_sv_chop_by_sv(Gup_String_View *sv, Gup_String_View thicc_delim);
bool            gup_sv_try_chop_by_delim(Gup_String_View *sv, char delim, Gup_String_View *chunk);
Gup_String_View gup_sv_chop_left(Gup_String_View *sv, size_t n);
Gup_String_View gup_sv_chop_right(Gup_String_View *sv, size_t n);
Gup_String_View gup_sv_chop_left_while(Gup_String_View *sv, bool (*predicate)(char x));
bool            gup_sv_index_of(Gup_String_View sv, char c, size_t *index);
bool            gup_sv_eq(Gup_String_View a, Gup_String_View b);
bool            gup_sv_eq_ignorecase(Gup_String_View a, Gup_String_View b);
bool            gup_sv_starts_with(Gup_String_View sv, Gup_String_View prefix);
bool            gup_sv_ends_with(Gup_String_View sv, Gup_String_View suffix);

// C-string utilities --------------------------------------------------------------------------------
char *gup_string_trim_double_quotes(const char *string);
char *gup_string_trim_whitespace(const char *string);
char *gup_string_without_whitespace(const char *string);

/**************************************************************************************************
 * Internal implementation                                                                        *
 **************************************************************************************************/

#define gup_defer_return(r) do { result = (r); goto defer; } while (0)
#define gup_print_variable_name(variable) printf("%s: ", #variable)

// Memory ------------------------------------------------------------------------------------------

void *_gup_malloc(size_t bytes, const char *file_name, int line_number) {
    void *ptr = malloc(bytes);

    if (ptr == NULL) {
        printf("[%s:%d] ", file_name, line_number);
        printf("Failed to allocate %zu bytes\n", bytes);
        exit(1);
    }

    #ifdef GUPPY_DEBUG_MEMORY
    printf("[%s:%d] Allocated %zu bytes at %p\n", file_name, line_number, bytes, ptr);
    #endif

    return ptr;
}

#ifdef GUPPY_DEBUG_MEMORY
#define malloc(bytes) _gup_malloc(bytes, __FILE__, __LINE__)
#endif

// Assert ------------------------------------------------------------------------------------------

void _gup_assert(bool pass_condition, const char *failure_explanation, const char *readable_pass_condition, const char *file_name, int line_number) {
    if (!pass_condition) {
        printf("[%s:%d] Failed assertion!\n", file_name, line_number);
        printf("---> %s <---\n", readable_pass_condition);
        printf("%s\n", failure_explanation);
        exit(1);
    }
}
#define gup_assert(pass_condition, failure_explanation) _gup_assert(pass_condition, failure_explanation, #pass_condition, __FILE__, __LINE__)

// File operations ---------------------------------------------------------------------------------

const char *GUP_DEFAULT_FILE_ERROR_MESSAGE = "Weird... a guppy file operation failed.\nYou should probably double check that you:\n1) spelled the file name correctly\n2) are creating the file in the directory you think you are\n3) have permissions to create a file in that directory\n";

bool gup_file_create(const char *file_name) {
    bool result = true;
    
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Failed to create file %s\n", file_name);
        gup_defer_return(false);
    }

defer:
    fclose(fp);
    return result;
}

bool gup_file_delete(const char *file_name) {
    const bool result = remove(file_name);

    #ifdef GUPPY_DEBUG
    if (!result) {    
        printf("Failed to delete file %s\n", file_name);
    }
    #endif // GUPPY_DEBUG

    return result;
}

bool gup_file_is_empty(const char *file_name) {
    int line_count = gup_file_line_count(file_name);
    // TODO: asserting here might be kinda overkill.
    gup_assert(line_count != -1, "gup_file_line_count had an issue while opening the file.");

    return line_count == 0;
}

int gup_file_line_count(const char *file_name) {
    int c = 0;
    int line_count = 0;
    int result = 0;

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        #ifdef GUPPY_DEBUG
        printf("Error opening file %s\n", file_name);
        #endif
        
        return -1;
    }

    c = fgetc(fp);
    if (c == EOF) {
        #ifdef GUPPY_DEBUG
        printf("The file you're trying to open (\"%s\") is empty\n", file_name);
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

void gup_file_print(const char *file_name) {
    char **file_lines = gup_file_read_lines(file_name);
    gup_assert(file_lines != NULL, GUP_DEFAULT_FILE_ERROR_MESSAGE);

    printf("[%s]\n", file_name);
    for (size_t i = 0; file_lines[i] != NULL; i++) {
        printf("%s\n", file_lines[i]);
    }
}

char *gup_file_read(const char *file_name) {
    char *result;
    char *buffer;
    size_t file_size;

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        #ifdef GUPPY_DEBUG
        printf("Failed to open file %s\n", file_name);
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
        #ifdef GUPPY_DEBUG
        printf("Failed to allocate memory for file %s\n", file_name);
        #endif
        gup_defer_return(NULL);
    }

    size_t bytes_read = fread(buffer, sizeof(char), file_size, fp);
    if (bytes_read != file_size) {
        #ifdef GUPPY_DEBUG
        printf("Failed to read file %s\n", file_name);
        #endif
        gup_defer_return(NULL);
    }
    buffer[file_size] = '\0';
    gup_defer_return(buffer);

defer:
    fclose(fp);
    return result;
}

char **gup_file_read_lines(const char *file_name) {
    char **lines = NULL;
    char *line = NULL;
    size_t line_size = 0;

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        #ifdef GUPPY_DEBUG
        printf("Failed to open file %s\n", file_name);
        #endif
        
        return NULL;
    }

    int line_count = gup_file_line_count(file_name);
    if (line_count == 0) {
        #ifdef GUPPY_DEBUG
        printf("No lines found in file %s\n", file_name);
        #endif
        
        return NULL;
    }

    lines = malloc(line_count * sizeof(char *));
    assert(lines != NULL);

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line, &line_size, fp);

        if (read == EOF) {
            lines[i] = NULL;
            break;
        }

        // Only allocate the exact amount of memory needed for the line text excluding the newline.
        lines[i] = (char *) malloc(read * sizeof(char));
        strncpy(lines[i], line, read-1);
        lines[i][read-1] = '\0';
    }

    free(line);
    fclose(fp);

    lines[line_count] = NULL;
    return lines;
}

char **gup_file_read_lines_keep_newlines(const char *file_name) {
    char **lines = NULL;
    char **result = NULL;
    char *line = NULL;
    size_t line_size = 0;

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Failed to open file %s\n", file_name);
        gup_defer_return(NULL);
    }

    int line_count = gup_file_line_count(file_name);
    if (line_count == 0) {
        #ifdef GUPPY_DEBUG
        printf("No lines found in file %s\n", file_name);
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

bool gup_file_write(const char *file_name, const char *text_to_write) {
    bool result = true;

    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Failed to open file %s\n", file_name);
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

/*
 * This is the default function, so it assumes the settings file is named settings.toml and is in
 * the current directory.
 */ 
char *gup_settings_get(const char *key) {
    int line_count = gup_file_line_count("test/settings.toml");
    gup_assert(line_count != -1, GUP_DEFAULT_FILE_ERROR_MESSAGE);
    gup_assert(line_count != 0, "The settings file is empty. You should probably add some settings to it.");

    char **settings_lines = gup_file_read_lines("test/settings.toml");
    gup_assert(settings_lines != NULL, GUP_DEFAULT_FILE_ERROR_MESSAGE);

    char *current_line = NULL;
    for (int i = 0; i < line_count; i++) {
        current_line = settings_lines[i];

        if (current_line[0] == '#') continue; // Skip comments.
        if (current_line[0] == '[') continue; // Skip section headers.

        char *current_key = strtok(current_line, "=");
        if (current_key == NULL) continue;
        
        char *trimmed_current_key = gup_string_trim_whitespace(current_key);
        if (strcmp(trimmed_current_key, key) != 0) continue;

        char *value = strtok(NULL, "=");
        char *trimmed_value = gup_string_trim_whitespace(value);
        return gup_string_trim_double_quotes(trimmed_value);
    }

    // If we get here, we didn't find the key.
    return NULL;
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

Gup_String_View gup_sv_from_parts(const char *data, size_t count) {
    Gup_String_View sv;
    sv.count = count;
    sv.data = data;
    return sv;
}

Gup_String_View gup_sv_from_cstr(const char *cstr) {
    return gup_sv_from_parts(cstr, strlen(cstr));
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

bool gup_sv_index_of(Gup_String_View sv, char c, size_t *index) {
    size_t i = 0;
    while (i < sv.count && sv.data[i] != c) {
        i += 1;
    }

    if (i < sv.count) {
        if (index) {
            *index = i;
        }
        return true;
    } else {
        return false;
    }
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
