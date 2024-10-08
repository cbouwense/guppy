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
    GupArrayInt xs = gup_array_int_create();

    gup_assert(xs.capacity == 256);

    free(xs.data);
}

void test_new_gup_array_has_zero_count(void) {
    GupArrayShort xs = gup_array_short_create();

    gup_assert(xs.count == 0);

    free(xs.data);
}

void test_new_gup_array_has_non_null_data(void) {
    GupArrayBool xs = gup_array_bool_create();

    gup_assert(xs.data != NULL);

    free(xs.data);
}

void test_two_empty_gup_arrays_are_equal(void) {
    GupArrayFloat xs = gup_array_float_create();
    GupArrayFloat ys = gup_array_float_create();

    gup_assert(gup_array_float_eq(xs, ys) == true);

    free(xs.data);
    free(ys.data);
}

void test_one_empty_one_populated_are_unequal(void) {
    GupArrayChar xs = gup_array_char_create();
    GupArrayChar ys = gup_array_char_create_from_array(static_cs, gup_array_len(static_cs));

    gup_assert(gup_array_char_eq(xs, ys) == false);
    
    free(xs.data);
    free(ys.data);
}

void test_gup_array_copy_equals_original(void) {
    int static_ints[] = {1, 7, 3, 8};
    GupArrayInt dyn_ints = gup_array_int_create_from_array(static_ints, gup_array_len(static_ints));

    GupArrayInt dyn_ints_copy = gup_array_int_copy(dyn_ints);

    gup_assert(gup_array_int_eq(dyn_ints, dyn_ints_copy));

    free(dyn_ints.data); 
    free(dyn_ints_copy.data); 
}

void test_a_gup_array_is_equal_to_itself(void) {
    GupArrayShort xs = gup_array_short_create();

    gup_assert(gup_array_short_eq(xs, xs));

    free(xs.data);
}

void test_equivalent_gup_arrays_are_equal(void) {
    GupArrayDouble xs = gup_array_double_create_from_array(static_ds, gup_array_len(static_ds));
    GupArrayDouble ys = gup_array_double_create();
    gup_array_double_append(&ys, static_ds[0]);
    gup_array_double_append(&ys, static_ds[1]);
    gup_array_double_append(&ys, static_ds[2]);

    gup_assert(gup_array_double_eq(xs, ys) == true);

    free(xs.data);
    free(ys.data);
}

void test_symmetric_gup_array_args_are_equal(void) {
    GupArrayBool xs = gup_array_bool_create_from_array(static_bs, gup_array_len(static_bs));
    GupArrayBool ys = gup_array_bool_create_from_array(static_bs, gup_array_len(static_bs));

    gup_assert(gup_array_bool_eq(xs, ys) == true);
    gup_assert(gup_array_bool_eq(ys, xs) == true);

    free(xs.data);
    free(ys.data);
}

void test_equivalent_but_differently_sized_gup_arrays_are_unequal(void) {
    GupArrayChar xs = gup_array_char_create_from_array(static_cs, gup_array_len(static_cs));
    GupArrayChar ys = gup_array_char_create_from_array(static_cs, gup_array_len(static_cs));
    gup_array_char_append(&ys, 'c');

    gup_assert(gup_array_char_eq(xs, ys) == false);

    free(xs.data);
    free(ys.data);
}

void test_one_append_one_prepend_orders_correctly(void) {
    GupArrayInt xs = gup_array_int_create();
    
    gup_array_int_append(&xs, static_is[0]);
    gup_array_int_prepend(&xs, static_is[1]);

    gup_assert(xs.data[0] == static_is[1]);
    gup_assert(xs.data[1] == static_is[0]);

    free(xs.data);
}

void test_map_on_empty_produces_empty(void) {
    GupArrayBool xs = gup_array_bool_create();

    GupArrayBool ys = gup_array_bool_map(xs, negate);

    gup_assert(gup_array_bool_eq(xs, ys));
    gup_assert(ys.count == 0);

    free(xs.data);
    free(ys.data);
}

void test_map(void) {
    bool static_bools[] = {true, true, false};
    GupArrayBool xs = gup_array_bool_create_from_array(static_bools, gup_array_len(static_bools));

    GupArrayBool ys = gup_array_bool_map(xs, negate);

    gup_assert(ys.data[0] == false);
    gup_assert(ys.data[1] == false);
    gup_assert(ys.data[2] == true);

    free(xs.data);
    free(ys.data);
}

// void _remove_trailing_newline(GupString *str) {
//     if (str->data[str->count-1] == '\n') {
//         str->count--;
//     }
// }

void test_map_in_place(void) {
    { // chars
        char static_chars[] = {'a', 'y', 'y', 'l', 'm', 'a', 'o'};
        GupArrayChar xs = gup_array_char_create_from_array(static_chars, gup_array_len(static_chars));

        gup_array_char_map_in_place(&xs, add_one);

        gup_assert(xs.data[0] == 'b');
        gup_assert(xs.data[1] == 'z');
        gup_assert(xs.data[2] == 'z');
        gup_assert(xs.data[3] == 'm');
        gup_assert(xs.data[4] == 'n');
        gup_assert(xs.data[5] == 'b');
        gup_assert(xs.data[6] == 'p');

        free(xs.data);
    }

    { // string array
        GupArrayString xs = gup_array_string_create();
        gup_array_string_append_cstr(&xs, "im\n");
        gup_array_string_append_cstr(&xs, "like\n");
        gup_array_string_append_cstr(&xs, "hey\n");
        gup_array_string_append_cstr(&xs, "whats\n");
        gup_array_string_append_cstr(&xs, "up\n");
        gup_array_string_append_cstr(&xs, "hello\n");

        gup_array_string_map_in_place(&xs, _remove_trailing_newline);

        gup_assert(gup_string_eq_cstr(xs.data[0], "im"));
        gup_assert(gup_string_eq_cstr(xs.data[1], "like"));
        gup_assert(gup_string_eq_cstr(xs.data[2], "hey"));
        gup_assert(gup_string_eq_cstr(xs.data[3], "whats"));
        gup_assert(gup_string_eq_cstr(xs.data[4], "up"));
        gup_assert(gup_string_eq_cstr(xs.data[5], "hello"));

        gup_array_string_destroy(xs);
    }
}

void test_filter_on_empty_produces_empty(void) {
    GupArrayDouble xs = gup_array_double_create();

    GupArrayDouble ys = gup_array_double_filter(xs, is_leet);

    gup_assert(ys.count == 0);

    free(xs.data);
    free(ys.data);
}

void test_filter_matches_none_returns_copy(void) {
    GupArrayDouble xs = gup_array_double_create();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);

    GupArrayDouble ys = gup_array_double_filter(xs, not_leet);

    gup_assert(ys.count == 0);

    free(xs.data);
    free(ys.data);
}

void test_filter_matches_some_only_keeps_matches(void) {
    GupArrayDouble xs = gup_array_double_create();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 17.38);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 0.42);

    GupArrayDouble ys = gup_array_double_filter(xs, is_leet);

    gup_assert(ys.count == 2);
    gup_assert(ys.data[0] == 1337);
    gup_assert(ys.data[1] == 13.37);

    free(xs.data);
    free(ys.data);
}

void test_filter_matches_all_returns_copy(void) {
    GupArrayDouble xs = gup_array_double_create();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);

    GupArrayDouble ys = gup_array_double_filter(xs, is_leet);

    gup_assert(gup_array_double_eq(xs, ys));

    free(xs.data);
    free(ys.data);
}

void test_filter_in_place_on_empty_produces_empty(void) {
    GupArrayDouble xs = gup_array_double_create();

    gup_array_double_filter_in_place(&xs, is_leet);

    gup_assert(xs.count == 0);

    free(xs.data);
}

void test_filter_in_place_matches_none_returns_copy(void) {
    GupArrayDouble xs = gup_array_double_create();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);

    GupArrayDouble ys = gup_array_double_filter(xs, not_leet);

    gup_assert(ys.count == 0);

    free(xs.data);
    free(ys.data);
}

void test_filter_in_place_matches_some_only_keeps_matches(void) {
    GupArrayDouble xs = gup_array_double_create();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 17.38);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 0.42);

    GupArrayDouble ys = gup_array_double_filter(xs, is_leet);

    gup_assert(ys.count == 2);
    gup_assert(ys.data[0] == 1337);
    gup_assert(ys.data[1] == 13.37);

    free(xs.data);
    free(ys.data);
}

void test_filter_in_place_matches_all_returns_copy(void) {
    GupArrayDouble xs = gup_array_double_create();
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);
    gup_array_double_append(&xs, 1337);
    gup_array_double_append(&xs, 133.7);
    gup_array_double_append(&xs, 13.37);
    gup_array_double_append(&xs, 1.337);

    GupArrayDouble ys = gup_array_double_filter(xs, is_leet);

    gup_assert(gup_array_double_eq(xs, ys));

    free(xs.data);
    free(ys.data);
}

void test_gup_array_char_create_from_cstr(void) {
    char chars[] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
    char *str = "Hello, World!";

    GupArrayChar xs = gup_array_char_create_from_array(chars, gup_array_len(chars));
    GupArrayChar ys = gup_array_char_create_from_cstr(str);

    gup_assert(gup_array_char_eq(xs, ys));

    free(xs.data);
    free(ys.data);
}

void test_gup_array_string_create(void) {
    GupArrayString strs = gup_array_string_create();

    gup_assert(strs.count == 0);

    gup_array_string_destroy(strs);
}

void test_gup_array_string_create_from_array(void) {
    GupString hello = gup_array_char_create_from_cstr("Hello");
    GupString world = gup_array_char_create_from_cstr("World");
    GupString bang = gup_array_char_create_from_cstr("!");
    GupString cs[] = {hello, world, bang};

    GupArrayString strs = gup_array_string_create_from_array(cs, gup_array_len(cs));

    gup_assert(strs.count == 3);

    gup_array_char_destroy(hello);
    gup_array_char_destroy(world);
    gup_array_char_destroy(bang);
    gup_array_string_destroy(strs);
}

void test_gup_array_string_copy(void) {
    GupString hello = gup_array_char_create_from_cstr("Hello");
    GupString world = gup_array_char_create_from_cstr("World");
    GupString bang = gup_array_char_create_from_cstr("!");
    GupString cs[] = {hello, world, bang};
    GupArrayString strs = gup_array_string_create_from_array(cs, gup_array_len(cs));

    GupArrayString strs_copy = gup_array_string_copy(strs);

    gup_assert(gup_array_string_eq(strs, strs_copy));

    gup_array_char_destroy(hello);
    gup_array_char_destroy(world);
    gup_array_char_destroy(bang);
    gup_array_string_destroy(strs);
    gup_array_string_destroy(strs_copy);
}

void test_gup_array_string_append(void) {
    GupArrayChar hello = gup_array_char_create_from_cstr("Hello");
    GupArrayChar world = gup_array_char_create_from_cstr("World");
    GupArrayChar bang = gup_array_char_create_from_cstr("!");
    GupArrayChar char_arrays[] = {hello, world, bang};
    GupArrayString strs_create_from = gup_array_string_create_from_array(char_arrays, gup_array_len(char_arrays));

    GupArrayString strs = gup_array_string_create();
    gup_array_string_append(&strs, hello);
    gup_array_string_append(&strs, world);
    gup_array_string_append(&strs, bang);

    gup_assert(gup_array_string_eq(strs, strs_create_from));

    free(hello.data);
    free(world.data);
    free(bang.data);
    gup_array_string_destroy(strs);
    gup_array_string_destroy(strs_create_from);
}

void test_gup_array_contains(void) {
    { // Empty arrays never contain anything
        GupArrayBool bs = gup_array_bool_create();
        gup_assert(gup_array_bool_contains(bs, true) == false);
        gup_assert(gup_array_bool_contains(bs, false) == false);
        
        GupArrayPtr ps = gup_array_ptr_create();
        gup_assert(gup_array_ptr_contains(ps, (void*)NULL) == false);
        gup_assert(gup_array_ptr_contains(ps, (void*)0x12345678) == false);

        gup_array_bool_destroy(bs);
        gup_array_ptr_destroy(ps);
    }

    { // Can find appended items
        GupArrayShort shorts = gup_array_short_create();
        gup_array_short_append(&shorts, 1);
        gup_array_short_append(&shorts, 7);
        gup_array_short_append(&shorts, 38);

        gup_assert(gup_array_short_contains(shorts, 0) == false);
        gup_assert(gup_array_short_contains(shorts, 1) == true);
        gup_assert(gup_array_short_contains(shorts, 2) == false);
        gup_assert(gup_array_short_contains(shorts, 7) == true);
        gup_assert(gup_array_short_contains(shorts, 37) == false);
        gup_assert(gup_array_short_contains(shorts, 38) == true);

        gup_array_short_destroy(shorts);
    }

    { // Can find regular array items
        float float_array[3] = {0.0f, 13.37f, FLT_MAX};
        GupArrayFloat floats = gup_array_float_create_from_array(float_array, 3);

        gup_assert(gup_array_float_contains(floats, 0.1f) == false);
        gup_assert(gup_array_float_contains(floats, 0.0f) == true);
        gup_assert(gup_array_float_contains(floats, 13.377f) == false);
        gup_assert(gup_array_float_contains(floats, 13.37f) == true);
        gup_assert(gup_array_float_contains(floats, FLT_MIN) == false);
        gup_assert(gup_array_float_contains(floats, FLT_MAX) == true);

        gup_array_float_destroy(floats);
    }

    int int_array[2] = {17, 38};
    GupArrayInt ints = gup_array_int_create_from_array(int_array, 2);
    
    gup_assert(gup_array_int_contains(ints, 1337) == false);
    gup_assert(gup_array_int_contains(ints, 17) == true);
    gup_assert(gup_array_int_contains(ints, 38) == true);
    gup_assert(gup_array_int_contains(ints, 42) == false);

    gup_array_int_prepend(&ints, 1337);
    gup_array_int_append(&ints, 42);

    gup_assert(gup_array_int_contains(ints, 1337) == true);
    gup_assert(gup_array_int_contains(ints, 17) == true);
    gup_assert(gup_array_int_contains(ints, 38) == true);
    gup_assert(gup_array_int_contains(ints, 42) == true);

    gup_array_int_destroy(ints);
}

bool is_undercase(char c) {
    return c >= 97 && c <= 122;
}

bool is_the_answer(double d) {
    return d == 42.0;
}

bool is_a_floating_answer(float f) {
    return ( 
        f == 0.42f ||
        f == 4.2f ||
        f == 42
    );
}

bool is_not_a_floating_answer(float f) {
    return !is_a_floating_answer(f);
}

void test_gup_array_find(void) {
    { // Empty arrays don't find anything
        GupArrayChar chars = gup_array_char_create();
        char found = '\0';

        bool result = gup_array_char_find(chars, is_undercase, &found);

        gup_assert(result == false);
        gup_assert(found == '\0');

        gup_array_char_destroy(chars);
    }

    { // Arrays without elements but not the needle don't find it
        GupArrayDouble doubles = gup_array_double_create();
        double found = 0.0;

        gup_array_double_append(&doubles, 13.37);
        gup_array_double_append(&doubles, 17.38);
        
        bool result = gup_array_double_find(doubles, is_the_answer, &found);

        gup_assert(result == false);
        gup_assert(found == 0.0);

        gup_array_double_destroy(doubles);
    }

    GupArrayFloat floats = gup_array_float_create();
    float found = 0.0;

    gup_array_float_append(&floats, 13.37f);
    gup_array_float_append(&floats, 4.2f);
    gup_array_float_append(&floats, 17.38f);
    gup_array_float_append(&floats, 42);
    
    bool result = gup_array_float_find(floats, is_a_floating_answer, &found);

    gup_assert(result == true);
    gup_assert(found == 4.2f);

    gup_array_float_prepend(&floats, 0.42f);
    result = gup_array_float_find(floats, is_a_floating_answer, &found);

    gup_assert(result == true);
    gup_assert(found == 0.42f);


    gup_array_float_filter_in_place(&floats, is_not_a_floating_answer);
    result = gup_array_float_find(floats, is_a_floating_answer, &found);

    gup_assert(result == false);
    gup_assert(found == 0.42f); // the value of found will be unchanged from the previous successful find.

    gup_array_float_destroy(floats);
}

bool is_all_undercase(GupString str) {
    for (int i = 0; i < str.count; i++) {
        if (!is_undercase(str.data[i])) {
            return false;
        }
    }
    return true;
}

void test_gup_array_string_find(void) {
    { // Empty arrays don't find anything
        GupArrayString strings = gup_array_string_create();
        GupString found = {0};

        bool result = gup_array_string_find(strings, is_all_undercase, &found);

        gup_assert(result == false);
        gup_assert(found.count == 0);

        gup_array_string_destroy(strings);
    }

    { // Arrays without acceptable elements do not produce any find
        char *string_arr[3] = {"Hello", "World", "!"};
        GupArrayString strings = gup_array_string_create_from_cstrs(string_arr, 3);
        GupString found = {0};

        bool result = gup_array_string_find(strings, is_all_undercase, &found);

        gup_assert(result == false);
        gup_assert(found.count == 0);

        gup_array_string_destroy(strings);
    }

    { // Arrays with acceptable elements produce the first one
        char *string_arr[3] = {"Hello", "world", "!"};
        GupArrayString strings = gup_array_string_create_from_cstrs(string_arr, 3);
        GupString found = {0};

        bool result = gup_array_string_find(strings, is_all_undercase, &found);

        gup_assert(result == true);
        gup_assert(gup_array_char_eq_cstr(found, "world"));

        gup_string_destroy(found);

        gup_array_string_prepend_cstr(&strings, "foo");
        result = gup_array_string_find(strings, is_all_undercase, &found);

        gup_assert(result == true);
        gup_assert(gup_array_char_eq_cstr(found, "foo"));

        gup_string_destroy(found);
        gup_array_string_destroy(strings);
    }
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

    test_gup_array_char_create_from_cstr();

    // Strings
    test_gup_array_string_create();
    test_gup_array_string_create_from_array();
    test_gup_array_string_copy();
    test_gup_array_string_append();
    
    test_gup_array_contains();
    test_gup_array_find();
    test_gup_array_string_find();

    #ifdef GUPPY_VERBOSE
    printf("All gup_array tests passed!\n");
    #endif // GUPPY_VERBOSE
}
