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

void test_gup_array_empty_constructors(void) {
    { // bool
        GupArrayBool bs = gup_array_bool();
        
        assert(bs.capacity == 256);
        assert(bs.count == 0);
        assert(bs.data == NULL);
    }

    { // char
        GupArrayChar cs = gup_array_char();
        
        assert(cs.capacity == 256);
        assert(cs.count == 0);
        assert(cs.data == NULL);
    }

    { // double
        GupArrayDouble ds = gup_array_double();
        
        assert(ds.capacity == 256);
        assert(ds.count == 0);
        assert(ds.data == NULL);
    }

    { // float
        GupArrayFloat fs = gup_array_float();
        
        assert(fs.capacity == 256);
        assert(fs.count == 0);
        assert(fs.data == NULL);
    }

    { // int
        GupArrayInt is = gup_array_int();
        
        assert(is.capacity == 256);
        assert(is.count == 0);
        assert(is.data == NULL);
    }

    { // long
        GupArrayLong ls = gup_array_long();
        
        assert(ls.capacity == 256);
        assert(ls.count == 0);
        assert(ls.data == NULL);
    }

    { // short
        GupArrayShort ss = gup_array_short();
        
        assert(ss.capacity == 256);
        assert(ss.count == 0);
        assert(ss.data == NULL);
    }
}

void test_gup_array_from_constructors(void) {
    { // bool
        GupArrayBool bs = gup_array_from_bool(static_bs, gup_array_size(static_bs));

        assert(bs.capacity == 256);
        assert(bs.count == 3);
        assert(memcmp(bs.data, static_bs, bs.count) == 0);
    }

    { // char
        GupArrayChar cs = gup_array_from_char(static_cs, gup_array_size(static_cs));

        assert(cs.capacity == 256);
        assert(cs.count == 3);
        assert(memcmp(cs.data, static_cs, cs.count) == 0);
    }

    { // double
        GupArrayDouble ds = gup_array_from_double(static_ds, gup_array_size(static_ds));

        assert(ds.capacity == 256);
        assert(ds.count == 3);
        assert(memcmp(ds.data, static_ds, ds.count) == 0);
    }

    { // float
        GupArrayFloat fs = gup_array_from_float(static_fs, gup_array_size(static_fs));

        assert(fs.capacity == 256);
        assert(fs.count == 3);
        assert(memcmp(fs.data, static_fs, fs.count) == 0);
    }

    { // int
        GupArrayInt is = gup_array_from_int(static_is, gup_array_size(static_is));

        assert(is.capacity == 256);
        assert(is.count == 3);
        assert(memcmp(is.data, static_is, is.count) == 0);
    }

    { // long
        GupArrayLong ls = gup_array_from_long(static_ls, gup_array_size(static_ls));

        assert(ls.capacity == 256);
        assert(ls.count == 3);
        assert(memcmp(ls.data, static_ls, ls.count) == 0);
    }

    { // short
        GupArrayShort ss = gup_array_from_short(static_ss, gup_array_size(static_ss));

        assert(ss.capacity == 256);
        assert(ss.count == 3);
        assert(memcmp(ss.data, static_ss, ss.count) == 0);
    }
}

void test_gup_array_copy_constructors(void) {
    { // bool
        GupArrayBool bs = gup_array_from_bool(static_bs, gup_array_size(static_bs));
        GupArrayBool bs_copy = gup_array_copy_bool(bs);

        assert(gup_array_eq_bool(bs, bs_copy));
    }

    { // char
        GupArrayChar cs = gup_array_from_char(static_cs, gup_array_size(static_cs));
        GupArrayChar cs_copy = gup_array_copy_char(cs);

        assert(gup_array_eq_char(cs, cs_copy));
    }

    { // double
        GupArrayDouble ds = gup_array_from_double(static_ds, gup_array_size(static_ds));
        GupArrayDouble ds_copy = gup_array_copy_double(ds);

        gup_array_print_double(ds);
        gup_array_print_double(ds_copy);

        assert(gup_array_eq_double(ds, ds_copy));
    }

    { // float
        GupArrayFloat fs = gup_array_from_float(static_fs, gup_array_size(static_fs));
        GupArrayFloat fs_copy = gup_array_copy_float(fs);

        assert(gup_array_eq_float(fs, fs_copy));
    }

    { // int
        GupArrayInt is = gup_array_from_int(static_is, gup_array_size(static_is));
        GupArrayInt is_copy = gup_array_copy_int(is);

        assert(gup_array_eq_int(is, is_copy));
    }

    { // long
        GupArrayLong ls = gup_array_from_long(static_ls, gup_array_size(static_ls));
        GupArrayLong ls_copy = gup_array_copy_long(ls);

        assert(gup_array_eq_long(ls, ls_copy));
    }

    { // short
        GupArrayShort ss = gup_array_from_short(static_ss, gup_array_size(static_ss));
        GupArrayShort ss_copy = gup_array_copy_short(ss);

        assert(gup_array_eq_short(ss, ss_copy));
    }
}

void test_gup_array(void) {
    test_gup_array_empty_constructors();
    test_gup_array_from_constructors();
    test_gup_array_copy_constructors();

    #ifdef GUPPY_VERBOSE
    printf("All gup_array tests passed!\n");
    #endif // GUPPY_VERBOSE
}
