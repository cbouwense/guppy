#include "../src/guppy.h"

void popping_before_pushing_anything_fails(void) {
    GupStackInt stack = gup_stack_int_create(NULL);
    int out = 0;

    gup_assert(!gup_stack_int_pop(&stack, &out));
    gup_assert(out == 0); // out should be unchanged

    gup_stack_int_destroy(stack);
}

void push_once_pop_once(void) {
    GupStackInt stack = gup_stack_int_create(NULL);
    int out = 0;

    gup_stack_int_push(NULL, &stack, 42);

    gup_assert(gup_stack_int_pop(&stack, &out));
    gup_assert(out == 42);

    gup_stack_int_destroy(stack);
}

void push_once_pop_twice(void) {
    GupStackInt stack = gup_stack_int_create(NULL);
    int out = 0;

    gup_stack_int_push(NULL, &stack, 42);

    gup_assert(gup_stack_int_pop(&stack, &out));
    gup_assert(!gup_stack_int_pop(&stack, &out));
    gup_assert(out == 42);

    gup_stack_int_destroy(stack);
}

void push_twice_pop_twice(void) {
    GupStackInt stack = gup_stack_int_create(NULL);
    int seventeen, thirtyeight = 0;

    gup_stack_int_push(NULL, &stack, 17);
    gup_stack_int_push(NULL, &stack, 38);

    gup_assert(gup_stack_int_pop(&stack, &thirtyeight));
    gup_assert(gup_stack_int_pop(&stack, &seventeen));
    gup_assert(thirtyeight == 38);
    gup_assert(seventeen == 17);

    gup_stack_int_destroy(stack);
}

void test_gup_stack(void) { 
    popping_before_pushing_anything_fails();
    push_once_pop_once();
    push_once_pop_twice();
    push_twice_pop_twice();

    #ifdef GUPPY_VERBOSE
    printf("All gup_stack tests passed!\n");
    #endif // GUPPY_VERBOSE
}
