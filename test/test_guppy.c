#include <float.h>
#include <limits.h>

// #define GUPPY_VERBOSE
#define GUPPY_IMPLEMENTATION
#include "../src/guppy.h"

#include "./test_gup_allocator_arena.c"
#include "./test_gup_allocator_bucket.c"
#include "./test_gup_array.c"
#include "./test_gup_file.c"
#include "./test_gup_set.c"
#include "./test_gup_hashmap.c"
#include "./test_gup_settings.c"
#include "./test_gup_stack.c"
#include "./test_gup_string.c"
#include "./test_gup_cstr.c"

int main(void) {
    // TODO: multi thread these
    test_gup_allocator_arena();
    test_gup_allocator_bucket();
    // test_gup_array();
    // test_gup_set();
    // test_gup_hashmap();
    // test_gup_file();
    // test_gup_settings();
    // test_gup_stack();
    // test_gup_string();
    // test_gup_cstr();

    printf("All tests passed!\n");

    return 0;
}
