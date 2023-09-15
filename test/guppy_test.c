#include <float.h>
#include <limits.h>
#include "../src/guppy.h"

int main(void) {
    const char *file_name = "./test/foo.txt";

    char **lines = guppy_file_read_lines(file_name);

    return 0;
}
