#include "../src/guppy.h"

void test_gup_set_general_bool(void) {
    GupSetBool set = gup_set_bool_create();

    gup_assert(!gup_set_bool_has(set, false));
    gup_assert(!gup_set_bool_has(set, true));
    gup_assert(gup_set_bool_size(set) == 0);

    gup_set_bool_insert(&set, false);

    gup_assert(gup_set_bool_has(set, false));
    gup_assert(!gup_set_bool_has(set, true));
    gup_assert(gup_set_bool_size(set) == 1);

    gup_set_bool_insert(&set, true);
    
    gup_assert(gup_set_bool_has(set, false));
    gup_assert(gup_set_bool_has(set, true));
    gup_assert(gup_set_bool_size(set) == 2);

    gup_set_bool_remove(&set, false);

    gup_assert(!gup_set_bool_has(set, false));
    gup_assert(gup_set_bool_has(set, true));
    gup_assert(gup_set_bool_size(set) == 1);

    gup_set_bool_remove(&set, true);

    gup_assert(!gup_set_bool_has(set, false));
    gup_assert(!gup_set_bool_has(set, true));
    gup_assert(gup_set_bool_size(set) == 0);

    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);
    gup_set_bool_insert(&set, true);

    gup_assert(!gup_set_bool_has(set, false));
    gup_assert(gup_set_bool_has(set, true));
    gup_assert(gup_set_bool_size(set) == 1);
}

void test_gup_set_from_array_bool(void) {
    { // Empty has neither
        bool *bools = NULL;
        GupSetBool set = gup_set_bool_create_from_array(bools, 0);
        
        gup_assert(!gup_set_bool_has(set, false));
        gup_assert(!gup_set_bool_has(set, true));
        gup_assert(gup_set_bool_size(set) == 0);
    }

    {
        bool bools[] = { false };
        GupSetBool set = gup_set_bool_create_from_array(bools, 1);
        
        gup_assert(gup_set_bool_has(set, false));
        gup_assert(!gup_set_bool_has(set, true));
        gup_assert(gup_set_bool_size(set) == 1);
    }

    {
        bool bools[] = { false, true, false, true, false, false, false, false };
        GupSetBool set = gup_set_bool_create_from_array(bools, gup_array_len(bools));
        
        gup_assert(gup_set_bool_has(set, false));
        gup_assert(gup_set_bool_has(set, true));
        gup_assert(gup_set_bool_size(set) == 2);
    }
}

void test_has_is_false_before_inserting_anything(void) {
    GupSetChar set = gup_set_char_create();

    gup_assert_verbose(!gup_set_char_has(set, 'a'), "A Set thinks that it has the character 'a' even though it never has anything at all inserted.");

    gup_set_char_destroy(set);
}

void test_has_is_false_after_inserting_something_different(void) {
    GupSetChar set = gup_set_char_create();

    gup_set_char_insert(&set, 'a');

    gup_assert_verbose(!gup_set_char_has(set, 'b'), "A Set thinks that it has the character 'b' even though it only had 'a' inserted.");

    gup_set_char_destroy(set);
}

void test_has_is_true_after_inserting_something(void) {
    GupSetChar set = gup_set_char_create();

    gup_set_char_insert(&set, 'a');

    gup_assert_verbose(gup_set_char_has(set, 'a'), "A Set doesn't realize it has 'a' after it was inserted.");

    gup_set_char_destroy(set);
}

void test_sets_general_functionality(void) {
    GupSetChar set = gup_set_char_create();

    gup_set_char_insert(&set, 'a');
    gup_set_char_insert(&set, 'a');
    gup_set_char_insert(&set, 'a');
    gup_set_char_insert(&set, 'b');
    gup_set_char_insert(&set, 'b');
    gup_set_char_insert(&set, 'b');

    gup_assert_verbose(gup_set_char_has(set, 'a'), "A Set doesn't realize it has 'a' after it was inserted.");
    gup_assert_verbose(gup_set_char_has(set, 'b'), "A Set doesn't realize it has 'b' after it was inserted.");
    gup_assert_verbose(!gup_set_char_has(set, 'c'), "A Set thinks it has has 'c' but it was never inserted.");
    gup_assert(gup_set_char_size(set) == 2);

    gup_set_char_destroy(set);
}

void test_sets_huge_mode(void) {
    GupSetChar set = gup_set_char_create();

    for (char c = 0; c < 127; c++) {
        gup_set_char_insert(&set, c);
    }

    gup_assert(gup_set_char_size(set) == 127);

    for (char c = 0; c < 127; c++) {
        char reason[1024];
        sprintf(reason, "set claims to not contain %c (%d)", c, c);
        gup_assert_verbose(gup_set_char_has(set, c), reason);
    }

    gup_set_char_destroy(set);
}

void test_sets_huge_mode_double(void) {
    GupSetChar set = gup_set_char_create();

    for (char c = 0; c < 127; c++) {
        gup_set_char_insert(&set, c);
    }
    
    gup_assert(gup_set_char_size(set) == 127);

    for (char c = 0; c < 127; c++) {
        char reason[1024];
        sprintf(reason, "set claims to not contain %c (%d)", c, c);
        gup_assert_verbose(gup_set_char_has(set, c), reason);
    }

    gup_set_char_destroy(set);
}

void test_gup_set(void) {
    test_gup_set_general_bool();
    test_gup_set_from_array_bool();
    test_has_is_false_before_inserting_anything();
    test_has_is_false_after_inserting_something_different();
    test_has_is_true_after_inserting_something();
    test_sets_general_functionality();
    test_sets_huge_mode();
}
