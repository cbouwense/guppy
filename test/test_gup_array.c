#include "../src/guppy.h"

void test_gup_array_bool(void) {
    GupArrayBool *bools, *x_bools, *y_bools;
    bool found;

    { // Empty
        bools = gup_array_bool();

        assert(bools->capacity == 0);
        assert(bools->count == 0);
        assert(bools->data == NULL);

        free(bools);
    }

    { // From a few elements
        const bool xs[] = {true, false, true};
        bools = gup_array_bool_from(xs, sizeof(xs) / sizeof(bool));

        assert(bools->capacity == 3);
        assert(bools->count == 3);
        assert(bools->data[0] == true);
        assert(bools->data[1] == false);
        assert(bools->data[2] == true);

        free(bools->data);
        free(bools);
    }

    { // Empty arrays are equivalent
        const bool xs[] = {0};
        const bool ys[] = {0};
        x_bools = gup_array_bool_from(xs, sizeof(xs) / sizeof(bool));
        y_bools = gup_array_bool_from(ys, sizeof(ys) / sizeof(bool));
        
        bool are_they_equal = gup_array_bool_eq(x_bools, y_bools);

        assert(are_they_equal == true);

        free(x_bools->data);
        free(y_bools->data);
        free(x_bools);
        free(y_bools);
    }

    { // One empty one not is not equivalent
        const bool xs[] = {true, false, true};
        const bool ys[] = {0};
        x_bools = gup_array_bool_from(xs, sizeof(xs) / sizeof(bool));
        y_bools = gup_array_bool_from(ys, sizeof(ys) / sizeof(bool));
        
        bool are_they_equal = gup_array_bool_eq(x_bools, y_bools);

        assert(are_they_equal == false);

        free(x_bools->data);
        free(y_bools->data);
        free(x_bools);
        free(y_bools);
    }

    { // Identical non-empty arrays are equivalent
        const bool xs[] = {true, false, true};
        const bool ys[] = {true, false, true};
        x_bools = gup_array_bool_from(xs, sizeof(xs) / sizeof(bool));
        y_bools = gup_array_bool_from(ys, sizeof(ys) / sizeof(bool));
        
        bool are_they_equal = gup_array_bool_eq(x_bools, y_bools);

        assert(are_they_equal == true);

        free(x_bools->data);
        free(y_bools->data);
        free(x_bools);
        free(y_bools);
    }

    { // Differing non-empty arrays are not equivalent
        const bool xs[] = {true, false, true};
        const bool ys[] = {true, false, true, false};
        x_bools = gup_array_bool_from(xs, sizeof(xs) / sizeof(bool));
        y_bools = gup_array_bool_from(ys, sizeof(ys) / sizeof(bool));
        
        bool are_they_equal = gup_array_bool_eq(x_bools, y_bools);

        assert(are_they_equal == false);

        free(x_bools->data);
        free(y_bools->data);
        free(x_bools);
        free(y_bools);
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

        free(bools->data);
        free(bools);
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

        free(bools->data);
        free(bools);
    }

    { // Remove first
        bools = gup_array_bool();
        gup_array_bool_append(bools, true);
        
        found = gup_array_bool_remove_first(bools, false);

        assert(found == false);
        assert(bools->capacity == 1);
        assert(bools->count == 1);
        assert(bools->data[0] == true);

        gup_array_bool_append(bools, false);
        gup_array_bool_append(bools, false);
        gup_array_bool_append(bools, false);
        gup_array_bool_append(bools, true);

        found = gup_array_bool_remove_first(bools, false);

        assert(found == true);
        assert(bools->capacity == 4);
        assert(bools->count == 4);
        assert(bools->data[0] == true);
        assert(bools->data[1] == false);
        assert(bools->data[2] == false);
        assert(bools->data[3] == true);

        free(bools->data);
        free(bools);
    }

    { // Remove last no occurrence
        GupArrayBool * bools = gup_array_bool();
        gup_array_bool_append(bools, true);
        
        found = gup_array_bool_remove_last(bools, false);

        assert(found == false);
        assert(bools->capacity == 1);
        assert(bools->count == 1);
        assert(bools->data[0] == true);

        free(bools->data);
        free(bools);
    }

    { // Remove last with occurrence
        bool xs[] = {true, false, true, false, true, false, false};
        bools = gup_array_bool_from(xs, sizeof(xs)/sizeof(bool));

        found = gup_array_bool_remove_last(bools, false);

        assert(found == true);
        assert(bools->capacity == 6);
        assert(bools->count == 6);
        assert(bools->data[0] == true);
        assert(bools->data[1] == false);
        assert(bools->data[2] == true);
        assert(bools->data[3] == false);
        assert(bools->data[4] == true);
        assert(bools->data[5] == false);

        free(bools->data);
        free(bools);
    }

}

void test_gup_array_char(void) {
    GupArrayChar *chars, *x_chars, *y_chars;
    bool found;

    { // Empty
        chars = gup_array_char();

        assert(chars->capacity == 0);
        assert(chars->count == 0);
        assert(chars->data == NULL);

        free(chars);
    }

    { // From a few elements
        const char xs[] = {'a', 'b', 'c'};
        chars = gup_array_char_from(xs, sizeof(xs) / sizeof(char));

        assert(chars->capacity == 3);
        assert(chars->count == 3);
        assert(chars->data[0] == 'a');
        assert(chars->data[1] == 'b');
        assert(chars->data[2] == 'c');

        free(chars->data);
        free(chars);
    }

    { // Empty arrays are equivalent
        const char xs[] = {0};
        const char ys[] = {0};
        x_chars = gup_array_char_from(xs, sizeof(xs) / sizeof(char));
        y_chars = gup_array_char_from(ys, sizeof(ys) / sizeof(char));
        
        char are_they_equal = gup_array_char_eq(x_chars, y_chars);

        assert(are_they_equal == true);

        free(x_chars->data);
        free(y_chars->data);
        free(x_chars);
        free(y_chars);
    }

    { // One empty one not is not equivalent
        const char xs[] = {true, false, true};
        const char ys[] = {0};
        x_chars = gup_array_char_from(xs, sizeof(xs) / sizeof(char));
        y_chars = gup_array_char_from(ys, sizeof(ys) / sizeof(char));
        
        char are_they_equal = gup_array_char_eq(x_chars, y_chars);

        assert(are_they_equal == false);

        free(x_chars->data);
        free(y_chars->data);
        free(x_chars);
        free(y_chars);
    }

    { // Identical non-empty arrays are equivalent
        const char xs[] = {true, false, true};
        const char ys[] = {true, false, true};
        x_chars = gup_array_char_from(xs, sizeof(xs) / sizeof(char));
        y_chars = gup_array_char_from(ys, sizeof(ys) / sizeof(char));
        
        char are_they_equal = gup_array_char_eq(x_chars, y_chars);

        assert(are_they_equal == true);

        free(x_chars->data);
        free(y_chars->data);
        free(x_chars);
        free(y_chars);
    }

    { // Differing non-empty arrays are not equivalent
        const char xs[] = {true, false, true};
        const char ys[] = {true, false, true, false};
        x_chars = gup_array_char_from(xs, sizeof(xs) / sizeof(char));
        y_chars = gup_array_char_from(ys, sizeof(ys) / sizeof(char));
        
        char are_they_equal = gup_array_char_eq(x_chars, y_chars);

        assert(are_they_equal == false);

        free(x_chars->data);
        free(y_chars->data);
        free(x_chars);
        free(y_chars);
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

        free(chars->data);
        free(chars);
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

        free(chars->data);
        free(chars);
    }

    { // Remove first
        chars = gup_array_char();
        gup_array_char_append(chars, 'a');
        
        found = gup_array_char_remove_first(chars, 'b');

        assert(found == false);
        assert(chars->capacity == 1);
        assert(chars->count == 1);
        assert(chars->data[0] == 'a');

        gup_array_char_append(chars, 'b');
        gup_array_char_append(chars, 'b');
        gup_array_char_append(chars, 'b');
        gup_array_char_append(chars, 'c');

        found = gup_array_char_remove_first(chars, 'b');

        assert(found == true);
        assert(chars->capacity == 4);
        assert(chars->count == 4);
        assert(chars->data[0] == 'a');
        assert(chars->data[1] == 'b');
        assert(chars->data[2] == 'b');
        assert(chars->data[3] == 'c');

        free(chars->data);
        free(chars);
    }

    { // Remove last no occurrence
        GupArrayChar * chars = gup_array_char();
        gup_array_char_append(chars, 'a');
        
        found = gup_array_char_remove_last(chars, 'b');

        assert(found == false);
        assert(chars->capacity == 1);
        assert(chars->count == 1);
        assert(chars->data[0] == 'a');

        free(chars->data);
        free(chars);
    }

    { // Remove last with occurrence
        char xs[] = {'a', 'b', 'c', 'b', 'd', 'b', 'e'};
        chars = gup_array_char_from(xs, sizeof(xs)/sizeof(char));

        found = gup_array_char_remove_last(chars, 'b');

        // [1, 2, 3, 2, 4, 2, 5] ->
        // [1, 2, 3, 2, 4, 5]
        assert(found == true);
        assert(chars->capacity == 6);
        assert(chars->count == 6);
        assert(chars->data[0] == 'a');
        assert(chars->data[1] == 'b');
        assert(chars->data[2] == 'c');
        assert(chars->data[3] == 'b');
        assert(chars->data[4] == 'd');
        assert(chars->data[5] == 'e');

        free(chars->data);
        free(chars);
    }
}

void test_gup_array_float(void) {
    GupArrayFloat *floats, *x_floats, *y_floats;
    bool found;

    { // Empty
        floats = gup_array_float();

        assert(floats->capacity == 0);
        assert(floats->count == 0);
        assert(floats->data == NULL);

        free(floats);
    }

    { // From a few elements
        const float xs[] = {1.0f, 2.0f, 3.0f};
        floats = gup_array_float_from(xs, sizeof(xs) / sizeof(float));

        assert(floats->capacity == 3);
        assert(floats->count == 3);
        assert(floats->data[0] == 1.0f);
        assert(floats->data[1] == 2.0f);
        assert(floats->data[2] == 3.0f);

        free(floats->data);
        free(floats);
    }

    { // Empty arrays are equivalent
        const float xs[] = {0};
        const float ys[] = {0};
        x_floats = gup_array_float_from(xs, sizeof(xs) / sizeof(float));
        y_floats = gup_array_float_from(ys, sizeof(ys) / sizeof(float));
        
        float are_they_equal = gup_array_float_eq(x_floats, y_floats);

        assert(are_they_equal == true);

        free(x_floats->data);
        free(y_floats->data);
        free(x_floats);
        free(y_floats);
    }

    { // One empty one not is not equivalent
        const float xs[] = {true, false, true};
        const float ys[] = {0};
        x_floats = gup_array_float_from(xs, sizeof(xs) / sizeof(float));
        y_floats = gup_array_float_from(ys, sizeof(ys) / sizeof(float));
        
        float are_they_equal = gup_array_float_eq(x_floats, y_floats);

        assert(are_they_equal == false);

        free(x_floats->data);
        free(y_floats->data);
        free(x_floats);
        free(y_floats);
    }

    { // Identical non-empty arrays are equivalent
        const float xs[] = {true, false, true};
        const float ys[] = {true, false, true};
        x_floats = gup_array_float_from(xs, sizeof(xs) / sizeof(float));
        y_floats = gup_array_float_from(ys, sizeof(ys) / sizeof(float));
        
        float are_they_equal = gup_array_float_eq(x_floats, y_floats);

        assert(are_they_equal == true);

        free(x_floats->data);
        free(y_floats->data);
        free(x_floats);
        free(y_floats);
    }

    { // Differing non-empty arrays are not equivalent
        const float xs[] = {true, false, true};
        const float ys[] = {true, false, true, false};
        x_floats = gup_array_float_from(xs, sizeof(xs) / sizeof(float));
        y_floats = gup_array_float_from(ys, sizeof(ys) / sizeof(float));
        
        float are_they_equal = gup_array_float_eq(x_floats, y_floats);

        assert(are_they_equal == false);

        free(x_floats->data);
        free(y_floats->data);
        free(x_floats);
        free(y_floats);
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

        free(floats->data);
        free(floats);
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

        free(floats->data);
        free(floats);
    }

    { // Remove first
        floats = gup_array_float();
        gup_array_float_append(floats, 1);
        
        found = gup_array_float_remove_first(floats, 0);

        assert(found == false);
        assert(floats->capacity == 1);
        assert(floats->count == 1);
        assert(floats->data[0] == 1);

        gup_array_float_append(floats, 2);
        gup_array_float_append(floats, 2);
        gup_array_float_append(floats, 2);
        gup_array_float_append(floats, 3);

        found = gup_array_float_remove_first(floats, 2);

        assert(found == true);
        assert(floats->capacity == 4);
        assert(floats->count == 4);
        assert(floats->data[0] == 1);
        assert(floats->data[1] == 2);
        assert(floats->data[2] == 2);
        assert(floats->data[3] == 3);

        free(floats->data);
        free(floats);
    }

    { // Remove last no occurrence
        GupArrayFloat * floats = gup_array_float();
        gup_array_float_append(floats, 1);
        
        found = gup_array_float_remove_last(floats, 0);

        assert(found == false);
        assert(floats->capacity == 1);
        assert(floats->count == 1);
        assert(floats->data[0] == 1);

        free(floats->data);
        free(floats);
    }

    { // Remove last with occurrence
        float xs[] = {1.0f, 2.0f, 3.0f, 2.0f, 4.0f, 2.0f, 5.0f};
        floats = gup_array_float_from(xs, sizeof(xs)/sizeof(float));

        found = gup_array_float_remove_last(floats, 2);

        // [1, 2, 3, 2, 4, 2, 5] ->
        // [1, 2, 3, 2, 4, 5]
        assert(found == true);
        assert(floats->capacity == 6);
        assert(floats->count == 6);
        assert(floats->data[0] == 1.0f);
        assert(floats->data[1] == 2.0f);
        assert(floats->data[2] == 3.0f);
        assert(floats->data[3] == 2.0f);
        assert(floats->data[4] == 4.0f);
        assert(floats->data[5] == 5.0f);

        free(floats->data);
        free(floats);
    }
}

void test_gup_array_int(void) {
    GupArrayInt *ints, *x_ints, *y_ints;
    bool found;

    { // Empty
        ints = gup_array_int();

        assert(ints->capacity == 0);
        assert(ints->count == 0);
        assert(ints->data == NULL);

        free(ints);
    }

    { // From a few elements
        const int xs[] = {1, 2, 3};
        ints = gup_array_int_from(xs, sizeof(xs) / sizeof(int));

        assert(ints->capacity == 3);
        assert(ints->count == 3);
        assert(ints->data[0] == 1);
        assert(ints->data[1] == 2);
        assert(ints->data[2] == 3);

        free(ints->data);
        free(ints);
    }

    { // Empty arrays are equivalent
        const int xs[] = {0};
        const int ys[] = {0};
        x_ints = gup_array_int_from(xs, sizeof(xs) / sizeof(int));
        y_ints = gup_array_int_from(ys, sizeof(ys) / sizeof(int));
        
        int are_they_equal = gup_array_int_eq(x_ints, y_ints);

        assert(are_they_equal == true);

        free(x_ints->data);
        free(y_ints->data);
        free(x_ints);
        free(y_ints);
    }

    { // One empty one not is not equivalent
        const int xs[] = {true, false, true};
        const int ys[] = {0};
        x_ints = gup_array_int_from(xs, sizeof(xs) / sizeof(int));
        y_ints = gup_array_int_from(ys, sizeof(ys) / sizeof(int));
        
        int are_they_equal = gup_array_int_eq(x_ints, y_ints);

        assert(are_they_equal == false);

        free(x_ints->data);
        free(y_ints->data);
        free(x_ints);
        free(y_ints);
    }

    { // Identical non-empty arrays are equivalent
        const int xs[] = {true, false, true};
        const int ys[] = {true, false, true};
        x_ints = gup_array_int_from(xs, sizeof(xs) / sizeof(int));
        y_ints = gup_array_int_from(ys, sizeof(ys) / sizeof(int));
        
        int are_they_equal = gup_array_int_eq(x_ints, y_ints);

        assert(are_they_equal == true);

        free(x_ints->data);
        free(y_ints->data);
        free(x_ints);
        free(y_ints);
    }

    { // Differing non-empty arrays are not equivalent
        const int xs[] = {true, false, true};
        const int ys[] = {true, false, true, false};
        x_ints = gup_array_int_from(xs, sizeof(xs) / sizeof(int));
        y_ints = gup_array_int_from(ys, sizeof(ys) / sizeof(int));
        
        int are_they_equal = gup_array_int_eq(x_ints, y_ints);

        assert(are_they_equal == false);

        free(x_ints->data);
        free(y_ints->data);
        free(x_ints);
        free(y_ints);
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

        free(ints->data);
        free(ints);
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
    
        free(ints->data);
        free(ints);
    }

    { // Remove all
        int found_count;
        ints = gup_array_int();
        gup_array_int_append(ints, 1);
        
        found_count = gup_array_int_remove_all(ints, 0);

        assert(found_count == 0);
        assert(ints->capacity == 1);
        assert(ints->count == 1);
        assert(ints->data[0] == 1);

        for (int i = 0; i < 1234; i++) {
            gup_array_int_append(ints, 2);
        }
        gup_array_int_append(ints, 3);

        found_count = gup_array_int_remove_all(ints, 2);

        assert(found_count == 1234);
        assert(ints->capacity == 2);
        assert(ints->count == 2);
        assert(ints->data[0] == 1);
        assert(ints->data[1] == 3);

        free(ints->data);
        free(ints);
    }

    { // Remove first
        ints = gup_array_int();
        gup_array_int_append(ints, 1);
        
        found = gup_array_int_remove_first(ints, 0);

        assert(found == false);
        assert(ints->capacity == 1);
        assert(ints->count == 1);
        assert(ints->data[0] == 1);

        gup_array_int_append(ints, 2);
        gup_array_int_append(ints, 2);
        gup_array_int_append(ints, 2);
        gup_array_int_append(ints, 3);

        found = gup_array_int_remove_first(ints, 2);

        assert(found == true);
        assert(ints->capacity == 4);
        assert(ints->count == 4);
        assert(ints->data[0] == 1);
        assert(ints->data[1] == 2);
        assert(ints->data[2] == 2);
        assert(ints->data[3] == 3);

        free(ints->data);
        free(ints);
    }

    { // Remove last no occurrence
        GupArrayInt * ints = gup_array_int();
        gup_array_int_append(ints, 1);
        
        found = gup_array_int_remove_last(ints, 0);

        assert(found == false);
        assert(ints->capacity == 1);
        assert(ints->count == 1);
        assert(ints->data[0] == 1);

        free(ints->data);
        free(ints);
    }

    { // Remove last with occurrence
        int xs[] = {1, 2, 3, 2, 4, 2, 5};
        ints = gup_array_int_from(xs, sizeof(xs)/sizeof(int));

        found = gup_array_int_remove_last(ints, 2);

        // [1, 2, 3, 2, 4, 2, 5] ->
        // [1, 2, 3, 2, 4, 5]
        assert(found == true);
        assert(ints->capacity == 6);
        assert(ints->count == 6);
        assert(ints->data[0] == 1);
        assert(ints->data[1] == 2);
        assert(ints->data[2] == 3);
        assert(ints->data[3] == 2);
        assert(ints->data[4] == 4);
        assert(ints->data[5] == 5);

        free(ints->data);
        free(ints);
    }
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