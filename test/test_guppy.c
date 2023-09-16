#include <float.h>
#include <limits.h>

// #define GUPPY_DEBUG_MEMORY
#include "../src/guppy.h"

int main(void) {
    char *title = guppy_settings_get("title");
    char *setting = guppy_settings_get("author");
    char *server = guppy_settings_get("server");
    char *port = guppy_settings_get("port");

    printf("title: %s\n", title);
    printf("author: %s\n", setting);
    printf("server: %s\n", server);
    printf("port: %s\n", port);

    return 0;
}
