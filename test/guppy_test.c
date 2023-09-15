#include <float.h>
#include <limits.h>
#include "../src/guppy.h"

int main(void) {
    const char *file_name = "./test/foo.txt";
    char **file_lines = guppy_file_read_lines(file_name, false);
    guppy_print_array_string(file_lines, 3, "foo.txt lines");

    free(file_lines);
    return 0;
}
