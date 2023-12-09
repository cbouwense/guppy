#define GUPPY_VERBOSE
#include "../src/guppy.h"

void test_gup_array_int(void) {
    Gup_Array_Int *ints;

    { // Empty
        ints = gup_array_int();

        assert(ints->capacity == 0);
        assert(ints->length == 0);
        assert(ints->data == NULL);
    }

    { // From a few elements
        const int xs[] = {1, 2, 3};
        ints = gup_array_int_from(xs, sizeof(xs) / sizeof(int));

        assert(ints->capacity == 3);
        assert(ints->length == 3);
        assert(ints->data[0] == 1);
        assert(ints->data[1] == 2);
        assert(ints->data[2] == 3);
    }

    { // Push
        ints = gup_array_int();
        gup_array_int_append(ints, 42);
        
        assert(ints->capacity == 1);
        assert(ints->length == 1);
        assert(ints->data[0] == 42);

        gup_array_int_append(ints, 17);
        gup_array_int_append(ints, 38);
        gup_array_int_append(ints, 1);
        gup_array_int_append(ints, 3);
        gup_array_int_append(ints, 3);
        gup_array_int_append(ints, 7);

        assert(ints->capacity == 8);
        assert(ints->length == 7);
        assert(ints->data[0] == 42);
        assert(ints->data[1] == 17);
        assert(ints->data[2] == 38);
    }

    { // 

    }

    free(ints->data);
    free(ints);
}

void test_gup_array(void) {
    test_gup_array_int();
    #ifdef GUPPY_VERBOSE
    printf("All gup_array tests passed!\n");
    #endif // GUPPY_VERBOSE
}