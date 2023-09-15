#include <float.h>
#include <limits.h>
#include "../src/guppy.h"

int main(void) {
    const char *file_name = "./test/foo.txt";

    printf("line count: %d\n", guppy_file_line_count(file_name));

    return 0;
}
