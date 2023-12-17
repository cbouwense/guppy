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

void test_gup_file_read(void) {
    char *file_contents = NULL;
    
    { // File that does not exist should return NULL
        file_contents = gup_file_read("./resources/doesnotexist.txt");
        assert(file_contents == NULL);
    }

    { // empty.txt
        file_contents = gup_file_read("./resources/empty.txt");
        assert(strcmp(file_contents, "") == 0);

        free(file_contents);
    }

    { // one_newline.txt
        file_contents = gup_file_read("./resources/one_newline.txt");
        assert(strcmp(file_contents, "\n") == 0);

        free(file_contents);
    }

    { // foo.txt
        file_contents = gup_file_read("./resources/foo.txt");
        assert(strcmp(file_contents, "one\ntwotwo\nthree three three\n\n") == 0);

        free(file_contents);
    }

    { // settings.toml
        file_contents = gup_file_read("./resources/settings.toml");
        
        assert(strcmp(file_contents, "# This is a TOML file\n\ntitle = \"guppy.h\"\nauthor = \"Christian Bouwense\"\n\n[database]\nserver = \"localhost\"\nport = 5432\n") == 0);

        free(file_contents);
    }
}

void test_gup_file_read_lines(void) {
    char **lines = NULL;
    
    { // empty.txt
        lines = gup_file_read_lines("./resources/empty.txt");
        assert(lines == NULL);
    }

    { // one_newline.txt
        lines = gup_file_read_lines("./resources/one_newline.txt");
        assert(gup_cstr_eq(lines[0], ""));
        assert(lines[1] == NULL);

        free(lines[0]);
        free(lines);
    }

    { // foo.txt
        lines = gup_file_read_lines("./resources/foo.txt");
        #ifdef GUPPY_VERBOSE
        gup_file_print("./resources/foo.txt");
        gup_print_array_string(lines);
        #endif

        assert(gup_cstr_eq(lines[0], "one"));
        assert(gup_cstr_eq(lines[1], "twotwo"));
        assert(gup_cstr_eq(lines[2], "three three three"));
        assert(gup_cstr_eq(lines[3], ""));
        assert(lines[4] == NULL);

        const int line_count = gup_file_line_count("./resources/foo.txt");
        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
    }

    { // settings.toml
        lines = gup_file_read_lines("./resources/settings.toml");
        #ifdef GUPPY_VERBOSE
        gup_file_print("./resources/settings.toml");
        gup_print_array_string(lines);
        #endif

        assert(gup_cstr_eq(lines[0], "# This is a TOML file"));
        assert(gup_cstr_eq(lines[1], ""));
        assert(gup_cstr_eq(lines[2], "title = \"guppy.h\""));
        assert(gup_cstr_eq(lines[3], "author = \"Christian Bouwense\""));
        assert(gup_cstr_eq(lines[4], ""));
        assert(gup_cstr_eq(lines[5], "[database]"));
        assert(gup_cstr_eq(lines[6], "server = \"localhost\""));
        assert(gup_cstr_eq(lines[7], "port = 5432"));
        assert(lines[8] == NULL);

        const int line_count = gup_file_line_count("./resources/settings.toml");
        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
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
        
        assert(gup_cstr_eq(lines[0], "\n"));
        assert(lines[1] == NULL);

        free(lines[0]);
        free(lines);
    }

    { // foo.txt
        lines = gup_file_read_lines_keep_newlines("./resources/foo.txt");
        #ifdef GUPPY_VERBOSE
        gup_file_print("./resources/foo.txt");
        gup_print_array_string(lines);
        #endif

        assert(gup_cstr_eq(lines[0], "one\n"));
        assert(gup_cstr_eq(lines[1], "twotwo\n"));
        assert(gup_cstr_eq(lines[2], "three three three\n"));
        assert(gup_cstr_eq(lines[3], "\n"));
        assert(lines[4] == NULL);

        const int line_count = gup_file_line_count("./resources/foo.txt");
        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
    }

    { // settings.toml
        lines = gup_file_read_lines_keep_newlines("./resources/settings.toml");
        #ifdef GUPPY_VERBOSE
        gup_print_array_string(lines);
        #endif

        assert(gup_cstr_eq(lines[0], "# This is a TOML file\n"));
        assert(gup_cstr_eq(lines[1], "\n"));
        assert(gup_cstr_eq(lines[2], "title = \"guppy.h\"\n"));
        assert(gup_cstr_eq(lines[3], "author = \"Christian Bouwense\"\n"));
        assert(gup_cstr_eq(lines[4], "\n"));
        assert(gup_cstr_eq(lines[5], "[database]\n"));
        assert(gup_cstr_eq(lines[6], "server = \"localhost\"\n"));
        assert(gup_cstr_eq(lines[7], "port = 5432\n"));
        assert(lines[8] == NULL);

        const int line_count = gup_file_line_count("./resources/settings.toml");
        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
    }
}

void test_gup_file_write(void) {
    bool result = true;
    char* file_contents;

    gup_file_delete("./resources/empty_write.txt");
    gup_file_delete("./resources/hello.txt");
    gup_file_delete("./resources/hello_world.txt");

    { // Empty line write
        result = gup_file_write("", "./resources/empty_write.txt");
        file_contents = gup_file_read("./resources/empty_write.txt");

        assert(result);
        assert(strcmp("", file_contents) == 0);

        free(file_contents);
    }

    { // Single line write
        result = gup_file_write("Hello", "./resources/hello.txt");
        file_contents = gup_file_read("./resources/hello.txt");

        assert(result);
        assert(strcmp("Hello", file_contents) == 0);

        free(file_contents);
    }

    { // Multi line write
        result = gup_file_write("Hello\nWorld\n", "./resources/hello_world.txt");
        file_contents = gup_file_read("./resources/hello_world.txt");

        assert(result);
        assert(strcmp("Hello\nWorld\n", file_contents) == 0);

        free(file_contents);
    }
}

void test_gup_file_write_lines(void) {
    bool result = true;
    char *file_contents;

    gup_file_delete("./resources/empty_write_lines.txt");
    gup_file_delete("./resources/hello_lines.txt");
    gup_file_delete("./resources/hello_world_lines.txt");

    { // No lines write
        const char *lines[] = {0};
        result = gup_file_write_lines(lines, 0, "./resources/empty_write_lines.txt");
        file_contents = gup_file_read("./resources/empty_write_lines.txt");
        
        assert(result);
        assert(strcmp("", file_contents) == 0);

        free(file_contents);
    }

    { // Single line write
        const char *lines[] = {"Hello"};
        result = gup_file_write_lines(lines, 1, "./resources/hello_lines.txt");
        file_contents = gup_file_read("./resources/hello_lines.txt");

        assert(result);
        assert(strcmp("Hello\n", file_contents) == 0);

        free(file_contents);
    }

    { // Multi line write
        const char *lines[] = {"Hello", "World", ""};
        result = gup_file_write_lines(lines, 3, "./resources/hello_world_lines.txt");
        file_contents = gup_file_read("./resources/hello_world_lines.txt");

        assert(result);
        assert(strcmp("Hello\nWorld\n\n", file_contents) == 0);

        free(file_contents);
    }
}

void test_gup_file_print(void) {
    gup_file_print("./resources/doesnotexist.txt");
    gup_file_print("./resources/empty.txt");
    gup_file_print("./resources/one_newline.txt");
    gup_file_print("./resources/foo.txt");
    gup_file_print("./resources/settings.toml");
}

void test_gup_file_print_lines(void) {
    gup_file_print_lines("./resources/doesnotexist.txt");
    gup_file_print_lines("./resources/empty.txt");
    gup_file_print_lines("./resources/one_newline.txt");
    gup_file_print_lines("./resources/foo.txt");
    gup_file_print_lines("./resources/settings.toml");
}

void test_gup_file(void) {
    test_gup_file_is_empty();
    test_gup_file_line_count();
    test_gup_file_read();
    test_gup_file_read_lines();
    test_gup_file_read_lines_keep_newlines();
    test_gup_file_write();
    test_gup_file_write_lines();
    #ifdef GUPPY_VERBOSE
    test_gup_file_print();
    test_gup_file_print_lines();
    #endif // GUPPY_VERBOSE
}
