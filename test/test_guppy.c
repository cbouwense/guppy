#include <float.h>
#include <limits.h>

// #define GUPPY_VERBOSE
// #define GUPPY_DEBUG_MEMORY
#include "../src/guppy.h"

#include "./test_gup_file.c"
#include "./test_gup_print_array_string.c"
#include "./test_gup_settings.c"
#include "./test_gup_string.c"
#include "./test_gup_sv.c"

void run_all_guppy_tests(void) {
    test_gup_file();
    // test_gup_print_array_string();
    test_gup_settings();
    test_gup_string();
    test_gup_sv();
}

void _reset_settings_file(void) {
    const bool result = gup_file_write("# This is a TOML file\n\ntitle = \"guppy.h\"\nauthor = \"Christian Bouwense\"\n\n[database]\nserver = \"localhost\"\nport = 5432\n", "./resources/settings.toml");

    gup_assert(result, "Encountered an error while resetting the settings file.\n");
}

int main(void) {
    _reset_settings_file();
    run_all_guppy_tests();

    #ifdef GUPPY_DEBUG_MEMORY
    _gup_memory_print();
    #endif

    _reset_settings_file();
    printf("All tests passed!\n");
    return 0;
}
