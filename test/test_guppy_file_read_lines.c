#include "../src/guppy.h"

void test_guppy_file_read_lines() {
    char **lines = NULL;

    // empty.txt
    lines = guppy_file_read_lines("test/empty.txt");
    assert(lines == NULL);

    // one_newline.txt
    lines = guppy_file_read_lines("test/one_newline.txt");
    assert(strcmp(lines[0], "") == 0);

    // foo.txt
    lines = guppy_file_read_lines("test/foo.txt");
    assert(strcmp(lines[0], "one") == 0);
    assert(strcmp(lines[1], "twotwo") == 0);
    assert(strcmp(lines[2], "three three three") == 0);
    assert(strcmp(lines[3], "") == 0);

    // guppy.h
    lines = guppy_file_read_lines("src/guppy.h");
    assert(strcmp(lines[0], "#ifndef GUPPY_H") == 0);
    guppy_print_array_string(lines);

    // settings.toml
    lines = guppy_file_read_lines("test/settings.toml");
    guppy_print_array_string(lines);

    free(lines);
}
