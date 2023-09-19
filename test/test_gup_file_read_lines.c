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

        free(lines[0]);
    }

    { // foo.txt
        lines = gup_file_read_lines("test/foo.txt");
        assert(strcmp(lines[0], "one") == 0);
        assert(strcmp(lines[1], "twotwo") == 0);
        assert(strcmp(lines[2], "three three three") == 0);
        assert(strcmp(lines[3], "") == 0);
        assert(lines[4] == NULL);

        for (int i = 0; i < gup_file_line_count("test/foo.txt") - 1; i++) {
            free(lines[i]);
        }
    }

    { // guppy.h
        lines = gup_file_read_lines("src/guppy.h");
        assert(strcmp(lines[2], "#ifndef GUPPY_H") == 0);
        #ifdef GUPPY_DEBUG
        gup_print_array_string(lines);
        #endif

        for (int i = 0; i < gup_file_line_count("src/guppy.h") - 1; i++) {
            free(lines[i]);
        }
    }

    { // settings.toml
        lines = gup_file_read_lines("test/settings.toml");
        #ifdef GUPPY_DEBUG
        gup_print_array_string(lines);
        #endif

        for (int i = 0; i < gup_file_line_count("test/settings.toml") - 1; i++) {
            free(lines[i]);
        }
    }
}
