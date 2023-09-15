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

void guppy_assert(bool pass_condition, const char *failure_message);

// Print full arrays -------------------------------------------------------------------------------
void guppy_print_array_bool(bool array[], size_t length, const char *array_name);
void guppy_print_array_char(char array[], size_t length, const char *array_name);
void guppy_print_array_double(double array[], size_t length, const char *array_name);
void guppy_print_array_float(float array[], size_t length, const char *array_name);
void guppy_print_array_int(int array[], size_t length, const char *array_name);
void guppy_print_array_long(long array[], size_t length, const char *array_name);
void guppy_print_array_string(char *array[], size_t length, const char *array_name);

// Print array slices [start, end) -----------------------------------------------------------------
void guppy_print_array_slice_bool(bool array[], size_t start, size_t end, const char *array_name);
void guppy_print_array_slice_char(char array[], size_t start, size_t end, const char *array_name);
void guppy_print_array_slice_double(double array[], size_t start, size_t end, const char *array_name);
void guppy_print_array_slice_float(float array[], size_t start, size_t end, const char *array_name);
void guppy_print_array_slice_int(int array[], size_t start, size_t end, const char *array_name);
void guppy_print_array_slice_long(long array[], size_t start, size_t end, const char *array_name);

// File operations ---------------------------------------------------------------------------------

int    guppy_file_line_count(const char *file_name);
char  *guppy_file_read(const char *file_name);
char **guppy_file_read_lines(const char *file_name, const bool should_keep_newlines);
int    guppy_file_write(const char *file_name, const char *text_to_write);

/**************************************************************************************************
 * Internal implementation                                                                        *
 **************************************************************************************************/

void guppy_assert(bool pass_condition, const char *failure_message) {
    printf("not implemented\n");
}

// Print full arrays -------------------------------------------------------------------------------

void guppy_print_array_bool(bool array[], size_t length, const char *array_name) {
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

void guppy_print_array_char(char array[], size_t length, const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%c", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_array_double(double array[], size_t length, const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%.17f", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_array_float(float array[], size_t length, const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%f", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_array_int(int array[], size_t length, const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%d", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_array_long(long array[], size_t length, const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        printf("%ld", array[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

void guppy_print_array_string(char *array[], size_t length, const char *array_name) {
    printf("%s: [", array_name);
    for (size_t i = 0; i < length; i++) {
        size_t j = 0;
        printf("\"");
        while (array[i][j] != '\0') {
            printf("%c", array[i][j]);
            j++;
        }
        printf("\"");
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

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
        printf("%c", array[i]);
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

int guppy_file_line_count(const char *file_name) {
    FILE *fp;
    int c, line_count = 0;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    c = fgetc(fp);
    if (c == EOF) return 0;

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

char **guppy_file_read_lines(const char *file_name, const bool should_keep_newlines) {
    FILE *fp;
    char **lines;
    char *line;
    size_t line_size = 0;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        return NULL;
    }

    int line_count = guppy_file_line_count(file_name);
    lines = malloc(line_count * sizeof(char *));
    assert(lines != NULL);

    for (int i = 0; i < line_count; i++) {
        ssize_t read = getline(&line, &line_size, fp);

        // This happens if the last line is the end of the file.
        if (read == EOF) break;

        lines[i] = (char *) malloc(read * sizeof(char) + 1);
        if (should_keep_newlines) {
            strncpy(lines[i], line, read);
        } else {
            strncpy(lines[i], line, read - 1);
        }
        lines[i][read] = '\0';
    }

    free(line);
    fclose(fp);
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
