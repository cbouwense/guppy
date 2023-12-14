#include "../src/guppy.h"

void test_gup_does_setting_file_line_contain_key(void) {
    {
        GupStringView line = SV_STATIC("title = \"guppy.h\"");
        GupStringView key  = SV_STATIC("title");

        assert(true == _gup_does_setting_file_line_contain_key(line, key));
    }

    {
        GupStringView line = SV_STATIC("title = \"guppy.h\"");
        GupStringView key  = SV_STATIC("author");

        assert(false == _gup_does_setting_file_line_contain_key(line, key));
    }

    { // Comments always return false
        GupStringView line = SV_STATIC("# Comment");
        GupStringView key  = SV_STATIC("title");

        assert(false == _gup_does_setting_file_line_contain_key(line, key));
    }

    { // Section headers always return false
        GupStringView line = SV_STATIC("[Section header]");
        GupStringView key  = SV_STATIC("title");

        assert(false == _gup_does_setting_file_line_contain_key(line, key));
    }

    { // Empty lines always return false
        GupStringView line = SV_STATIC("");
        GupStringView key  = SV_STATIC("title");

        assert(false == _gup_does_setting_file_line_contain_key(line, key));
    }

    { // Lines without equals signs always return false
        GupStringView line = SV_STATIC("title is guppy.h");
        GupStringView key  = SV_STATIC("title");

        assert(false == _gup_does_setting_file_line_contain_key(line, key));
    }
}

void test_gup_settings_get(void) {
    char *title          = gup_settings_get("title");
    char *author         = gup_settings_get("author");
    char *server         = gup_settings_get("server");
    int port             = gup_settings_get_int("port");
    char *does_not_exist = gup_settings_get("does_not_exist");

    assert(gup_cstr_eq(title, "guppy.h"));
    assert(gup_cstr_eq(author, "Christian Bouwense"));
    assert(gup_cstr_eq(server, "localhost"));
    assert(port == 5432);
    assert(does_not_exist == NULL);

    free(title);
    free(author);
    free(server);
}

void test_gup_settings_get_from_file(void) {
    const char *filename = "./resources/settings.toml";
    char *title          = gup_settings_get_from_file("title", filename);
    char *author         = gup_settings_get_from_file("author", filename);
    char *server         = gup_settings_get_from_file("server", filename);
    char *does_not_exist = gup_settings_get_from_file("does_not_exist", filename);

    assert(gup_cstr_eq(title, "guppy.h"));
    assert(gup_cstr_eq(author, "Christian Bouwense"));
    assert(gup_cstr_eq(server, "localhost"));
    assert(does_not_exist == NULL);

    assert(gup_cstr_eq(title, "guppy.h"));
    assert(gup_cstr_eq(author, "Christian Bouwense"));
    assert(gup_cstr_eq(server, "localhost"));

    free(title);
    free(author);
    free(server);
}

void test_gup_settings_set(void) {
    { // Setting that exists
        gup_settings_set("title", "asdf.h");

        assert(gup_cstr_eq(gup_settings_get("title"), "asdf.h"));
    }

    { // Setting that doesn't exist
        gup_settings_set("does_not_exist", "should still show up though");

        assert(gup_settings_get("does_not_exist") != NULL);
        assert(gup_cstr_eq(gup_settings_get("does_not_exist"), "should still show up though"));
    }
}

void test_gup_settings(void) {
    test_gup_does_setting_file_line_contain_key();
    test_gup_settings_get();
    test_gup_settings_get_from_file();
    test_gup_settings_set();
}
