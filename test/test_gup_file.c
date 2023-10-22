#include "../src/guppy.h"

void test_gup_file_is_empty(void) {
    assert(gup_file_is_empty("./resources/empty.txt") == true);
    assert(gup_file_is_empty("./resources/one_newline.txt") == false);
    assert(gup_file_is_empty("./resources/foo.txt") == false);
    assert(gup_file_is_empty("./resources/stb.txt") == false);
}

void test_gup_file_line_count(void) {
    int line_count = 0;

    line_count = gup_file_line_count("./resources/empty.txt");
    assert(line_count == 0);

    line_count = gup_file_line_count("./resources/one_newline.txt");
    assert(line_count == 2);

    line_count = gup_file_line_count("./resources/foo.txt");
    assert(line_count == 5);

    line_count = gup_file_line_count("./resources/stb.txt");
    assert(line_count == 13111);
}

void test_gup_file_read_lines(void) {
    char **lines = NULL;
    
    { // empty.txt
        lines = gup_file_read_lines("./resources/empty.txt");
        assert(lines == NULL);
    }

    { // one_newline.txt
        lines = gup_file_read_lines("./resources/one_newline.txt");
        assert(strcmp(lines[0], "") == 0);
        assert(lines[1] == NULL);

        free(lines[0]);
    }

    { // foo.txt
        lines = gup_file_read_lines("./resources/foo.txt");
        #ifdef GUPPY_VERBOSE
        gup_file_print("./resources/foo.txt");
        gup_print_array_string(lines);
        #endif

        assert(strcmp(lines[0], "one") == 0);
        assert(strcmp(lines[1], "twotwo") == 0);
        assert(strcmp(lines[2], "three three three") == 0);
        assert(strcmp(lines[3], "") == 0);
        assert(lines[4] == NULL);

        const int line_count = gup_file_line_count("./resources/foo.txt");
        for (int i = 0; i < line_count; i++) {
            if (lines[i]) free(lines[i]);
        }
    }

    { // settings.toml
        lines = gup_file_read_lines("./resources/settings.toml");
        #ifdef GUPPY_VERBOSE
        gup_file_print("./resources/settings.toml");
        gup_print_array_string(lines);
        #endif

        assert(strcmp(lines[0], "# This is a TOML file") == 0);
        assert(strcmp(lines[1], "") == 0);
        assert(strcmp(lines[2], "title = \"guppy.h\"") == 0);
        assert(strcmp(lines[3], "author = \"Christian Bouwense\"") == 0);
        assert(strcmp(lines[4], "") == 0);
        assert(strcmp(lines[5], "[database]") == 0);
        assert(strcmp(lines[6], "server = \"localhost\"") == 0);
        assert(strcmp(lines[7], "port = 5432") == 0);
        assert(lines[8] == NULL);

        const int line_count = gup_file_line_count("./resources/settings.toml");
        for (int i = 0; i < line_count; i++) {
            if (lines[i]) free(lines[i]);
        }
    }
}

void test_gup_file_read_lines_keep_newlines(void) {
    char **lines = NULL;
    
    { // empty.txt
        lines = gup_file_read_lines_keep_newlines("./resources/empty.txt");
        assert(lines == NULL);
    }

    { // one_newline.txt
        lines = gup_file_read_lines_keep_newlines("./resources/one_newline.txt");
        #ifdef GUPPY_VERBOSE
        gup_file_print("./resources/one_newline.txt");
        gup_print_array_string(lines);
        #endif
        
        assert(strcmp(lines[0], "\n") == 0);
        assert(lines[1] == NULL);

        free(lines[0]);
    }

    { // foo.txt
        lines = gup_file_read_lines_keep_newlines("./resources/foo.txt");
        #ifdef GUPPY_VERBOSE
        gup_file_print("./resources/foo.txt");
        gup_print_array_string(lines);
        #endif

        assert(strcmp(lines[0], "one\n") == 0);
        assert(strcmp(lines[1], "twotwo\n") == 0);
        assert(strcmp(lines[2], "three three three\n") == 0);
        assert(strcmp(lines[3], "\n") == 0);
        assert(lines[4] == NULL);

        const int line_count = gup_file_line_count("./resources/foo.txt");
        for (int i = 0; i < line_count; i++) {
            if (lines[i]) free(lines[i]);
        }
    }

    { // settings.toml
        lines = gup_file_read_lines_keep_newlines("./resources/settings.toml");
        #ifdef GUPPY_VERBOSE
        gup_print_array_string(lines);
        #endif

        assert(strcmp(lines[0], "# This is a TOML file\n") == 0);
        assert(strcmp(lines[1], "\n") == 0);
        assert(strcmp(lines[2], "title = \"guppy.h\"\n") == 0);
        assert(strcmp(lines[3], "author = \"Christian Bouwense\"\n") == 0);
        assert(strcmp(lines[4], "\n") == 0);
        assert(strcmp(lines[5], "[database]\n") == 0);
        assert(strcmp(lines[6], "server = \"localhost\"\n") == 0);
        assert(strcmp(lines[7], "port = 5432\n") == 0);
        assert(lines[8] == NULL);

        const int line_count = gup_file_line_count("./resources/settings.toml");
        for (int i = 0; i < line_count; i++) {
            if (lines[i]) free(lines[i]);
        }
    }
}

void test_gup_file(void) {
    test_gup_file_is_empty();
    test_gup_file_line_count();
    test_gup_file_read_lines();
    test_gup_file_read_lines_keep_newlines();
}