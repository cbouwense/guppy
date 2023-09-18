#include "../src/guppy.h"

void test_gup_file_read_lines() {
    char **lines = NULL;
    
    { // empty.txt
        lines = gup_file_read_lines("test/empty.txt");
        assert(lines == NULL);
    }

    { // one_newline.txt
        lines = gup_file_read_lines("test/one_newline.txt");
        assert(strcmp(lines[0], "") == 0);
        assert(lines[1] == NULL);
    }

    { // foo.txt
        lines = gup_file_read_lines("test/foo.txt");
        assert(strcmp(lines[0], "one") == 0);
        assert(strcmp(lines[1], "twotwo") == 0);
        assert(strcmp(lines[2], "three three three") == 0);
        assert(strcmp(lines[3], "") == 0);
        assert(lines[4] == NULL);
    }

    { // guppy.h
        lines = gup_file_read_lines("src/guppy.h");
        assert(strcmp(lines[2], "#ifndef GUPPY_H") == 0);
        gup_print_array_string(lines);
    }

    { // settings.toml
        lines = gup_file_read_lines("test/settings.toml");
        gup_print_array_string(lines);
    }

    free(lines);
}
