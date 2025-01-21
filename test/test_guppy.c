#include <float.h>
#include <limits.h>

// #define GUPPY_VERBOSE
#define GUPPY_IMPLEMENTATION
#include "../src/guppy.h"

#include "./test_gup_arena.c"
#include "./test_gup_array.c"
#include "./test_gup_file.c"
#include "./test_gup_set.c"
#include "./test_gup_hashmap.c"
#include "./test_gup_settings.c"
#include "./test_gup_stack.c"
#include "./test_gup_string.c"
#include "./test_gup_cstr.c"

void reset_settings_file(void) {
    const bool result = gup_file_write_cstr("# This is a TOML file\n\ntitle = \"guppy.h\"\nauthor = \"Christian Bouwense\"\n\n[database]\nserver = \"localhost\"\nport = 5432\n", "./resources/settings.toml");

    gup_assert_verbose(result, "Encountered an error while resetting the settings file.\n");
}

int main(void) {
    reset_settings_file();

    test_gup_arena();
    test_gup_array();
    test_gup_set();
    test_gup_hashmap();
    test_gup_file();
    test_gup_settings();
    test_gup_stack();
    test_gup_string();
    test_gup_cstr();

    reset_settings_file();
    #ifdef GUPPY_DEBUG_MEMORY
    gup_memory_print();
    #endif

    printf("All tests passed!\n");

    return 0;
}
