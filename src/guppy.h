#ifndef GUPPY_H
#define GUPPY_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/scrump.h"

/**************************************************************************************************
 * Public API                                                                                     *
 **************************************************************************************************/

// Assert ------------------------------------------------------------------------------------------
void guppy_assert(bool pass_condition, const char *failure_explanation);

// Print -------------------------------------------------------------------------------------------

void guppy_print_string(const char *string);

// Print full arrays -------------------------------------------------------------------------------
void guppy_print_array_bool(bool array[], const char *array_name);
void guppy_print_array_char(char array[]);
void guppy_print_array_double(double array[], const char *array_name);
void guppy_print_array_float(float array[], const char *array_name);
void guppy_print_array_int(int array[], const char *array_name);
void guppy_print_array_long(long array[], const char *array_name);
void guppy_print_array_string(char *array[], const char *array_name);

// Print array slices [start, end) -----------------------------------------------------------------
void guppy_print_array_slice_bool(bool array[], size_t start, size_t end, const char *array_name);
void guppy_print_array_slice_char(char array[], size_t start, size_t end, const char *array_name);
void guppy_print_array_slice_double(double array[], size_t start, size_t end, const char *array_name);
void guppy_print_array_slice_float(float array[], size_t start, size_t end, const char *array_name);
void guppy_print_array_slice_int(int array[], size_t start, size_t end, const char *array_name);
void guppy_print_array_slice_long(long array[], size_t start, size_t end, const char *array_name);

// File operations ---------------------------------------------------------------------------------
int    guppy_file_create(const char *file_name);
char  *guppy_file_find_line_containing(const char *file_name, const char *text_to_find);
bool   guppy_file_is_empty(const char *file_name);
int    guppy_file_line_count(const char *file_name);
char  *guppy_file_read(const char *file_name);
char **guppy_file_read_lines(const char *file_name);
char **guppy_file_read_lines_keep_newlines(const char *file_name);
int    guppy_file_write(const char *file_name, const char *text_to_write);

/**************************************************************************************************
 * Internal implementation                                                                        *
 **************************************************************************************************/

// Memory ------------------------------------------------------------------------------------------

void *_guppy_malloc(size_t n, const char *file_name, int line_number) {
    void *ptr = malloc(n);

    if (ptr == NULL) {
        printf("[%s:%d] ", file_name, line_number);
        printf("Failed to allocate %zu bytes\n", n);
        exit(1);
    }

    #ifdef GUPPY_DEBUG_MEMORY
    printf("[%s:%d] Allocated %zu bytes at %p\n", file_name, line_number, n, ptr);
    #endif

    return ptr;
}

#ifdef GUPPY_DEBUG
#define malloc(n) _guppy_malloc(n, __FILE__, __LINE__)
#endif

// Assert ------------------------------------------------------------------------------------------

void _guppy_assert(bool pass_condition, const char *failure_explanation, const char *readable_pass_condition, const char *file_name, int line_number) {
    if (!pass_condition) {
        printf("[%s:%d] Failed assertion!\n", file_name, line_number);
        printf("---> %s <---\n", readable_pass_condition);
        printf("%s\n", failure_explanation);
        exit(1);
    }
}
#define guppy_assert(pass_condition, failure_explanation) _guppy_assert(pass_condition, failure_explanation, #pass_condition, __FILE__, __LINE__)

// Print -------------------------------------------------------------------------------------------

void guppy_print_string(const char *string) {
    printf("\"%s\"\n", string);
}

// Print full arrays -------------------------------------------------------------------------------

void _guppy_print_array_bool(bool array[], const char *array_name) {
    printf("%s: [", array_name);
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
#define guppy_print_array_bool(array) _guppy_print_array_bool(array, #array)

void _guppy_print_array_char(char array[], const char *array_name) {
    printf("%s", array);
    printf("%s: [", array_name);
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
#define guppy_print_array_char(array) _guppy_print_array_char(array, #array)

void _guppy_print_array_double(double array[], const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; array[i] != '\0'; i++) {
        printf("%.17f", array[i]);
        if (array[i+1] != '\0') {
            printf(", ");
        }
    }
    printf("]\n");
}
#define guppy_print_array_double(array) _guppy_print_array_double(array, #array)

void _guppy_print_array_float(float array[], const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; array[i] != '\0'; i++) {
        printf("%f", array[i]);
        if (array[i+1] != '\0') {
            printf(", ");
        }
    }
    printf("]\n");
}
#define guppy_print_array_float(array) _guppy_print_array_float(array, #array)

void _guppy_print_array_int(int array[], const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; array[i] != '\0'; i++) {
        printf("%d", array[i]);
        if (array[i+1] != '\0') {
            printf(", ");
        }
    }
    printf("]\n");
}
#define guppy_print_array_int(array) _guppy_print_array_int(array, #array)

void _guppy_print_array_long(long array[], const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; array[i] != '\0'; i++) {
        printf("%ld", array[i]);
        if (array[i+1] != '\0') {
            printf(", ");
        }
    }
    printf("]\n");
}
#define guppy_print_array_long(array) _guppy_print_array_long(array, #array)

void _guppy_print_array_string(char *array[], const char *array_name) {
    if (array == NULL) {
        printf("%s: NULL\n", array_name);
        return;
    }
    
    printf("%s: [", array_name);
    for (size_t i = 0; array[i] != NULL; i++) {
        printf("\"%s\"", array[i]);
        if (array[i+1] != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}
#define guppy_print_array_string(array) _guppy_print_array_string(array, #array)

// Print array slices ------------------------------------------------------------------------------

void guppy_print_array_slice_bool(bool array[], size_t start, size_t end, const char *array_name) {
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

void guppy_print_array_slice_char(char array[], size_t start, size_t end, const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = start; i < end; i++) {
        printf("'%c'", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_array_slice_double(double array[], size_t start, size_t end, const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = start; i < end; i++) {
        printf("%.17f", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_array_slice_float(float array[], size_t start, size_t end, const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = start; i < end; i++) {
        printf("%f", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_array_slice_int(int array[], size_t start, size_t end, const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = start; i < end; i++) {
        printf("%d", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_array_slice_long(long array[], size_t start, size_t end, const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = start; i < end; i++) {
        printf("%ld", array[i]);
        if (i < end - 1) printf(", ");
    }
    printf("]\n");
}

// File operations ---------------------------------------------------------------------------------

const char *GUPPY_DEFAULT_FILE_ERROR_MESSAGE = "Weird... a guppy file operation failed.\nYou should probably double check that you:\n1) spelled the file name correctly\n2) are creating the file in the directory you think you are\n3) have permissions to create a file in that directory\n";

int guppy_file_create(const char *file_name) {
    FILE *fp;

    fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Failed to create file %s\n", file_name);
        return 1;
    }

    fclose(fp);
    return 0;
}

char *guppy_file_find_line_containing(const char *file_name, const char *text_to_find) {
    char **file_lines = guppy_file_read_lines(file_name);
    guppy_assert(file_lines != NULL, GUPPY_DEFAULT_FILE_ERROR_MESSAGE);

    guppy_print_array_string(file_lines);
    
    return "Not implemented yet";
}

bool guppy_file_is_empty(const char *file_name) {
    int line_count = guppy_file_line_count(file_name) == 0;
    guppy_assert(line_count != -1, "guppy_file_line_count had an issue while trying to open the file.");
    return line_count == 0;
}

int guppy_file_line_count(const char *file_name) {
    FILE *fp;
    int c, line_count = 0;

    fp = fopen(file_name, "r");
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

        return 0;
    }

    // If the first character is anything other than the end of the file, then we can say there is
    // at least one line in the file (even if it is a newline).
    line_count++;

    do {
        if (c == '\n') {
            line_count++;
        }
    } while ((c = fgetc(fp)) != EOF);

    fclose(fp);
    return line_count;
}

char *guppy_file_read(const char *file_name) {
    FILE *fp;
    char *buffer;
    long file_size;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        return NULL;
    }

    // TODO: This is not portable. Make a function.
    // Determine how many bytes are in the file.
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    buffer = (char*) malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(fp);
        return NULL;
    }

    if (fread(buffer, sizeof(char), file_size, fp) != file_size) {
        free(buffer);
        fclose(fp);
        return NULL;
    }

    buffer[file_size] = '\0';

    fclose(fp);
    return buffer;
}

char **guppy_file_read_lines(const char *file_name) {
    FILE *fp;
    char **lines;
    char *line;
    size_t line_size = 0;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        #ifdef GUPPY_DEBUG
        printf("Failed to open file %s\n", file_name);
        #endif
        
        return NULL;
    }

    int line_count = guppy_file_line_count(file_name);
    if (line_count == 0) {
        #ifdef GUPPY_DEBUG
        printf("No lines found in file %s\n", file_name);
        #endif
        
        return NULL;
    }

    lines = malloc(line_count * sizeof(char *) + 1);
    assert(lines != NULL);

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line, &line_size, fp);

        if (read == EOF) break;

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

char **guppy_file_read_lines_keep_newlines(const char *file_name) {
    FILE *fp;
    char **lines;
    char *line;
    size_t line_size = 0;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Failed to open file %s\n", file_name);
        return NULL;
    }

    int line_count = guppy_file_line_count(file_name);
    if (line_count == 0) {
        #ifdef GUPPY_DEBUG
        printf("No lines found in file %s\n", file_name);
        #endif
        
        return NULL;
    }

    lines = malloc(line_count * sizeof(char *) + 1);
    assert(lines != NULL);

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line, &line_size, fp);

        // Add an extra byte for null termination.
        lines[i] = (char *) malloc(read * sizeof(char) + 1);
        strcpy(lines[i], line);
    }
    
    free(line);
    fclose(fp);

    lines[line_count] = NULL;
    return lines;
}

int guppy_file_write(const char *file_name, const char *text_to_write) {
    FILE *fp;

    fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Failed to open file %s\n", file_name);
        return 1;
    }

    fprintf(fp, "%s", text_to_write);

    fclose(fp);
    return 0;
}

#endif // GUPPY_H
