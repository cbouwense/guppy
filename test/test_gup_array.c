#include "../src/guppy.h"

bool negate(bool b) {
    return !b;
}

bool is_false(bool b) {
    return !b;
}

bool and(bool a, bool b) {
    return a && b;
}

bool or(bool a, bool b) {
    return a || b;
}

char add_one(char c) {
    return c + 1;
}

bool static_bs[] = {true, false, true};
char static_cs[] = {'a', 'b', 'c'};
double static_ds[] = {17.38, 133.7, 0.42};
float static_fs[] = {17.38f, 133.7f, 0.42f};
int static_is[] = {1738, 1337, 42};
long static_ls[] = {1738L, 1337L, 42L};
short static_ss[] = {1738, 1337, 42};

void test_new_gup_array_has_default_capacity(void) {
    GupArrayInt xs = gup_array_int();

    assert(xs.capacity == 256);

    free(xs.data);
}

void test_new_gup_array_has_zero_count(void) {
    GupArrayShort xs = gup_array_short();

    assert(xs.count == 0);

    free(xs.data);
}

void test_new_gup_array_has_non_null_data(void) {
    GupArrayBool xs = gup_array_bool();

    assert(xs.data != NULL);

    free(xs.data);
}

void test_two_empty_gup_arrays_are_equal(void) {
    GupArrayFloat xs = gup_array_float();
    GupArrayFloat ys = gup_array_float();

    assert(gup_array_eq_float(xs, ys) == true);

    free(xs.data);
    free(ys.data);
}

void test_one_empty_one_populated_are_unequal(void) {
    GupArrayChar xs = gup_array_char();
    GupArrayChar ys = gup_array_from_char(static_cs, gup_array_size(static_cs));

    assert(gup_array_eq_char(xs, ys) == false);
    
    free(xs.data);
    free(ys.data);
}

void test_a_gup_array_is_equal_to_itself(void) {
    GupArrayShort xs = gup_array_short();

    assert(gup_array_eq_short(xs, xs));

    free(xs.data);
}

void test_equivalent_gup_arrays_are_equal(void) {
    GupArrayDouble xs = gup_array_from_double(static_ds, gup_array_size(static_ds));
    GupArrayDouble ys = gup_array_double();
    gup_array_append_double(&ys, static_ds[0]);
    gup_array_append_double(&ys, static_ds[1]);
    gup_array_append_double(&ys, static_ds[2]);

    assert(gup_array_eq_double(xs, ys) == true);

    free(xs.data);
    free(ys.data);
}

void test_symmetric_gup_array_args_are_equal(void) {
    GupArrayBool xs = gup_array_from_bool(static_bs, gup_array_size(static_bs));
    GupArrayBool ys = gup_array_from_bool(static_bs, gup_array_size(static_bs));

    assert(gup_array_eq_bool(xs, ys) == true);
    assert(gup_array_eq_bool(ys, xs) == true);

    free(xs.data);
    free(ys.data);
}

void test_equivalent_but_differently_sized_gup_arrays_are_unequal(void) {
    GupArrayChar xs = gup_array_from_char(static_cs, gup_array_size(static_cs));
    GupArrayChar ys = gup_array_from_char(static_cs, gup_array_size(static_cs));
    gup_array_append_char(&ys, false);

    assert(gup_array_eq_char(xs, ys) == false);

    free(xs.data);
    free(ys.data);
}

void test_one_append_one_prepend_orders_correctly(void) {
    GupArrayInt xs = gup_array_int();
    
    gup_array_append_int(&xs, static_is[0]);
    gup_array_prepend_int(&xs, static_is[1]);

    assert(xs.data[0] == static_is[1]);
    assert(xs.data[1] == static_is[0]);

    free(xs.data);
}


void test_gup_array(void) {
    test_new_gup_array_has_default_capacity();
    test_new_gup_array_has_zero_count();
    test_new_gup_array_has_non_null_data();
    test_two_empty_gup_arrays_are_equal();
    test_one_empty_one_populated_are_unequal();
    test_a_gup_array_is_equal_to_itself();
    test_equivalent_gup_arrays_are_equal();
    test_symmetric_gup_array_args_are_equal();
    test_equivalent_but_differently_sized_gup_arrays_are_unequal();
    test_one_append_one_prepend_orders_correctly();

    #ifdef GUPPY_VERBOSE
    printf("All gup_array tests passed!\n");
    #endif // GUPPY_VERBOSE
}
