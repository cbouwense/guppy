#include "../src/guppy.h"

void test_gup_settings_get() {
    char *title  = gup_settings_get("title");
    char *author = gup_settings_get("author");
    char *server = gup_settings_get("server");
    int   port  = gup_settings_get_int("port");

    assert(strcmp(title, "guppy.h") == 0);
    assert(strcmp(author, "Christian Bouwense") == 0);
    assert(strcmp(server, "localhost") == 0);
    assert(port == 5432);
}
