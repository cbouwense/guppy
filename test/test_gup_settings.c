#include "../src/guppy.h"

void test_gup_settings_get_and_set(void) {
    GupAllocatorBucket a = gup_allocator_bucket_create();

    GupString foo, bar, baz, not_there;
    bool foo_result = gup_settings_get_cstr((GupAllocator*)&a, "foo", &foo);
    bool bar_result = gup_settings_get_cstr((GupAllocator*)&a, "bar", &bar);
    bool baz_result = gup_settings_get_cstr((GupAllocator*)&a, "baz", &baz);
    bool not_there_result = gup_settings_get_cstr((GupAllocator*)&a, "not_there", &not_there);

    gup_assert(foo_result == true);
    gup_assert(bar_result == true);
    gup_assert(baz_result == true);
    gup_assert(not_there_result == false);
    gup_assert(gup_string_equals_cstr(foo, "1"));
    gup_assert(gup_string_equals_cstr(bar, "bar"));
    gup_assert(gup_string_equals_cstr(baz, "true"));

    gup_allocator_bucket_destroy(&a);
}

void reset_settings_file(void) {
    const bool result = gup_file_write_cstr("# This is a TOML file\n\ntitle = \"guppy.h\"\nauthor = \"Christian Bouwense\"\n\n[database]\nserver = \"localhost\"\nport = 5432\n", "./resources/settings.toml");

    gup_assert_verbose(result, "Encountered an error while resetting the settings file.\n");
}

void test_gup_settings(void) {
    reset_settings_file();

    test_gup_settings_get_and_set();

    reset_settings_file();
}
