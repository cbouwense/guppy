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
    GupStackChar stack = gup_stack_char_create(NULL);
    char seventeen, thirtyeight = 0;

    gup_stack_char_push(NULL, &stack, (char)17);
    gup_stack_char_push(NULL, &stack, (char)38);

    gup_assert(gup_stack_char_pop(&stack, &thirtyeight));
    gup_assert(gup_stack_char_pop(&stack, &seventeen));
    gup_assert(thirtyeight == 38);
    gup_assert(seventeen == 17);

    gup_stack_char_destroy(stack);
}

void cstr_stacks_work(void) {
    GupStackCstr stack = gup_stack_cstr_create(NULL);
    char *seventeen, *thirtyeight;

    gup_stack_cstr_push(NULL, &stack, "7 teen");
    gup_stack_cstr_push(NULL, &stack, "thirty 8");

    gup_assert(gup_stack_cstr_pop(&stack, &thirtyeight));
    gup_assert(gup_stack_cstr_pop(&stack, &seventeen));
    gup_assert(gup_cstr_equals(thirtyeight, "thirty 8"));
    gup_assert(gup_cstr_equals(seventeen, "7 teen"));

    gup_stack_cstr_destroy(stack);
}

void test_gup_stack(void) { 
    popping_before_pushing_anything_fails();
    push_once_pop_once();
    push_once_pop_twice();
    push_twice_pop_twice();
    cstr_stacks_work();

    #ifdef GUPPY_VERBOSE
    printf("All gup_stack tests passed!\n");
    #endif // GUPPY_VERBOSE
}
