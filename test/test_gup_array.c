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
    { // bool
        GupArrayBool bs = gup_array_bool();
        
        assert(bs.capacity == 256);
    }

    { // char
        GupArrayChar cs = gup_array_char();
        
        assert(cs.capacity == 256);
    }

    { // double
        GupArrayDouble ds = gup_array_double();
        
        assert(ds.capacity == 256);
    }

    { // float
        GupArrayFloat fs = gup_array_float();
        
        assert(fs.capacity == 256);
    }

    { // int
        GupArrayInt is = gup_array_int();
        
        assert(is.capacity == 256);
    }

    { // long
        GupArrayLong ls = gup_array_long();
        
        assert(ls.capacity == 256);
    }

    { // short
        GupArrayShort ss = gup_array_short();
        
        assert(ss.capacity == 256);
    }
}

void test_new_gup_array_has_zero_count(void) {
    { // bool
        GupArrayBool bs = gup_array_bool();

        assert(bs.count == 0);
    }

    { // char
        GupArrayChar cs = gup_array_char();

        assert(cs.count == 0);
    }

    { // double
        GupArrayDouble ds = gup_array_double();

        assert(ds.count == 0);
    }

    { // float
        GupArrayFloat fs = gup_array_float();

        assert(fs.count == 0);
    }

    { // int
        GupArrayInt is = gup_array_int();

        assert(is.count == 0);
    }

    { // long
        GupArrayLong ls = gup_array_long();

        assert(ls.count == 0);
    }

    { // short
        GupArrayShort ss = gup_array_short();

        assert(ss.count == 0);
    }
}

void test_new_gup_array_has_non_null_data(void) {
    { // bool
        GupArrayBool bs = gup_array_bool();

        assert(bs.data != NULL);
    }

    { // char
        GupArrayChar cs = gup_array_char();

        assert(cs.data != NULL);
    }

    { // double
        GupArrayDouble ds = gup_array_double();

        assert(ds.data != NULL);
    }

    { // float
        GupArrayFloat fs = gup_array_float();

        assert(fs.data != NULL);
    }

    { // int
        GupArrayInt is = gup_array_int();

        assert(is.data != NULL);
    }

    { // long
        GupArrayLong ls = gup_array_long();

        assert(ls.data != NULL);
    }

    { // short
        GupArrayShort ss = gup_array_short();

        assert(ss.data != NULL);
    }
}

void test_two_empty_gup_arrays_are_equal(void) {
    { // bool
        GupArrayBool xs = gup_array_bool();
        GupArrayBool ys = gup_array_bool();

        assert(gup_array_eq_bool(xs, ys) == true);
    }

    { // char
        GupArrayChar xs = gup_array_char();
        GupArrayChar ys = gup_array_char();

        assert(gup_array_eq_char(xs, ys) == true);
    }

    { // double
        GupArrayDouble xs = gup_array_double();
        GupArrayDouble ys = gup_array_double();

        assert(gup_array_eq_double(xs, ys) == true);
    }

    { // float
        GupArrayFloat xs = gup_array_float();
        GupArrayFloat ys = gup_array_float();

        assert(gup_array_eq_float(xs, ys) == true);
    }

    { // int
        GupArrayInt xs = gup_array_int();
        GupArrayInt ys = gup_array_int();

        assert(gup_array_eq_int(xs, ys) == true);
    }

    { // long
        GupArrayLong xs = gup_array_long();
        GupArrayLong ys = gup_array_long();

        assert(gup_array_eq_long(xs, ys) == true);
    }

    { // short
        GupArrayShort xs = gup_array_short();
        GupArrayShort ys = gup_array_short();

        assert(gup_array_eq_short(xs, ys) == true);
    }
}

void test_one_empty_one_populated_are_unequal(void) {
    { // bool
        GupArrayBool xs = gup_array_bool();
        GupArrayBool ys = gup_array_from_bool(static_bs, gup_array_size(static_bs));

        assert(gup_array_eq_bool(xs, ys) == false);
    }

    { // char
        GupArrayChar xs = gup_array_char();
        GupArrayChar ys = gup_array_from_char(static_cs, gup_array_size(static_cs));

        assert(gup_array_eq_char(xs, ys) == false);
    }

    { // double
        GupArrayDouble xs = gup_array_double();
        GupArrayDouble ys = gup_array_from_double(static_ds, gup_array_size(static_ds));

        assert(gup_array_eq_double(xs, ys) == false);
    }

    { // float
        GupArrayFloat xs = gup_array_float();
        GupArrayFloat ys = gup_array_from_float(static_fs, gup_array_size(static_fs));

        assert(gup_array_eq_float(xs, ys) == false);
    }

    { // int
        GupArrayInt xs = gup_array_int();
        GupArrayInt ys = gup_array_from_int(static_is, gup_array_size(static_is));

        assert(gup_array_eq_int(xs, ys) == false);
    }

    { // long
        GupArrayLong xs = gup_array_long();
        GupArrayLong ys = gup_array_from_long(static_ls, gup_array_size(static_ls));

        assert(gup_array_eq_long(xs, ys) == false);
    }

    { // short
        GupArrayShort xs = gup_array_short();
        GupArrayShort ys = gup_array_from_short(static_ss, gup_array_size(static_ss));

        assert(gup_array_eq_short(xs, ys) == false);
    }
}

void test_gup_array(void) {
    test_new_gup_array_has_default_capacity();
    test_new_gup_array_has_zero_count();
    test_new_gup_array_has_non_null_data();
    test_two_empty_gup_arrays_are_equal();
    test_one_empty_one_populated_are_unequal();

    #ifdef GUPPY_VERBOSE
    printf("All gup_array tests passed!\n");
    #endif // GUPPY_VERBOSE
}
