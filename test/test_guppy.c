#include <float.h>
#include <limits.h>

// #define GUPPY_DEBUG_MEMORY
#include "../src/guppy.h"

int main(void) {
    char *title = gup_settings_get("title");
    char *setting = gup_settings_get("author");
    char *server = gup_settings_get("server");
    char *port = gup_settings_get("port");

    Gup_String_View title_sv = gup_sv_from_cstr(title);
    printf("title_sv: "SV_Fmt"\n", SV_Arg(title_sv));

    printf("title: %s\n", title);
    printf("author: %s\n", setting);
    printf("server: %s\n", server);
    printf("port: %s\n", port);

    return 0;
}
