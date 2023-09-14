#include <float.h>
#include <limits.h>
#include <stdio.h>
#include "../src/guppy.h"

int main(void) {
    const char *file_name = "./test/foo.txt";
    int write_result = guppy_file_write(file_name, "written by guppy");
    assert(write_result == 0);

    char *file_contents = guppy_file_read(file_name);
    printf("file contents:\n%s\n", file_contents);

    return 0;
}
