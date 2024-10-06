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
    // TODO: maybe file_read should return a boolean?
    { // File that does not exist should return count of 0
        GupString file_contents = gup_file_read("./resources/doesnotexist.txt");
        
        assert(file_contents.count == 0);
    
        free(file_contents.data);
    }

    { // empty.txt
        GupString file_contents = gup_file_read("./resources/empty.txt");
        
        assert(file_contents.count == 0);

        free(file_contents.data);
    }

    { // one_newline.txt
        GupString file_contents = gup_file_read("./resources/one_newline.txt");
        
        assert(gup_array_char_eq_cstr(file_contents, "\n"));

        free(file_contents.data);
    }

    { // foo.txt
        const char *expected = "one\ntwotwo\nthree three three\n\n";

        GupString file_contents = gup_file_read("./resources/foo.txt");
        
        assert(gup_array_char_eq_cstr(file_contents, expected));

        free(file_contents.data);
    }

    { // settings.toml
        const char *expected = "# This is a TOML file\n\ntitle = \"guppy.h\"\nauthor = \"Christian Bouwense\"\n\n[database]\nserver = \"localhost\"\nport = 5432\n";

        GupString file_contents = gup_file_read("./resources/settings.toml");
        
        assert(gup_array_char_eq_cstr(file_contents, expected));

        free(file_contents.data);
    }
}

void test_gup_file_read_as_cstr(void) {   
    { // File that does not exist should return NULL
        char *file_contents = gup_file_read_as_cstr("./resources/doesnotexist.txt");

        assert(file_contents == NULL);
    }

    { // empty.txt
        char *file_contents = gup_file_read_as_cstr("./resources/empty.txt");

        assert(strcmp(file_contents, "") == 0);

        free(file_contents);
    }

    { // one_newline.txt
        char *file_contents = gup_file_read_as_cstr("./resources/one_newline.txt");

        assert(strcmp(file_contents, "\n") == 0);

        free(file_contents);
    }

    { // foo.txt
        char *file_contents = gup_file_read_as_cstr("./resources/foo.txt");

        assert(strcmp(file_contents, "one\ntwotwo\nthree three three\n\n") == 0);

        free(file_contents);
    }

    { // settings.toml
        char *file_contents = gup_file_read_as_cstr("./resources/settings.toml");
        
        assert(strcmp(file_contents, "# This is a TOML file\n\ntitle = \"guppy.h\"\nauthor = \"Christian Bouwense\"\n\n[database]\nserver = \"localhost\"\nport = 5432\n") == 0);

        free(file_contents);
    }
}

void test_gup_file_read_lines(void) {
    { // empty.txt
        GupArrayString lines = gup_file_read_lines("./resources/empty.txt");

        assert(lines.count == 0);
    }

    { // one_newline.txt
        GupArrayString lines = gup_file_read_lines("./resources/one_newline.txt");

        assert(lines.count == 1);
        assert(lines.data[0].count == 0);

        gup_array_string_destroy(lines);
    }

    { // foo.txt
        GupArrayString lines = gup_file_read_lines("./resources/foo.txt");

        assert(lines.count == 4);
        assert(gup_array_char_eq_cstr(lines.data[0], "one"));
        assert(gup_array_char_eq_cstr(lines.data[1], "twotwo"));
        assert(gup_array_char_eq_cstr(lines.data[2], "three three three"));
        assert(gup_array_char_eq_cstr(lines.data[3], ""));

        gup_array_string_destroy(lines);
    }

    { // settings.toml
        GupArrayString lines = gup_file_read_lines("./resources/settings.toml");

        assert(lines.count == 8);
        assert(gup_array_char_eq_cstr(lines.data[0], "# This is a TOML file"));
        assert(gup_array_char_eq_cstr(lines.data[1], ""));
        assert(gup_array_char_eq_cstr(lines.data[2], "title = \"guppy.h\""));
        assert(gup_array_char_eq_cstr(lines.data[3], "author = \"Christian Bouwense\""));
        assert(gup_array_char_eq_cstr(lines.data[4], ""));
        assert(gup_array_char_eq_cstr(lines.data[5], "[database]"));
        assert(gup_array_char_eq_cstr(lines.data[6], "server = \"localhost\""));
        assert(gup_array_char_eq_cstr(lines.data[7], "port = 5432"));

        gup_array_string_destroy(lines);
    }
}

void test_gup_file_read_lines_keep_newlines(void) {
    { // empty.txt
        GupArrayString lines = gup_file_read_lines_keep_newlines("./resources/empty.txt");

        assert(lines.count == 0);
    }

    { // one_newline.txt
        GupArrayString lines = gup_file_read_lines_keep_newlines("./resources/one_newline.txt");

        assert(lines.count == 1);
        assert(gup_array_char_eq_cstr(lines.data[0], "\n"));

        gup_array_string_destroy(lines);
    }

    { // foo.txt
        GupArrayString lines = gup_file_read_lines_keep_newlines("./resources/foo.txt");

        assert(lines.count == 4);
        assert(gup_array_char_eq_cstr(lines.data[0], "one\n"));
        assert(gup_array_char_eq_cstr(lines.data[1], "twotwo\n"));
        assert(gup_array_char_eq_cstr(lines.data[2], "three three three\n"));
        assert(gup_array_char_eq_cstr(lines.data[3], "\n"));

        gup_array_string_destroy(lines);
    }

    { // settings.toml
        GupArrayString lines = gup_file_read_lines_keep_newlines("./resources/settings.toml");

        assert(lines.count == 8);
        assert(gup_array_char_eq_cstr(lines.data[0], "# This is a TOML file\n"));
        assert(gup_array_char_eq_cstr(lines.data[1], "\n"));
        assert(gup_array_char_eq_cstr(lines.data[2], "title = \"guppy.h\"\n"));
        assert(gup_array_char_eq_cstr(lines.data[3], "author = \"Christian Bouwense\"\n"));
        assert(gup_array_char_eq_cstr(lines.data[4], "\n"));
        assert(gup_array_char_eq_cstr(lines.data[5], "[database]\n"));
        assert(gup_array_char_eq_cstr(lines.data[6], "server = \"localhost\"\n"));
        assert(gup_array_char_eq_cstr(lines.data[7], "port = 5432\n"));

        gup_array_string_destroy(lines);
    }
}

void test_gup_file_read_lines_as_cstrs(void) {
    char **lines = NULL;

    { // empty.txt
        lines = gup_file_read_lines_as_cstrs("./resources/empty.txt");

        assert(lines == NULL);
    }

    { // one_newline.txt
        lines = gup_file_read_lines_as_cstrs("./resources/one_newline.txt");

        assert(strcmp(lines[0], "") == 0);
        assert(lines[1] == NULL);

        free(lines[0]);
        free(lines);
    }

    { // foo.txt
        lines = gup_file_read_lines_as_cstrs("./resources/foo.txt");

        assert(strcmp(lines[0], "one") == 0);
        assert(strcmp(lines[1], "twotwo") == 0);
        assert(strcmp(lines[2], "three three three") == 0);
        assert(strcmp(lines[3], "") == 0);
        assert(lines[4] == NULL);

        const int line_count = gup_file_line_count("./resources/foo.txt");
        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
    }

    { // settings.toml
        lines = gup_file_read_lines_as_cstrs("./resources/settings.toml");
        const int line_count = gup_file_line_count("./resources/settings.toml");

        #ifdef GUPPY_VERBOSE
        gup_file_print("./resources/settings.toml");
        for (int i = 0; i < line_count; i++) {
            printf("%s\n", lines[i]);
        }
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

        
        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
    }

}

void test_gup_file_read_lines_as_cstrs_keep_newlines(void) {
    char **lines = NULL;

    { // empty.txt
        lines = gup_file_read_lines_as_cstrs_keep_newlines("./resources/empty.txt");

        assert(lines == NULL);
    }

    { // one_newline.txt
        lines = gup_file_read_lines_as_cstrs_keep_newlines("./resources/one_newline.txt");

        assert(strcmp(lines[0], "\n") == 0);
        assert(lines[1] == NULL);

        free(lines[0]);
        free(lines);
    }

    { // foo.txt
        lines = gup_file_read_lines_as_cstrs_keep_newlines("./resources/foo.txt");

        assert(strcmp(lines[0], "one\n") == 0);
        assert(strcmp(lines[1], "twotwo\n") == 0);
        assert(strcmp(lines[2], "three three three\n") == 0);
        assert(strcmp(lines[3], "\n") == 0);
        assert(lines[4] == NULL);

        const int line_count = gup_file_line_count("./resources/foo.txt");
        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
    }

    { // settings.toml
        lines = gup_file_read_lines_as_cstrs_keep_newlines("./resources/settings.toml");

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
            free(lines[i]);
        }
        free(lines);
    }

}

void test_gup_file_size(void) {
    gup_assert_verbose(gup_file_size("./resources/empty.txt") == 0, "Expected empty.txt to have 0 characters");
    gup_assert_verbose(gup_file_size("./resources/hello.txt") == 5, "Expected hello.txt to have 5 characters");
}

void test_gup_file_write(void) {
    bool result = true;
    char* file_contents;

    gup_file_delete("./resources/empty_write.txt");
    gup_file_delete("./resources/hello.txt");
    gup_file_delete("./resources/hello_world.txt");

    { // Empty line write
        result = gup_file_write("", "./resources/empty_write.txt");
        file_contents = gup_file_read_as_cstr("./resources/empty_write.txt");

        assert(result);
        assert(strcmp("", file_contents) == 0);

        free(file_contents);
    }

    { // Single line write
        result = gup_file_write("Hello", "./resources/hello.txt");
        file_contents = gup_file_read_as_cstr("./resources/hello.txt");

        assert(result);
        assert(strcmp("Hello", file_contents) == 0);

        free(file_contents);
    }

    { // Multi line write
        result = gup_file_write("Hello\nWorld\n", "./resources/hello_world.txt");
        file_contents = gup_file_read_as_cstr("./resources/hello_world.txt");

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
        file_contents = gup_file_read_as_cstr("./resources/empty_write_lines.txt");
        
        assert(result);
        assert(strcmp("", file_contents) == 0);

        free(file_contents);
    }

    { // Single line write
        const char *lines[] = {"Hello"};
        result = gup_file_write_lines(lines, 1, "./resources/hello_lines.txt");
        file_contents = gup_file_read_as_cstr("./resources/hello_lines.txt");

        assert(result);
        assert(strcmp("Hello\n", file_contents) == 0);

        free(file_contents);
    }

    { // Multi line write
        const char *lines[] = {"Hello", "World", ""};
        result = gup_file_write_lines(lines, 3, "./resources/hello_world_lines.txt");
        file_contents = gup_file_read_as_cstr("./resources/hello_world_lines.txt");

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
    test_gup_file_read_as_cstr();
    test_gup_file_read_lines();
    test_gup_file_read_lines_keep_newlines();
    test_gup_file_read_lines_as_cstrs();
    test_gup_file_read_lines_as_cstrs_keep_newlines();
    test_gup_file_size();
    test_gup_file_write();
    test_gup_file_write_lines();
    #ifdef GUPPY_VERBOSE
    test_gup_file_print();
    test_gup_file_print_lines();
    #endif // GUPPY_VERBOSE
}
