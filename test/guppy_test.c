#include <float.h>
#include <limits.h>

// #define GUPPY_DEBUG
#include "../src/guppy.h"

int main(void) {

    char **file_lines_wo_n = guppy_file_read_lines("./test.guppy");
    char **file_lines_with_n = guppy_file_read_lines_keep_newlines("./test.guppy");
    
    guppy_print_array_string(file_lines_wo_n);
    guppy_print_array_string(file_lines_with_n);

    return 0;
}
