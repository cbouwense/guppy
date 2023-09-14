/*
 * "Scrump" is a nickname for my bearded dragon. I think "Scrump Buffer" sounds funny, and therefore
 * I named this buffer module after him. This is a simple buffer implementation that utilizes the 
 * read/write "cursor" pattern.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SCRUMP_SUCCESS = 0,
    SCRUMP_ATTEMPTED_WRITE_OVERFLOW = 1,
    SCRUMP_ATTEMPTED_READ_OVERFLOW = 2,
    SCRUMP_READ_BUFFER_TOO_SMALL = 3,
} ScrumpReturnCodeType;

typedef struct scrump_char_buffer {
    char   *data;
    size_t  capacity;
    char   *read_cursor;
    char   *write_cursor;
} ScrumpCharBuffer;

typedef struct scrump_int_buffer {
    int    *data;
    size_t  capacity;
    int    *read_cursor;
    int    *write_cursor;
} ScrumpIntBuffer;

/**************************************************************************************************
 * Public API                                                                                     *
 **************************************************************************************************/

// Scrump char buffer ------------------------------------------------------------------------------

ScrumpCharBuffer     *scrump_char_buffer_create(const size_t capacity);
ScrumpReturnCodeType  scrump_char_buffer_free(ScrumpCharBuffer *buffer);
// TODO: scrump_char_buffer_expand
ScrumpReturnCodeType  scrump_char_buffer_write(ScrumpCharBuffer *buffer, const char data[], const size_t size);
ScrumpReturnCodeType  scrump_char_buffer_read(ScrumpCharBuffer *buffer, char *read_buffer, const size_t size, const size_t read_buffer_size);
void                  scrump_char_buffer_debug(const ScrumpCharBuffer *buffer, const char *buffer_name);

// Scrump int buffer -------------------------------------------------------------------------------

ScrumpIntBuffer      *scrump_int_buffer_create(const size_t capacity);
ScrumpReturnCodeType  scrump_int_buffer_free(ScrumpIntBuffer *buffer);
// TODO: scrump_int_buffer_expand
ScrumpReturnCodeType  scrump_int_buffer_write(ScrumpIntBuffer *buffer, const int data[], const size_t size);
ScrumpReturnCodeType  scrump_int_buffer_read(ScrumpIntBuffer *buffer, int *read_buffer, const size_t size);
void                  scrump_int_buffer_debug(const ScrumpIntBuffer *buffer, const char *buffer_name);

// Scrump buffer utilities -------------------------------------------------------------------------

const char *scrump_return_code_to_string(const int return_code);

/**************************************************************************************************
 * Internal implementation                                                                        *
 **************************************************************************************************/

// Scrump char buffer ------------------------------------------------------------------------------

ScrumpCharBuffer *scrump_char_buffer_create(const size_t capacity) {
    if (capacity == 0) return NULL;

    ScrumpCharBuffer *buffer = (ScrumpCharBuffer *)malloc(sizeof(ScrumpCharBuffer));

    buffer->data = (char *)malloc(sizeof(char) * capacity);
    buffer->capacity = capacity;
    buffer->read_cursor = buffer->data;
    buffer->write_cursor = buffer->data;

    return buffer;
}

ScrumpReturnCodeType scrump_char_buffer_free(ScrumpCharBuffer *buffer) {
    if (buffer != NULL) {
        free(buffer->data);
    }
    free(buffer);
    return SCRUMP_SUCCESS;
}

ScrumpReturnCodeType scrump_char_buffer_write(ScrumpCharBuffer *buffer, const char data[], const size_t size) {
    const size_t remaining_capacity = buffer->capacity - (buffer->write_cursor - buffer->data);
    if (size > remaining_capacity) return SCRUMP_ATTEMPTED_WRITE_OVERFLOW;
    
    // Intentionally not setting a null terminator. This is a buffer, not a string.
    // We null terminate on read for convenience.
    for (size_t i = 0; i < size; i++) {
        *buffer->write_cursor = data[i];
        buffer->write_cursor++;
    }

    return SCRUMP_SUCCESS;
}

ScrumpReturnCodeType scrump_char_buffer_read(ScrumpCharBuffer *buffer, char *read_buffer, const size_t size, const size_t read_buffer_size) {
    const size_t read_capacity = buffer->write_cursor - buffer->read_cursor;
    if (size > read_capacity) return SCRUMP_ATTEMPTED_READ_OVERFLOW;

    // Check that the read buffer is big enough to hold the data plus a manually added null terminator.
    if (read_buffer_size < size + 1) return SCRUMP_READ_BUFFER_TOO_SMALL;

    strncpy(read_buffer, buffer->read_cursor, size);
    // Manually null terminate the destination string.
    read_buffer[size] = '\0';

    buffer->read_cursor += size;

    return SCRUMP_SUCCESS;
}

/* 
 * TODO: when the screen is too small, the read cursor is technically aligned, but it is unclear
 * what it is aligned to. For example:
 * 
 *                         | read
 *                         v
 * data=['H', 'e', 'l', 'l', 'o', 'W
 * ', 'o', 'r', 'l', 'd', ...]
 *                         ^
 *                         | write
 * 
 * In this output it kinda looks like read is pointing to the 'l', but really it's pointing to the
 * ... that had to wrap around to the next line. For now the answer is to just make sure your
 * terminal is big enough to fit the output. But, maybe this would be interesting to fix.
 */
void scrump_char_buffer_debug(const ScrumpCharBuffer *buffer, const char *buffer_name) {
    const size_t size = buffer->write_cursor - buffer->data;
    const char *data = buffer->data;

    // For example, if the first character is 'e', it will look like `'e', `, thus 5 spaces.
    const int spaces_per_character = 5;
    // For example, the first line reads `data=['`, thus 7 spaces.
    const int offset_from_left = 7;

    const size_t read_cursor_offset = ((buffer->read_cursor - buffer->data) * spaces_per_character) + offset_from_left;
    const size_t write_cursor_offset = ((buffer->write_cursor - buffer->data) * spaces_per_character) + offset_from_left;

    printf("========== %s ==========\n", buffer_name);
    printf("| size: %zu | capacity: %zu\n", size, buffer->capacity);
    printf("--------------------------------\n");
    for(int i = 0; i < read_cursor_offset; i++) printf(" ");
    printf("| read\n");
    for(int i = 0; i < read_cursor_offset; i++) printf(" ");
    printf("v\n");
    printf("data=[");
    for (size_t i = 0; i < size; i++) {
        printf("'%c', ", data[i]);
    }
    printf("...]\n");
    
    for(int i = 0; i < write_cursor_offset; i++) printf(" ");
    printf("^\n");
    for(int i = 0; i < write_cursor_offset; i++) printf(" ");
    printf("| write\n\n");
}

// Scrump int buffer -------------------------------------------------------------------------------

ScrumpIntBuffer *scrump_int_buffer_create(const size_t capacity) {
    if (capacity == 0) return NULL;

    ScrumpIntBuffer *buffer = (ScrumpIntBuffer *)malloc(sizeof(ScrumpIntBuffer));

    buffer->data = (int *)malloc(sizeof(int) * capacity);
    buffer->capacity = capacity;
    buffer->read_cursor = buffer->data;
    buffer->write_cursor = buffer->data;

    return buffer;
}

ScrumpReturnCodeType scrump_int_buffer_free(ScrumpIntBuffer *buffer) {
    if (buffer != NULL) {
        free(buffer->data);
    }
    free(buffer);
    return SCRUMP_SUCCESS;
}

ScrumpReturnCodeType scrump_int_buffer_write(ScrumpIntBuffer *buffer, const int data[], const size_t size) {
    const size_t remaining_capacity = buffer->capacity - (buffer->write_cursor - buffer->data);
    if (size > remaining_capacity) return SCRUMP_ATTEMPTED_WRITE_OVERFLOW;

    for (size_t i = 0; i < size; i++) {
        *buffer->write_cursor = data[i];
        buffer->write_cursor++;
    }

    return SCRUMP_SUCCESS;
}

ScrumpReturnCodeType scrump_int_buffer_read(ScrumpIntBuffer *buffer, int *read_buffer, const size_t size) {
    const size_t read_capacity = buffer->write_cursor - buffer->read_cursor;
    if (size > read_capacity) return SCRUMP_ATTEMPTED_READ_OVERFLOW;

    for (size_t i = 0; i < size; i++) {
        read_buffer[i] = *buffer->read_cursor;
        buffer->read_cursor++;
    }

    return SCRUMP_SUCCESS;
}


void scrump_int_buffer_debug(const ScrumpIntBuffer *buffer, const char *buffer_name) {
    const size_t size = buffer->write_cursor - buffer->data;
    const int *data = buffer->data;

    // TODO: this only works for single digit numbers.
    const int spaces_per_int = 3;
    // For example, the first line reads `data=[`, thus 6 spaces.
    const int offset_from_left = 6;

    const size_t read_cursor_offset = ((buffer->read_cursor - buffer->data) * spaces_per_int) + offset_from_left;
    const size_t write_cursor_offset = ((buffer->write_cursor - buffer->data) * spaces_per_int) + offset_from_left;

    // TODO: It would be nice if we could calculate how many characters to print here to get a consistent width.
    printf("========== %s ==========\n", buffer_name);
    printf("| size: %zu | capacity: %zu\n", size, buffer->capacity);
    printf("--------------------------------\n");
    for(int i = 0; i < read_cursor_offset; i++) printf(" ");
    printf("| read\n");
    for(int i = 0; i < read_cursor_offset; i++) printf(" ");
    printf("v\n");
    printf("data=[");
    for (size_t i = 0; i < size; i++) {
        printf("%d, ", data[i]);
    }

    // TODO: make it so that a full buffer doesn't end with `, ]`
    if (size == buffer->capacity) printf("]\n");
    else printf("...]\n");
    
    for(int i = 0; i < write_cursor_offset; i++) printf(" ");
    printf("^\n");
    for(int i = 0; i < write_cursor_offset; i++) printf(" ");
    printf("| write\n\n");
}

// Scrump buffer utilities -------------------------------------------------------------------------

const char *scrump_return_code_to_string(const int return_code) {
    switch (return_code) {
        case SCRUMP_SUCCESS:
            return "SCRUMP_SUCCESS";
        case SCRUMP_ATTEMPTED_WRITE_OVERFLOW:
            return "SCRUMP_ATTEMPTED_WRITE_OVERFLOW";
        case SCRUMP_ATTEMPTED_READ_OVERFLOW:
            return "SCRUMP_ATTEMPTED_READ_OVERFLOW";
        case SCRUMP_READ_BUFFER_TOO_SMALL:
            return "SCRUMP_READ_BUFFER_TOO_SMALL";
        default:
            return "UNKNOWN";
    }
}
