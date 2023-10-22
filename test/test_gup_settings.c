#include "../src/guppy.h"

void test_gup_settings_get(void) {
    char *title          = gup_settings_get("title");
    char *author         = gup_settings_get("author");
    char *server         = gup_settings_get("server");
    int port             = gup_settings_get_int("port");
    char *does_not_exist = gup_settings_get("does_not_exist");

    assert(strcmp(title, "guppy.h") == 0);
    assert(strcmp(author, "Christian Bouwense") == 0);
    assert(strcmp(server, "localhost") == 0);
    assert(port == 5432);
    assert(does_not_exist == NULL);

    free(title);
    free(author);
    free(server);
}

void test_gup_settings_get_from(void) {
    const char *filename = "./resources/settings.toml";
    char *title          = gup_settings_get_from("title", filename);
    char *author         = gup_settings_get_from("author", filename);
    char *server         = gup_settings_get_from("server", filename);
    char *does_not_exist = gup_settings_get_from("does_not_exist", filename);

    assert(strcmp(title, "guppy.h") == 0);
    assert(strcmp(author, "Christian Bouwense") == 0);
    assert(strcmp(server, "localhost") == 0);
    assert(does_not_exist == NULL);

    assert(strcmp(title, "guppy.h") == 0);
    assert(strcmp(author, "Christian Bouwense") == 0);
    assert(strcmp(server, "localhost") == 0);

    free(title);
    free(author);
    free(server);
}

void test_gup_settings_set(void) {
    gup_settings_set("title", "asdf.h");
    assert(strcmp(gup_settings_get("title"), "asdf.h") == 0);

    // Reset for other tests
    gup_settings_set("title", "guppy.h");
    assert(strcmp(gup_settings_get("title"), "guppy.h") == 0);
}

void test_gup_settings(void) {
    test_gup_settings_get();
    test_gup_settings_get_from();
    test_gup_settings_set();
}
