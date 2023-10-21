#include "../src/guppy.h"

void test_gup_settings_get_from() {
    const char *filename = "./resources/settings.toml";
    char *title = gup_settings_get_from("title", filename);
    // char *author = gup_settings_get_from("author", filename);
    // char *server = gup_settings_get_from("server", filename);

    // assert(title != NULL);
    // assert(author != NULL);
    // assert(server != NULL);

    // assert(strcmp(title, "guppy.h") == 0);
    // assert(strcmp(author, "Christian Bouwense") == 0);
    // assert(strcmp(server, "localhost") == 0);
}
