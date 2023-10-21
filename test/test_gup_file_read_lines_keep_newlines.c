#include "../src/guppy.h"

void test_gup_file_read_lines_keep_newlines() {
    char **lines = NULL;
    
    { // empty.txt
        lines = gup_file_read_lines_keep_newlines("./resources/empty.txt");
        assert(lines == NULL);
    }

    { // one_newline.txt
        lines = gup_file_read_lines_keep_newlines("./resources/one_newline.txt");
        assert(strcmp(lines[0], "\n") == 0);
        assert(lines[1] == NULL);

        free(lines[0]);
    }

    { // foo.txt
        lines = gup_file_read_lines_keep_newlines("./resources/foo.txt");
        assert(strcmp(lines[0], "one\n") == 0);
        assert(strcmp(lines[1], "twotwo\n") == 0);
        assert(strcmp(lines[2], "three three three\n") == 0);
        assert(strcmp(lines[3], "\n") == 0);
        assert(lines[4] == NULL);

        for (int i = 0; i < gup_file_line_count("./resources/foo.txt") - 1; i++) {
            free(lines[i]);
        }
    }

    { // guppy.h
        lines = gup_file_read_lines_keep_newlines("./src/guppy.h");
        assert(strcmp(lines[2], "#ifndef GUPPY_H\n") == 0);
        #ifdef GUPPY_DEBUG
        gup_print_array_string(lines);
        #endif

        for (int i = 0; i < gup_file_line_count("./src/guppy.h") - 1; i++) {
            free(lines[i]);
        }
    }

    { // settings.toml
        lines = gup_file_read_lines_keep_newlines("./resources/settings.toml");
        #ifdef GUPPY_DEBUG
        gup_print_array_string(lines);
        #endif

        for (int i = 0; i < gup_file_line_count("./resources/settings.toml") - 1; i++) {
            free(lines[i]);
        }
    }
}
