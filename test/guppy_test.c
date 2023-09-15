#include <float.h>
#include <limits.h>

#define GUPPY_DEBUG
#include "../src/guppy.h"

int main(void) {
    int result = guppy_file_create("./test.guppy");
    guppy_assert(result == 1, GUPPY_DEFAULT_FILE_ERROR_MESSAGE);    

    char *file_contents = guppy_file_read("./test.guppy");
    guppy_assert(file_contents != NULL, GUPPY_DEFAULT_FILE_ERROR_MESSAGE);

    result = guppy_file_write("./test.guppy", "Hello\nWorld\n!");
    guppy_assert(result == 0, GUPPY_DEFAULT_FILE_ERROR_MESSAGE);

    char **file_lines = guppy_file_read_lines("./test.guppy", false);
    guppy_assert(file_lines != NULL, GUPPY_DEFAULT_FILE_ERROR_MESSAGE);

    int file_lines_count = guppy_file_line_count("./test.guppy");
    guppy_print_array_string(file_lines, file_lines_count, "file_lines");

    return 0;
}
