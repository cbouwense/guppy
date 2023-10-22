#include <float.h>
#include <limits.h>

// #define GUPPY_VERBOSE
// #define GUPPY_DEBUG_MEMORY
#include "../src/guppy.h"

#include "./test_gup_file.c"
#include "./test_gup_print_array_string.c"
#include "./test_gup_settings.c"
#include "./test_gup_sv.c"

void run_all_guppy_tests(void) {
    test_gup_file();
    test_gup_print_array_string();
    test_gup_settings();
    test_gup_sv();
}

int main(void) {
    test_gup_file();

    #ifdef GUPPY_DEBUG_MEMORY
    _gup_memory_print();
    #endif

    printf("All tests passed!\n");
    return 0;
}
