#include "../src/guppy.h"

bool negate(bool b) {
    return !b;
}

bool is_leet(double d) {
    return d == (double)1337 || d == 133.7 || d == 13.37 || d == 1.337;
}

bool not_leet(double d) {
    return !is_leet(d);
}

bool is_over_9000(float f) {
    return f > 9000.0;
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
    GupArrayBool xs = gup_array_bool_create();

    assert(xs.data != NULL);

    free(xs.data);
}

void test_two_empty_gup_arrays_are_equal(void) {
    GupArrayFloat xs = gup_array_float();
    GupArrayFloat ys = gup_array_float();

    assert(gup_array_float_eq(xs, ys) == true);

    free(xs.data);
    free(ys.data);
}

void test_one_empty_one_populated_are_unequal(void) {
    GupArrayChar xs = gup_array_char();
    GupArrayChar ys = gup_array_char_from(static_cs, gup_array_size(static_cs));

    assert(gup_array_char_eq(xs, ys) == false);
    
    free(xs.data);
    free(ys.data);
}

void test_gup_array_copy_equals_original(void) {
    int static_ints[] = {1, 7, 3, 8};
    GupArrayInt dyn_ints = gup_array_int_from(static_ints, gup_array_size(static_ints));

    GupArrayInt dyn_ints_copy = gup_array_int_copy(dyn_ints);

    assert(gup_array_int_eq(dyn_ints, dyn_ints_copy));

    free(dyn_ints.data); 
    free(dyn_ints_copy.data); 
}

void test_a_gup_array_is_equal_to_itself(void) {
    GupArrayShort xs = gup_array_short();

    assert(gup_array_short_eq(xs, xs));

    free(xs.data);
}

void test_equivalent_gup_arrays_are_equal(void) {
    GupArrayDouble xs = gup_array_double_from(static_ds, gup_array_size(static_ds));
    GupArrayDouble ys = gup_array_double();
    gup_array_double_append(&ys, static_ds[0]);
    gup_array_double_append(&ys, static_ds[1]);
    gup_array_double_append(&ys, static_ds[2]);

    assert(gup_array_double_eq(xs, ys) == true);

    free(xs.data);
    free(ys.data);
}

void test_symmetric_gup_array_args_are_equal(void) {
    GupArrayBool xs = gup_array_bool_from(static_bs, gup_array_size(static_bs));
    GupArrayBool ys = gup_array_bool_from(static_bs, gup_array_size(static_bs));

    assert(gup_array_bool_eq(xs, ys) == true);
    assert(gup_array_bool_eq(ys, xs) == true);

    free(xs.data);
    free(ys.data);
}

void test_equivalent_but_differently_sized_gup_arrays_are_unequal(void) {
    GupArrayChar xs = gup_array_char_from(static_cs, gup_array_size(static_cs));
    GupArrayChar ys = gup_array_char_from(static_cs, gup_array_size(static_cs));
    gup_array_char_append(&ys, false);

    assert(gup_array_char_eq(xs, ys) == false);

    free(xs.data);
    free(ys.data);
}

void test_one_append_one_prepend_orders_correctly(void) {
    GupArrayInt xs = gup_array_int();
    
    gup_array_int_append(&xs, static_is[0]);
    gup_array_int_prepend(&xs, static_is[1]);

    assert(xs.data[0] == static_is[1]);
    assert(xs.data[1] == static_is[0]);

    free(xs.data);
}

void test_map_on_empty_produces_empty(void) {
    GupArrayBool xs = gup_array_bool_create();

    GupArrayBool ys = gup_array_bool_map(xs, negate);

    assert(gup_array_bool_eq(xs, ys));
    assert(ys.count == 0);

    free(xs.data);
    free(ys.data);
}

void test_map(void) {
    bool static_bools[] = {true, true, false};
    GupArrayBool xs = gup_array_bool_from(static_bools, gup_array_size(static_bools));

    GupArrayBool ys = gup_array_bool_map(xs, negate);

    assert(ys.data[0] == false);
    assert(ys.data[1] == false);
    assert(ys.data[2] == true);

    free(xs.data);
    free(ys.data);
}

void test_map_in_place(void) {
    char static_chars[] = {'a', 'y', 'y', 'l', 'm', 'a', 'o'};
    GupArrayChar xs = gup_array_char_from(static_chars, gup_array_size(static_chars));

    gup_array_char_map_in_place(xs, add_one);

    assert(xs.data[0] == 'b');
    assert(xs.data[1] == 'z');
    assert(xs.data[2] == 'z');
    assert(xs.data[3] == 'm');
    assert(xs.data[4] == 'n');
    assert(xs.data[5] == 'b');
    assert(xs.data[6] == 'p');

    free(xs.data);
}

void test_filter_on_empty_produces_empty(void) {
    GupArrayDouble xs = gup_array_double();

    GupArrayDouble ys = gup_array_double_filter(xs, is_leet);

    assert(ys.count == 0);

    free(xs.data);
    free(ys.data);
}

void test_filter_matches_none_returns_copy(void) {
    GupArrayDouble xs = gup_array_double();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);

    GupArrayDouble ys = gup_array_double_filter(xs, not_leet);

    assert(ys.count == 0);

    free(xs.data);
    free(ys.data);
}

void test_filter_matches_some_only_keeps_matches(void) {
    GupArrayDouble xs = gup_array_double();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 17.38);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 0.42);

    GupArrayDouble ys = gup_array_double_filter(xs, is_leet);

    assert(ys.count == 2);
    assert(ys.data[0] == 1337);
    assert(ys.data[1] == 13.37);

    free(xs.data);
    free(ys.data);
}

void test_filter_matches_all_returns_copy(void) {
    GupArrayDouble xs = gup_array_double();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);

    GupArrayDouble ys = gup_array_double_filter(xs, is_leet);

    assert(gup_array_double_eq(xs, ys));

    free(xs.data);
    free(ys.data);
}

void test_filter_in_place_on_empty_produces_empty(void) {
    GupArrayDouble xs = gup_array_double();

    gup_array_double_filter_in_place(&xs, is_leet);

    assert(xs.count == 0);

    free(xs.data);
}

void test_filter_in_place_matches_none_returns_copy(void) {
    GupArrayDouble xs = gup_array_double();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);

    GupArrayDouble ys = gup_array_double_filter(xs, not_leet);

    assert(ys.count == 0);

    free(xs.data);
    free(ys.data);
}

void test_filter_in_place_matches_some_only_keeps_matches(void) {
    GupArrayDouble xs = gup_array_double();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 17.38);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 0.42);

    GupArrayDouble ys = gup_array_double_filter(xs, is_leet);

    assert(ys.count == 2);
    assert(ys.data[0] == 1337);
    assert(ys.data[1] == 13.37);

    free(xs.data);
    free(ys.data);
}

void test_filter_in_place_matches_all_returns_copy(void) {
    GupArrayDouble xs = gup_array_double();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);

    GupArrayDouble ys = gup_array_double_filter(xs, is_leet);

    assert(gup_array_double_eq(xs, ys));

    free(xs.data);
    free(ys.data);
}

void test_gup_array_char_from_cstr(void) {
    char chars[] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
    char *str = "Hello, World!";
    GupArrayChar xs = gup_array_char_from(chars, gup_array_size(chars));

    GupArrayChar ys = gup_array_char_from_cstr(str);

    assert(gup_array_char_eq(xs, ys));

    free(xs.data);
    free(ys.data);
}

void test_gup_array_string(void) {
    GupArrayString strs = gup_array_string();

    assert(strs.count == 0);

    gup_array_string_free(strs);
}

void test_gup_array_string_from(void) {
    GupString hello = gup_array_char_from_cstr("Hello");
    GupString world = gup_array_char_from_cstr("World");
    GupString bang = gup_array_char_from_cstr("!");
    GupString cs[] = {hello, world, bang};

    GupArrayString strs = gup_array_string_from(cs, gup_array_size(cs));

    assert(strs.count == 3);

    gup_array_char_free(hello);
    gup_array_char_free(world);
    gup_array_char_free(bang);
    gup_array_string_free(strs);
}

void test_gup_array_string_copy(void) {
    GupString hello = gup_array_char_from_cstr("Hello");
    GupString world = gup_array_char_from_cstr("World");
    GupString bang = gup_array_char_from_cstr("!");
    GupString cs[] = {hello, world, bang};
    GupArrayString strs = gup_array_string_from(cs, gup_array_size(cs));

    GupArrayString strs_copy = gup_array_string_copy(strs);

    assert(gup_array_string_eq(strs, strs_copy));

    gup_array_char_free(hello);
    gup_array_char_free(world);
    gup_array_char_free(bang);
    gup_array_string_free(strs);
    gup_array_string_free(strs_copy);
}

void test_gup_array_string_append(void) {
    GupArrayChar hello = gup_array_char_from_cstr("Hello");
    GupArrayChar world = gup_array_char_from_cstr("World");
    GupArrayChar bang = gup_array_char_from_cstr("!");
    GupArrayChar char_arrays[] = {hello, world, bang};
    GupArrayString strs_from = gup_array_string_from(char_arrays, gup_array_size(char_arrays));

    GupArrayString strs = gup_array_string();
    gup_array_string_append(&strs, hello);
    gup_array_string_append(&strs, world);
    gup_array_string_append(&strs, bang);

    assert(gup_array_string_eq(strs, strs_from));

    free(hello.data);
    free(world.data);
    free(bang.data);
    gup_array_string_free(strs);
    gup_array_string_free(strs_from);
}

void test_gup_array(void) {
    test_new_gup_array_has_default_capacity();
    test_new_gup_array_has_zero_count();
    test_new_gup_array_has_non_null_data();

    test_two_empty_gup_arrays_are_equal();
    test_one_empty_one_populated_are_unequal();
    test_a_gup_array_is_equal_to_itself();
    test_gup_array_copy_equals_original();
    test_equivalent_gup_arrays_are_equal();
    test_symmetric_gup_array_args_are_equal();
    test_equivalent_but_differently_sized_gup_arrays_are_unequal();
    test_one_append_one_prepend_orders_correctly();

    test_map_on_empty_produces_empty();
    test_map();
    test_map_in_place();

    test_filter_on_empty_produces_empty();
    test_filter_matches_some_only_keeps_matches();
    test_filter_matches_all_returns_copy();
    test_filter_in_place_on_empty_produces_empty();
    test_filter_in_place_matches_none_returns_copy();
    test_filter_in_place_matches_some_only_keeps_matches();
    test_filter_in_place_matches_all_returns_copy();

    test_gup_array_char_from_cstr();

    // Strings
    test_gup_array_string();
    test_gup_array_string_from();
    test_gup_array_string_copy();
    test_gup_array_string_append();
    
    #ifdef GUPPY_VERBOSE
    printf("All gup_array tests passed!\n");
    #endif // GUPPY_VERBOSE
}
