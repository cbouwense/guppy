#include "../src/guppy.h"

void test_gup_set_general(void) {
    GupSetBool set = gup_set_bool_create();

    gup_assert(!gup_set_bool_contains(set, false));
    gup_assert(!gup_set_bool_contains(set, true));
    gup_assert(gup_set_bool_size(set) == 0);

    gup_set_bool_insert(&set, false);

    gup_assert(gup_set_bool_contains(set, false));
    gup_assert(!gup_set_bool_contains(set, true));
    gup_assert(gup_set_bool_size(set) == 1);

    gup_set_bool_insert(&set, true);
    
    gup_assert(gup_set_bool_contains(set, false));
    gup_assert(gup_set_bool_contains(set, true));
    gup_assert(gup_set_bool_size(set) == 2);

    gup_set_bool_remove(&set, false);

    gup_assert(!gup_set_bool_contains(set, false));
    gup_assert(gup_set_bool_contains(set, true));
    gup_assert(gup_set_bool_size(set) == 1);

    gup_set_bool_remove(&set, true);

    gup_assert(!gup_set_bool_contains(set, false));
    gup_assert(!gup_set_bool_contains(set, true));
    gup_assert(gup_set_bool_size(set) == 0);

    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);

    gup_assert(!gup_set_bool_contains(set, false));
    gup_assert(gup_set_bool_contains(set, true));
    gup_assert(gup_set_bool_size(set) == 1);
}

void test_gup_set_from_array(void) {
    { // Empty has neither
        bool *bools = NULL;
        GupSetBool set = gup_set_bool_create_from_array(bools, 0);
        
        gup_assert(!gup_set_bool_contains(set, false));
        gup_assert(!gup_set_bool_contains(set, true));
        gup_assert(gup_set_bool_size(set) == 0);
    }

    {
        bool bools[] = { false };
        GupSetBool set = gup_set_bool_create_from_array(bools, 1);
        
        gup_assert(gup_set_bool_contains(set, false));
        gup_assert(!gup_set_bool_contains(set, true));
        gup_assert(gup_set_bool_size(set) == 1);
    }

    {
        bool bools[] = { false, true, false, true, false, false, false, false };
        GupSetBool set = gup_set_bool_create_from_array(bools, gup_array_len(bools));
        
        gup_assert(gup_set_bool_contains(set, false));
        gup_assert(gup_set_bool_contains(set, true));
        gup_assert(gup_set_bool_size(set) == 2);
    }
}

void test_gup_set(void) {
    test_gup_set_general();
    test_gup_set_from_array();
}
