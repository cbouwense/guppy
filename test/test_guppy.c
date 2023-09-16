#include <float.h>
#include <limits.h>

#define GUPPY_DEBUG
#include "../src/guppy.h"

#include "test_guppy_file_read_lines_keep_newlines.c"

int main(void) {
    // char **file_lines = guppy_file_read_lines("test/settings.toml");
    // guppy_assert(file_lines != NULL, "guppy_file_read_lines had some issues while working with settings.toml. maybe turn on GUPPY_DEBUG to see what's going on.");
    // guppy_print_array_string(file_lines);

    test_guppy_file_read_lines_keep_newlines();

    return 0;
}
