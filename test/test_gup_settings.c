#include "../src/guppy.h"

void test_gup_settings_get_and_set(void) {
    GupString foo, bar, baz, not_there;
    bool foo_result = gup_settings_get_cstr("foo", &foo);
    bool bar_result = gup_settings_get_cstr("bar", &bar);
    bool baz_result = gup_settings_get_cstr("baz", &baz);
    bool not_there_result = gup_settings_get_cstr("not_there", &not_there);

    gup_assert(foo_result == true);
    gup_assert(bar_result == true);
    gup_assert(baz_result == true);
    gup_assert(not_there_result == false);
    gup_assert(gup_string_eq_cstr(foo, "1"));
    gup_assert(gup_string_eq_cstr(bar, "bar"));
    gup_assert(gup_string_eq_cstr(baz, "true"));

    gup_string_destroy(foo);
    gup_string_destroy(bar);
    gup_string_destroy(baz);
}

void test_gup_settings(void) {
    test_gup_settings_get_and_set();
}
