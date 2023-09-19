#include <float.h>
#include <limits.h>

// #define GUPPY_DEBUG
// #define GUPPY_DEBUG_MEMORY
#include "../src/guppy.h"

#include "./test_gup_file_read_lines_keep_newlines.c"
#include "./test_gup_file_read_lines.c"
#include "./test_gup_file_line_count.c"
#include "./test_gup_print_array_string.c"
#include "./test_gup_settings_get.c"

void run_all_guppy_tests(void) {
    // test_gup_file_line_count();
    // test_gup_file_read_lines();
    // test_gup_file_read_lines_keep_newlines();
    // test_gup_print_array_string();
    test_gup_settings_get();
}

int main(void) {
    run_all_guppy_tests();

    return 0;
}
