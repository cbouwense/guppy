#include "../src/guppy.h"

void popping_before_pushing_anything_fails(void) {
    GupStackInt stack = gup_stack_int_create(NULL);

    gup_assert(!gup_stack_int_pop(stack));

    gup_stack_int_destroy(stack);
}

void test_gup_stack(void) { 
    push_one_pop_one_gives_element();

    #ifdef GUPPY_VERBOSE
    printf("All gup_stack tests passed!\n");
    #endif // GUPPY_VERBOSE
}
