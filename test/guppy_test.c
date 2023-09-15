#include <float.h>
#include <limits.h>
#include "../src/guppy.h"

int main(void) {
    const char *file_name = "./test/foo.txt";
    
    char **lines_in_file = guppy_file_read_lines(file_name, false);
    guppy_print_array_string(lines_in_file, 3, "the file lines");

    return 0;
}
