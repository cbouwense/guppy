#include "../src/guppy.h"

void test_gup_array_bool(void) {
    Gup_Array_Bool *bools;

    { // Empty
        bools = gup_array_bool();

        assert(bools->capacity == 0);
        assert(bools->count == 0);
        assert(bools->data == NULL);
    }

    { // From a few elements
        const bool xs[] = {true, false, true};
        bools = gup_array_bool_from(xs, sizeof(xs) / sizeof(bool));

        assert(bools->capacity == 3);
        assert(bools->count == 3);
        assert(bools->data[0] == true);
        assert(bools->data[1] == false);
        assert(bools->data[2] == true);
    }

    { // Append
        bools = gup_array_bool();
        gup_array_bool_append(bools, true);
        
        assert(bools->capacity == 1);
        assert(bools->count == 1);
        assert(bools->data[0] == true);

        gup_array_bool_append(bools, true);
        gup_array_bool_append(bools, false);
        gup_array_bool_append(bools, true);
        gup_array_bool_append(bools, true);
        gup_array_bool_append(bools, false);
        gup_array_bool_append(bools, false);

        assert(bools->capacity == 8);
        assert(bools->count == 7);
        assert(bools->data[0] == true);
        assert(bools->data[1] == true);
        assert(bools->data[2] == false);
        assert(bools->data[3] == true);
        assert(bools->data[4] == true);
        assert(bools->data[5] == false);
        assert(bools->data[6] == false);
    }

    { // Prepend
        bools = gup_array_bool();
        gup_array_bool_prepend(bools, true);
        
        assert(bools->capacity == 1);
        assert(bools->count == 1);
        assert(bools->data[0] == true);

        gup_array_bool_prepend(bools, true);
        gup_array_bool_prepend(bools, false);
        gup_array_bool_prepend(bools, true);
        gup_array_bool_prepend(bools, true);
        gup_array_bool_prepend(bools, false);
        gup_array_bool_prepend(bools, false);

        assert(bools->capacity == 8);
        assert(bools->count == 7);
        assert(bools->data[0] == false);
        assert(bools->data[1] == false);
        assert(bools->data[2] == true);
        assert(bools->data[3] == true);
        assert(bools->data[4] == false);
        assert(bools->data[5] == true);
        assert(bools->data[6] == true);
    }

    free(bools->data);
    free(bools);
}

void test_gup_array_char(void) {
    Gup_Array_Char *chars;

    { // Empty
        chars = gup_array_char();

        assert(chars->capacity == 0);
        assert(chars->count == 0);
        assert(chars->data == NULL);
    }

    { // From a few elements
        const char xs[] = {'a', 'b', 'c'};
        chars = gup_array_char_from(xs, sizeof(xs) / sizeof(char));

        assert(chars->capacity == 3);
        assert(chars->count == 3);
        assert(chars->data[0] == 'a');
        assert(chars->data[1] == 'b');
        assert(chars->data[2] == 'c');
    }

    { // Append
        chars = gup_array_char();
        gup_array_char_append(chars, 'a');
        
        assert(chars->capacity == 1);
        assert(chars->count == 1);
        assert(chars->data[0] == 'a');

        gup_array_char_append(chars, 'a');
        gup_array_char_append(chars, 'b');
        gup_array_char_append(chars, 'a');
        gup_array_char_append(chars, 'a');
        gup_array_char_append(chars, 'b');
        gup_array_char_append(chars, 'b');

        assert(chars->capacity == 8);
        assert(chars->count == 7);
        assert(chars->data[0] == 'a');
        assert(chars->data[1] == 'a');
        assert(chars->data[2] == 'b');
        assert(chars->data[3] == 'a');
        assert(chars->data[4] == 'a');
        assert(chars->data[5] == 'b');
        assert(chars->data[6] == 'b');
    }

    { // Prepend
        chars = gup_array_char();
        gup_array_char_prepend(chars, 'a');
        
        assert(chars->capacity == 1);
        assert(chars->count == 1);
        assert(chars->data[0] == 'a');

        gup_array_char_prepend(chars, 'a');
        gup_array_char_prepend(chars, 'b');
        gup_array_char_prepend(chars, 'a');
        gup_array_char_prepend(chars, 'a');
        gup_array_char_prepend(chars, 'b');
        gup_array_char_prepend(chars, 'b');

        assert(chars->capacity == 8);
        assert(chars->count == 7);
        assert(chars->data[0] == 'b');
        assert(chars->data[1] == 'b');
        assert(chars->data[2] == 'a');
        assert(chars->data[3] == 'a');
        assert(chars->data[4] == 'b');
        assert(chars->data[5] == 'a');
        assert(chars->data[6] == 'a');
    }

    free(chars->data);
    free(chars);
}

void test_gup_array_float(void) {
    Gup_Array_Float *floats;

    { // Empty
        floats = gup_array_float();

        assert(floats->capacity == 0);
        assert(floats->count == 0);
        assert(floats->data == NULL);
    }

    { // From a few elements
        const float xs[] = {1.0f, 2.0f, 3.0f};
        floats = gup_array_float_from(xs, sizeof(xs) / sizeof(float));

        assert(floats->capacity == 3);
        assert(floats->count == 3);
        assert(floats->data[0] == 1.0f);
        assert(floats->data[1] == 2.0f);
        assert(floats->data[2] == 3.0f);
    }

    { // Append
        floats = gup_array_float();
        gup_array_float_append(floats, 42.0f);
        
        assert(floats->capacity == 1);
        assert(floats->count == 1);
        assert(floats->data[0] == 42.0f);

        gup_array_float_append(floats, 17.0f);
        gup_array_float_append(floats, 38.0f);
        gup_array_float_append(floats, 1.0f);
        gup_array_float_append(floats, 3.0f);
        gup_array_float_append(floats, 3.0f);
        gup_array_float_append(floats, 7.0f);

        assert(floats->capacity == 8);
        assert(floats->count == 7);
        assert(floats->data[0] == 42.0f);
        assert(floats->data[1] == 17.0f);
        assert(floats->data[2] == 38.0f);
        assert(floats->data[3] == 1.0f);
        assert(floats->data[4] == 3.0f);
        assert(floats->data[5] == 3.0f);
        assert(floats->data[6] == 7.0f);
    }

    { // Prepend
        floats = gup_array_float();
        gup_array_float_prepend(floats, 42.0f);
        
        assert(floats->capacity == 1);
        assert(floats->count == 1);
        assert(floats->data[0] == 42.0f);

        gup_array_float_prepend(floats, 17.0f);
        gup_array_float_prepend(floats, 38.0f);
        gup_array_float_prepend(floats, 1.0f);
        gup_array_float_prepend(floats, 3.0f);
        gup_array_float_prepend(floats, 3.0f);
        gup_array_float_prepend(floats, 7.0f);

        assert(floats->capacity == 8);
        assert(floats->count == 7);
        assert(floats->data[0] == 7.0f);
        assert(floats->data[1] == 3.0f);
        assert(floats->data[2] == 3.0f);
        assert(floats->data[3] == 1.0f);
        assert(floats->data[4] == 38.0f);
        assert(floats->data[5] == 17.0f);
        assert(floats->data[6] == 42.0f);
    }

    free(floats->data);
    free(floats);
}

void test_gup_array_int(void) {
    Gup_Array_Int *ints;

    { // Empty
        ints = gup_array_int();

        assert(ints->capacity == 0);
        assert(ints->count == 0);
        assert(ints->data == NULL);
    }

    { // From a few elements
        const int xs[] = {1, 2, 3};
        ints = gup_array_int_from(xs, sizeof(xs) / sizeof(int));

        assert(ints->capacity == 3);
        assert(ints->count == 3);
        assert(ints->data[0] == 1);
        assert(ints->data[1] == 2);
        assert(ints->data[2] == 3);
    }

    { // Append
        ints = gup_array_int();
        gup_array_int_append(ints, 42);
        
        assert(ints->capacity == 1);
        assert(ints->count == 1);
        assert(ints->data[0] == 42);

        gup_array_int_append(ints, 17);
        gup_array_int_append(ints, 38);
        gup_array_int_append(ints, 1);
        gup_array_int_append(ints, 3);
        gup_array_int_append(ints, 3);
        gup_array_int_append(ints, 7);

        assert(ints->capacity == 8);
        assert(ints->count == 7);
        assert(ints->data[0] == 42);
        assert(ints->data[1] == 17);
        assert(ints->data[2] == 38);
        assert(ints->data[3] == 1);
        assert(ints->data[4] == 3);
        assert(ints->data[5] == 3);
        assert(ints->data[6] == 7);
    }

    { // Prepend
        ints = gup_array_int();
        gup_array_int_prepend(ints, 42);
        
        assert(ints->capacity == 1);
        assert(ints->count == 1);
        assert(ints->data[0] == 42);

        gup_array_int_prepend(ints, 17);
        gup_array_int_prepend(ints, 38);
        gup_array_int_prepend(ints, 1);
        gup_array_int_prepend(ints, 3);
        gup_array_int_prepend(ints, 3);
        gup_array_int_prepend(ints, 7);

        assert(ints->capacity == 8);
        assert(ints->count == 7);
        assert(ints->data[0] == 7);
        assert(ints->data[1] == 3);
        assert(ints->data[2] == 3);
        assert(ints->data[3] == 1);
        assert(ints->data[4] == 38);
        assert(ints->data[5] == 17);
        assert(ints->data[6] == 42);
    }

    free(ints->data);
    free(ints);
}

void test_gup_array(void) {
    test_gup_array_bool();
    test_gup_array_char();
    test_gup_array_float();
    test_gup_array_int();

    #ifdef GUPPY_VERBOSE
    printf("All gup_array tests passed!\n");
    #endif // GUPPY_VERBOSE
}