#include <float.h>
#include <limits.h>

#define GUPPY_DEBUG
#include "../src/guppy.h"

int main(void) {
    char *author_setting = guppy_settings_get("author");
    guppy_print_array_char(author_setting);

    assert(strcmp(author_setting, "John Doe") == 0);

    return 0;
}
