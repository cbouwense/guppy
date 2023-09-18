#include <float.h>
#include <limits.h>

// #define GUPPY_DEBUG
#include "../src/guppy.h"

#include "./test_gup_file_read_lines_keep_newlines.c"
#include "./test_gup_file_read_lines.c"
#include "./test_gup_file_line_count.c"
#include "./test_gup_print_array_string.c"

void run_all_guppy_tests(void) {
    test_gup_file_line_count();
    test_gup_file_read_lines();
    test_gup_file_read_lines_keep_newlines();
    test_gup_print_array_string();
}

int main(void) {
    run_all_guppy_tests();

    return 0;
}
