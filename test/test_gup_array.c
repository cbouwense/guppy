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
        GupArrayBool xs = gup_array_bool();

        assert(xs.capacity == 256);

        free(xs.data);
    }

    { // char
        GupArrayChar xs = gup_array_char();

        assert(xs.capacity == 256);

        free(xs.data);
    }

    { // double
        GupArrayDouble xs = gup_array_double();

        assert(xs.capacity == 256);

        free(xs.data);
    }

    { // float
        GupArrayFloat xs = gup_array_float();

        assert(xs.capacity == 256);

        free(xs.data);
    }

    { // int
        GupArrayInt xs = gup_array_int();

        assert(xs.capacity == 256);

        free(xs.data);
    }

    { // long
        GupArrayLong xs = gup_array_long();

        assert(xs.capacity == 256);

        free(xs.data);
    }

    { // short
        GupArrayShort xs = gup_array_short();

        assert(xs.capacity == 256);

        free(xs.data);
    }
}

void test_new_gup_array_has_zero_count(void) {
    { // bool
        GupArrayBool xs = gup_array_bool();

        assert(xs.count == 0);

        free(xs.data);
    }

    { // char
        GupArrayChar xs = gup_array_char();

        assert(xs.count == 0);

        free(xs.data);
    }

    { // double
        GupArrayDouble xs = gup_array_double();

        assert(xs.count == 0);

        free(xs.data);
    }

    { // float
        GupArrayFloat xs = gup_array_float();

        assert(xs.count == 0);

        free(xs.data);
    }

    { // int
        GupArrayInt xs = gup_array_int();

        assert(xs.count == 0);

        free(xs.data);
    }

    { // long
        GupArrayLong xs = gup_array_long();

        assert(xs.count == 0);

        free(xs.data);
    }

    { // short
        GupArrayShort xs = gup_array_short();

        assert(xs.count == 0);

        free(xs.data);
    }
}

void test_new_gup_array_has_non_null_data(void) {
    { // bool
        GupArrayBool xs = gup_array_bool();

        assert(xs.data != NULL);

        free(xs.data);
    }

    { // char
        GupArrayChar xs = gup_array_char();

        assert(xs.data != NULL);

        free(xs.data);
    }

    { // double
        GupArrayDouble xs = gup_array_double();

        assert(xs.data != NULL);

        free(xs.data);
    }

    { // float
        GupArrayFloat xs = gup_array_float();

        assert(xs.data != NULL);

        free(xs.data);
    }

    { // int
        GupArrayInt xs = gup_array_int();

        assert(xs.data != NULL);

        free(xs.data);
    }

    { // long
        GupArrayLong xs = gup_array_long();

        assert(xs.data != NULL);

        free(xs.data);
    }

    { // short
        GupArrayShort xs = gup_array_short();

        assert(xs.data != NULL);

        free(xs.data);
    }
}

void test_two_empty_gup_arrays_are_equal(void) {
    { // bool
        GupArrayBool xs = gup_array_bool();
        GupArrayBool ys = gup_array_bool();

        assert(gup_array_eq_bool(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // char
        GupArrayChar xs = gup_array_char();
        GupArrayChar ys = gup_array_char();

        assert(gup_array_eq_char(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // double
        GupArrayDouble xs = gup_array_double();
        GupArrayDouble ys = gup_array_double();

        assert(gup_array_eq_double(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // float
        GupArrayFloat xs = gup_array_float();
        GupArrayFloat ys = gup_array_float();

        assert(gup_array_eq_float(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // int
        GupArrayInt xs = gup_array_int();
        GupArrayInt ys = gup_array_int();

        assert(gup_array_eq_int(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // long
        GupArrayLong xs = gup_array_long();
        GupArrayLong ys = gup_array_long();

        assert(gup_array_eq_long(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // short
        GupArrayShort xs = gup_array_short();
        GupArrayShort ys = gup_array_short();

        assert(gup_array_eq_short(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }
}

void test_one_empty_one_populated_are_unequal(void) {
    { // bool
        GupArrayBool xs = gup_array_bool();
        GupArrayBool ys = gup_array_from_bool(static_bs, gup_array_size(static_bs));

        assert(gup_array_eq_bool(xs, ys) == false);
        
        free(xs.data);
        free(ys.data);
    }

    { // char
        GupArrayChar xs = gup_array_char();
        GupArrayChar ys = gup_array_from_char(static_cs, gup_array_size(static_cs));

        assert(gup_array_eq_char(xs, ys) == false);
        
        free(xs.data);
        free(ys.data);
    }

    { // double
        GupArrayDouble xs = gup_array_double();
        GupArrayDouble ys = gup_array_from_double(static_ds, gup_array_size(static_ds));

        assert(gup_array_eq_double(xs, ys) == false);
        
        free(xs.data);
        free(ys.data);
    }

    { // float
        GupArrayFloat xs = gup_array_float();
        GupArrayFloat ys = gup_array_from_float(static_fs, gup_array_size(static_fs));

        assert(gup_array_eq_float(xs, ys) == false);
        
        free(xs.data);
        free(ys.data);
    }

    { // int
        GupArrayInt xs = gup_array_int();
        GupArrayInt ys = gup_array_from_int(static_is, gup_array_size(static_is));

        assert(gup_array_eq_int(xs, ys) == false);
        
        free(xs.data);
        free(ys.data);
    }

    { // long
        GupArrayLong xs = gup_array_long();
        GupArrayLong ys = gup_array_from_long(static_ls, gup_array_size(static_ls));

        assert(gup_array_eq_long(xs, ys) == false);
        
        free(xs.data);
        free(ys.data);
    }

    { // short
        GupArrayShort xs = gup_array_short();
        GupArrayShort ys = gup_array_from_short(static_ss, gup_array_size(static_ss));

        assert(gup_array_eq_short(xs, ys) == false);
        
        free(xs.data);
        free(ys.data);
    }

}

void test_a_gup_array_is_equal_to_itself(void) {
    { // bool
        GupArrayBool xs = gup_array_bool();

        assert(gup_array_eq_bool(xs, xs));

        free(xs.data);
    }

    { // char
        GupArrayChar xs = gup_array_char();

        assert(gup_array_eq_char(xs, xs));

        free(xs.data);
    }

    { // double
        GupArrayDouble xs = gup_array_double();

        assert(gup_array_eq_double(xs, xs));

        free(xs.data);
    }

    { // float
        GupArrayFloat xs = gup_array_float();

        assert(gup_array_eq_float(xs, xs));

        free(xs.data);
    }

    { // int
        GupArrayInt xs = gup_array_int();

        assert(gup_array_eq_int(xs, xs));

        free(xs.data);
    }

    { // long
        GupArrayLong xs = gup_array_long();

        assert(gup_array_eq_long(xs, xs));

        free(xs.data);
    }

    { // short
        GupArrayShort xs = gup_array_short();

        assert(gup_array_eq_short(xs, xs));

        free(xs.data);
    }
}

void test_equivalent_gup_arrays_are_equal(void) {
    { // bool
        GupArrayBool xs = gup_array_from_bool(static_bs, gup_array_size(static_bs));
        GupArrayBool ys = gup_array_bool();
        gup_array_append_bool(&ys, static_bs[0]);
        gup_array_append_bool(&ys, static_bs[1]);
        gup_array_append_bool(&ys, static_bs[2]);

        assert(gup_array_eq_bool(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // char
        GupArrayChar xs = gup_array_from_char(static_cs, gup_array_size(static_cs));
        GupArrayChar ys = gup_array_char();
        gup_array_append_char(&ys, static_cs[0]);
        gup_array_append_char(&ys, static_cs[1]);
        gup_array_append_char(&ys, static_cs[2]);

        assert(gup_array_eq_char(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // double
        GupArrayDouble xs = gup_array_from_double(static_ds, gup_array_size(static_ds));
        GupArrayDouble ys = gup_array_double();
        gup_array_append_double(&ys, static_ds[0]);
        gup_array_append_double(&ys, static_ds[1]);
        gup_array_append_double(&ys, static_ds[2]);

        assert(gup_array_eq_double(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // float
        GupArrayFloat xs = gup_array_from_float(static_fs, gup_array_size(static_fs));
        GupArrayFloat ys = gup_array_float();
        gup_array_append_float(&ys, static_fs[0]);
        gup_array_append_float(&ys, static_fs[1]);
        gup_array_append_float(&ys, static_fs[2]);

        assert(gup_array_eq_float(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // int
        GupArrayInt xs = gup_array_from_int(static_is, gup_array_size(static_is));
        GupArrayInt ys = gup_array_int();
        gup_array_append_int(&ys, static_is[0]);
        gup_array_append_int(&ys, static_is[1]);
        gup_array_append_int(&ys, static_is[2]);

        assert(gup_array_eq_int(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // long
        GupArrayLong xs = gup_array_from_long(static_ls, gup_array_size(static_ls));
        GupArrayLong ys = gup_array_long();
        gup_array_append_long(&ys, static_ls[0]);
        gup_array_append_long(&ys, static_ls[1]);
        gup_array_append_long(&ys, static_ls[2]);

        assert(gup_array_eq_long(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }

    { // short
        GupArrayShort xs = gup_array_from_short(static_ss, gup_array_size(static_ss));
        GupArrayShort ys = gup_array_short();
        gup_array_append_short(&ys, static_ss[0]);
        gup_array_append_short(&ys, static_ss[1]);
        gup_array_append_short(&ys, static_ss[2]);

        assert(gup_array_eq_short(xs, ys) == true);

        free(xs.data);
        free(ys.data);
    }
}

void test_symmetric_gup_array_args_are_equal(void) {
    { // bool
        GupArrayBool xs = gup_array_from_bool(static_bs, gup_array_size(static_bs));
        GupArrayBool ys = gup_array_from_bool(static_bs, gup_array_size(static_bs));

        assert(gup_array_eq_bool(xs, ys) == true);
        assert(gup_array_eq_bool(ys, xs) == true);

        free(xs.data);
        free(ys.data);
    }

    { // char
        GupArrayChar xs = gup_array_from_char(static_cs, gup_array_size(static_cs));
        GupArrayChar ys = gup_array_from_char(static_cs, gup_array_size(static_cs));

        assert(gup_array_eq_char(xs, ys) == true);
        assert(gup_array_eq_char(ys, xs) == true);

        free(xs.data);
        free(ys.data);
    }

    { // double
        GupArrayDouble xs = gup_array_from_double(static_ds, gup_array_size(static_ds));
        GupArrayDouble ys = gup_array_from_double(static_ds, gup_array_size(static_ds));

        assert(gup_array_eq_double(xs, ys) == true);
        assert(gup_array_eq_double(ys, xs) == true);

        free(xs.data);
        free(ys.data);
    }

    { // float
        GupArrayFloat xs = gup_array_from_float(static_fs, gup_array_size(static_fs));
        GupArrayFloat ys = gup_array_from_float(static_fs, gup_array_size(static_fs));

        assert(gup_array_eq_float(xs, ys) == true);
        assert(gup_array_eq_float(ys, xs) == true);

        free(xs.data);
        free(ys.data);
    }

    { // int
        GupArrayInt xs = gup_array_from_int(static_is, gup_array_size(static_is));
        GupArrayInt ys = gup_array_from_int(static_is, gup_array_size(static_is));

        assert(gup_array_eq_int(xs, ys) == true);
        assert(gup_array_eq_int(ys, xs) == true);

        free(xs.data);
        free(ys.data);
    }

    { // long
        GupArrayLong xs = gup_array_from_long(static_ls, gup_array_size(static_ls));
        GupArrayLong ys = gup_array_from_long(static_ls, gup_array_size(static_ls));

        assert(gup_array_eq_long(xs, ys) == true);
        assert(gup_array_eq_long(ys, xs) == true);

        free(xs.data);
        free(ys.data);
    }

    { // short
        GupArrayShort xs = gup_array_from_short(static_ss, gup_array_size(static_ss));
        GupArrayShort ys = gup_array_from_short(static_ss, gup_array_size(static_ss));

        assert(gup_array_eq_short(xs, ys) == true);
        assert(gup_array_eq_short(ys, xs) == true);

        free(xs.data);
        free(ys.data);
    }
}

void test_equivalent_but_differently_sized_gup_arrays_are_unequal(void) {
    { // bool
        GupArrayBool xs = gup_array_from_bool(static_bs, gup_array_size(static_bs));
        GupArrayBool ys = gup_array_from_bool(static_bs, gup_array_size(static_bs));
        gup_array_append_bool(&ys, static_bs[0]);

        assert(gup_array_eq_bool(xs, ys) == false);

        free(xs.data);
        free(ys.data);
    }

    { // char
        GupArrayChar xs = gup_array_from_char(static_cs, gup_array_size(static_cs));
        GupArrayChar ys = gup_array_from_char(static_cs, gup_array_size(static_cs));
        gup_array_append_char(&ys, static_cs[0]);

        assert(gup_array_eq_char(xs, ys) == false);

        free(xs.data);
        free(ys.data);
    }

    { // double
        GupArrayDouble xs = gup_array_from_double(static_ds, gup_array_size(static_ds));
        GupArrayDouble ys = gup_array_from_double(static_ds, gup_array_size(static_ds));
        gup_array_append_double(&ys, static_ds[0]);

        assert(gup_array_eq_double(xs, ys) == false);

        free(xs.data);
        free(ys.data);
    }

    { // float
        GupArrayFloat xs = gup_array_from_float(static_fs, gup_array_size(static_fs));
        GupArrayFloat ys = gup_array_from_float(static_fs, gup_array_size(static_fs));
        gup_array_append_float(&ys, static_fs[0]);

        assert(gup_array_eq_float(xs, ys) == false);

        free(xs.data);
        free(ys.data);
    }

    { // int
        GupArrayInt xs = gup_array_from_int(static_is, gup_array_size(static_is));
        GupArrayInt ys = gup_array_from_int(static_is, gup_array_size(static_is));
        gup_array_append_int(&ys, static_is[0]);

        assert(gup_array_eq_int(xs, ys) == false);

        free(xs.data);
        free(ys.data);
    }

    { // long
        GupArrayLong xs = gup_array_from_long(static_ls, gup_array_size(static_ls));
        GupArrayLong ys = gup_array_from_long(static_ls, gup_array_size(static_ls));
        gup_array_append_long(&ys, static_ls[0]);

        assert(gup_array_eq_long(xs, ys) == false);

        free(xs.data);
        free(ys.data);
    }

    { // short
        GupArrayShort xs = gup_array_from_short(static_ss, gup_array_size(static_ss));
        GupArrayShort ys = gup_array_from_short(static_ss, gup_array_size(static_ss));
        gup_array_append_short(&ys, static_ss[0]);

        assert(gup_array_eq_short(xs, ys) == false);

        free(xs.data);
        free(ys.data);
    }
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

    #ifdef GUPPY_VERBOSE
    printf("All gup_array tests passed!\n");
    #endif // GUPPY_VERBOSE
}
