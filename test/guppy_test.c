#include <float.h>
#include <limits.h>

// #define GUPPY_DEBUG
#include "../src/guppy.h"

int main(void) {
    // int result = guppy_file_create("./test.guppy");
    // guppy_assert(result == 0, GUPPY_DEFAULT_FILE_ERROR_MESSAGE);    

    // result = guppy_file_write("./test.guppy", "Hello\nHello\n!");
    // guppy_assert(result == 0, GUPPY_DEFAULT_FILE_ERROR_MESSAGE);

    // char *file_contents = guppy_file_read("./test.guppy");
    // guppy_assert(file_contents != NULL, GUPPY_DEFAULT_FILE_ERROR_MESSAGE);

    char **file_lines = guppy_file_read_lines("./test.guppy");
    guppy_assert(file_lines != NULL, GUPPY_DEFAULT_FILE_ERROR_MESSAGE);

    guppy_print_array_char(file_lines[0]);
    guppy_print_array_char(file_lines[1]);
    guppy_print_array_char(file_lines[2]);
    guppy_print_array_char(file_lines[3]);

    return 0;
}
