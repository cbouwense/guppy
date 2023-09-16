#include "../src/guppy.h"

void test_guppy_file_read_lines_keep_newlines() {
    char **lines = NULL;

    // empty.txt
    lines = guppy_file_read_lines_keep_newlines("test/empty.txt");
    assert(lines == NULL);

    // one_newline.txt
    lines = guppy_file_read_lines_keep_newlines("test/one_newline.txt");
    assert(strcmp(lines[0], "\n") == 0);

    // foo.txt
    lines = guppy_file_read_lines_keep_newlines("test/foo.txt");
    assert(strcmp(lines[0], "one\n") == 0);
    assert(strcmp(lines[1], "twotwo\n") == 0);
    assert(strcmp(lines[2], "three three three\n") == 0);
    assert(strcmp(lines[3], "\n") == 0);

    // guppy.h
    lines = guppy_file_read_lines_keep_newlines("src/guppy.h");
    assert(strcmp(lines[0], "#ifndef GUPPY_H\n") == 0);
    guppy_print_array_string(lines);

    // settings.toml
    lines = guppy_file_read_lines_keep_newlines("test/settings.toml");
    guppy_print_array_string(lines);

    free(lines);
}
