#include <float.h>
#include <limits.h>

#define GUPPY_DEBUG
#include "../src/guppy.h"

int main(void) {
    guppy_file_print("test/settings.toml");

    return 0;
}
