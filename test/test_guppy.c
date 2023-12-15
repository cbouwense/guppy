#include <float.h>
#include <limits.h>

// #define GUPPY_VERBOSE
// #define GUPPY_DEBUG_MEMORY
#include "../src/guppy.h"

#include "./test_gup_array.c"
#include "./test_gup_file.c"
#include "./test_gup_print_array_string.c"
#include "./test_gup_settings.c"
#include "./test_gup_string.c"
#include "./test_gup_sv.c"

void _reset_settings_file(void) {
    const bool result = gup_file_write("# This is a TOML file\n\ntitle = \"guppy.h\"\nauthor = \"Christian Bouwense\"\n\n[database]\nserver = \"localhost\"\nport = 5432\n", "./resources/settings.toml");

    gup_assert(result, "Encountered an error while resetting the settings file.\n");
}

void run_all_guppy_tests(void) {
    _reset_settings_file();
    
    test_gup_array();
    test_gup_file();
    test_gup_print_array_string();
    test_gup_settings();
    test_gup_string();
    test_gup_sv();

    #ifdef GUPPY_DEBUG_MEMORY
    gup_memory_print();
    #endif
    
    printf("All tests passed!\n");
}

int main(void) {
    gup_operation_seconds_verbose(run_all_guppy_tests);

    return 0;
}
