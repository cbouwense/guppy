#include "../src/guppy.h"

void test_gup_settings_get(void) {
    char *title  = gup_settings_get("title");
    char *author = gup_settings_get("author");
    char *server = gup_settings_get("server");
    int port     = gup_settings_get_int("port");

    assert(strcmp(title, "guppy.h") == 0);
    assert(strcmp(author, "Christian Bouwense") == 0);
    assert(strcmp(server, "localhost") == 0);
    assert(port == 5432);

    free(title);
    free(author);
    free(server);
}

void test_gup_settings_get_from(void) {
    const char *filename = "./resources/settings.toml";
    char *title = gup_settings_get_from("title", filename);
    char *author = gup_settings_get_from("author", filename);
    char *server = gup_settings_get_from("server", filename);

    assert(title != NULL);
    assert(author != NULL);
    assert(server != NULL);

    assert(strcmp(title, "guppy.h") == 0);
    assert(strcmp(author, "Christian Bouwense") == 0);
    assert(strcmp(server, "localhost") == 0);

    free(title);
    free(author);
    free(server);
}

void test_gup_settings_set(void) {
    gup_settings_set("title", "new guppy.h");
    char *title  = gup_settings_get("title");

    assert(strcmp(title, "guppy.h") == 0);

    free(title);
}

void test_gup_settings(void) {
    test_gup_settings_get();
    test_gup_settings_get_from();
    test_gup_settings_set();
}