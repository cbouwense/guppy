#include <float.h>
#include <limits.h>

// #define GUPPY_DEBUG
#include "../src/guppy.h"

int main(void) {

    char **file_lines = guppy_file_read_lines_keep_newlines("./test.guppy");
    guppy_assert(file_lines != NULL, GUPPY_DEFAULT_FILE_ERROR_MESSAGE);

    guppy_print_array_string(file_lines);
    // guppy_print_array_char(file_lines[0]);
    // guppy_print_array_char(file_lines[1]);
    // guppy_print_array_char(file_lines[2]);
    // guppy_print_array_char(file_lines[3]);
    // guppy_print_array_char(file_lines[4]);
    // guppy_print_array_char(file_lines[5]);
    // guppy_print_array_char(file_lines[6]);

    return 0;
}
