#include "../src/guppy.h"

void test_gup_settings_get_and_set(void) {
    GupArena a = gup_arena_create();

    GupString foo, bar, baz, not_there;
    bool foo_result = gup_settings_get_cstr_arena(&a, "foo", &foo);
    bool bar_result = gup_settings_get_cstr_arena(&a, "bar", &bar);
    bool baz_result = gup_settings_get_cstr_arena(&a, "baz", &baz);
    bool not_there_result = gup_settings_get_cstr_arena(&a, "not_there", &not_there);

    gup_assert(foo_result == true);
    gup_assert(bar_result == true);
    gup_assert(baz_result == true);
    gup_assert(not_there_result == false);
    gup_assert(gup_string_eq_cstr(foo, "1"));
    gup_assert(gup_string_eq_cstr(bar, "bar"));
    gup_assert(gup_string_eq_cstr(baz, "true"));

    gup_arena_destroy(a);
}

void test_gup_settings(void) {
    test_gup_settings_get_and_set();
}
