#include "../src/guppy.h"

void test_gup_file_is_empty() {
    gup_assert(gup_file_is_empty("./resources/empty.txt") == true);
    gup_assert(gup_file_is_empty("./resources/one_newline.txt") == false);
    gup_assert(gup_file_is_empty("./resources/foo.txt") == false);
    gup_assert(gup_file_is_empty("./resources/stb.txt") == false);
}

void test_gup_file_line_count() {
    int line_count = 0;

    line_count = gup_file_line_count("./resources/empty.txt");
    gup_assert(line_count == 0);

    line_count = gup_file_line_count("./resources/one_newline.txt");
    gup_assert(line_count == 2);

    line_count = gup_file_line_count("./resources/foo.txt");
    gup_assert(line_count == 5);

    line_count = gup_file_line_count("./resources/stb.txt");
    gup_assert(line_count == 13111);
}

void test_gup_file_read(void) {
    GupString file_contents = {0};

    { // File that does not exist should return count of 0
        gup_assert(!gup_file_read("./resources/doesnotexist.txt", &file_contents));

        gup_string_destroy(file_contents);
    }

    { // empty.txt
        gup_assert(gup_file_read("./resources/empty.txt", &file_contents));
        gup_assert(file_contents.count == 0);

        gup_string_destroy(file_contents);
    }

    { // one_newline.txt
        gup_assert(gup_file_read("./resources/one_newline.txt", &file_contents));
        gup_assert(gup_array_char_eq_cstr(file_contents, "\n"));

        gup_string_destroy(file_contents);
    }

    { // foo.txt
        const char *expected = "one\ntwotwo\nthree three three\n\n";

        gup_assert(gup_file_read("./resources/foo.txt", &file_contents));
        gup_assert(gup_array_char_eq_cstr(file_contents, expected));

        gup_string_destroy(file_contents);
    }

    { // settings.toml
        const char *expected = "# This is a TOML file\n\ntitle = \"guppy.h\"\nauthor = \"Christian Bouwense\"\n\n[database]\nserver = \"localhost\"\nport = 5432\n";

        gup_assert(gup_file_read("./resources/settings.toml", &file_contents));
        gup_assert(gup_array_char_eq_cstr(file_contents, expected));

        gup_string_destroy(file_contents);
    }
}

void test_gup_file_read_arena(GupArena *a) {
    GupString file_contents = {0};

    { // File that does not exist should fail
        gup_assert(!gup_file_read_arena(a, "./resources/doesnotexist.txt", &file_contents));
    }

    { // empty.txt
        gup_assert(gup_file_read_arena(a, "./resources/empty.txt", &file_contents));
        gup_assert(file_contents.count == 0);
    }

    { // one_newline.txt
        gup_assert(gup_file_read_arena(a, "./resources/one_newline.txt", &file_contents));
        gup_assert(gup_array_char_eq_cstr(file_contents, "\n"));
    }

    { // foo.txt
        const char *expected = "one\ntwotwo\nthree three three\n\n";

        gup_assert(gup_file_read_arena(a, "./resources/foo.txt", &file_contents));
        gup_assert(gup_array_char_eq_cstr(file_contents, expected));
    }

    { // settings.toml
        const char *expected = "# This is a TOML file\n\ntitle = \"guppy.h\"\nauthor = \"Christian Bouwense\"\n\n[database]\nserver = \"localhost\"\nport = 5432\n";

        gup_assert(gup_file_read_arena(a, "./resources/settings.toml", &file_contents));
        gup_assert(gup_array_char_eq_cstr(file_contents, expected));
    }
}

void test_gup_file_read_as_cstr(void) {   
    { // File that does not exist should return false
        char *file_contents = NULL;

        gup_assert(!gup_file_read_as_cstr("./resources/doesnotexist.txt", &file_contents));
        gup_assert(file_contents == NULL);
    }

    { // empty.txt
        char *file_contents = NULL;

        gup_assert(gup_file_read_as_cstr("./resources/empty.txt", &file_contents));
        gup_assert(strcmp(file_contents, "") == 0);

        free(file_contents);
    }

    { // one_newline.txt
        char *file_contents = NULL;

        gup_assert(gup_file_read_as_cstr("./resources/one_newline.txt", &file_contents));
        gup_assert(strcmp(file_contents, "\n") == 0);

        free(file_contents);
    }

    { // foo.txt
        char *file_contents = NULL;
        gup_assert(gup_file_read_as_cstr("./resources/foo.txt", &file_contents));

        gup_assert(strcmp(file_contents, "one\ntwotwo\nthree three three\n\n") == 0);

        free(file_contents);
    }

    { // settings.toml
        char *file_contents = NULL;
        gup_assert(gup_file_read_as_cstr("./resources/settings.toml", &file_contents));
        
        gup_assert(strcmp(file_contents, "# This is a TOML file\n\ntitle = \"guppy.h\"\nauthor = \"Christian Bouwense\"\n\n[database]\nserver = \"localhost\"\nport = 5432\n") == 0);

        free(file_contents);
    }
}

void test_gup_file_read_as_cstr_arena(GupArena *a) {   
    { // File that does not exist should return false
        char *file_contents = NULL;

        gup_assert(!gup_file_read_as_cstr("./resources/doesnotexist.txt", &file_contents));
    }

    { // empty.txt
        char *file_contents = NULL;
        
        gup_assert(gup_file_read_as_cstr_arena(a, "./resources/empty.txt", &file_contents));

        gup_assert(strcmp(file_contents, "") == 0);
    }

    { // one_newline.txt
        char *file_contents = NULL;

        gup_assert(gup_file_read_as_cstr_arena(a, "./resources/one_newline.txt", &file_contents));

        gup_assert(strcmp(file_contents, "\n") == 0);
    }

    { // foo.txt
        char *file_contents = NULL;

        gup_assert(gup_file_read_as_cstr_arena(a, "./resources/foo.txt", &file_contents));

        gup_assert(strcmp(file_contents, "one\ntwotwo\nthree three three\n\n") == 0);
    }

    { // settings.toml
        char *file_contents = NULL;

        gup_assert(gup_file_read_as_cstr_arena(a, "./resources/settings.toml", &file_contents));
        
        gup_assert(strcmp(file_contents, "# This is a TOML file\n\ntitle = \"guppy.h\"\nauthor = \"Christian Bouwense\"\n\n[database]\nserver = \"localhost\"\nport = 5432\n") == 0);
    }
}

void test_gup_file_read_lines(void) {
    { // empty.txt
        GupArrayString lines = gup_file_read_lines("./resources/empty.txt");

        gup_assert(lines.count == 0);
    }

    { // one_newline.txt
        GupArrayString lines = gup_file_read_lines("./resources/one_newline.txt");

        gup_assert(lines.count == 1);
        gup_assert(lines.data[0].count == 0);

        gup_array_string_destroy(lines);
    }

    { // foo.txt
        GupArrayString lines = gup_file_read_lines("./resources/foo.txt");

        gup_assert(lines.count == 4);
        gup_assert(gup_array_char_eq_cstr(lines.data[0], "one"));
        gup_assert(gup_array_char_eq_cstr(lines.data[1], "twotwo"));
        gup_assert(gup_array_char_eq_cstr(lines.data[2], "three three three"));
        gup_assert(gup_array_char_eq_cstr(lines.data[3], ""));

        gup_array_string_destroy(lines);
    }

    { // settings.toml
        GupArrayString lines = gup_file_read_lines("./resources/settings.toml");

        gup_assert(lines.count == 8);
        gup_assert(gup_array_char_eq_cstr(lines.data[0], "# This is a TOML file"));
        gup_assert(gup_array_char_eq_cstr(lines.data[1], ""));
        gup_assert(gup_array_char_eq_cstr(lines.data[2], "title = \"guppy.h\""));
        gup_assert(gup_array_char_eq_cstr(lines.data[3], "author = \"Christian Bouwense\""));
        gup_assert(gup_array_char_eq_cstr(lines.data[4], ""));
        gup_assert(gup_array_char_eq_cstr(lines.data[5], "[database]"));
        gup_assert(gup_array_char_eq_cstr(lines.data[6], "server = \"localhost\""));
        gup_assert(gup_array_char_eq_cstr(lines.data[7], "port = 5432"));

        gup_array_string_destroy(lines);
    }
}

void test_gup_file_read_lines_arena(GupArena *a) {
    { // empty.txt
        GupArrayString lines = gup_file_read_lines_arena(a, "./resources/empty.txt");

        gup_assert(lines.count == 0);
    }

    { // one_newline.txt
        GupArrayString lines = gup_file_read_lines_arena(a, "./resources/one_newline.txt");

        gup_assert(lines.count == 1);
        gup_assert(lines.data[0].count == 0);
    }

    { // foo.txt
        GupArrayString lines = gup_file_read_lines_arena(a, "./resources/foo.txt");

        gup_assert(lines.count == 4);
        gup_assert(gup_array_char_eq_cstr(lines.data[0], "one"));
        gup_assert(gup_array_char_eq_cstr(lines.data[1], "twotwo"));
        gup_assert(gup_array_char_eq_cstr(lines.data[2], "three three three"));
        gup_assert(gup_array_char_eq_cstr(lines.data[3], ""));
    }

    { // settings.toml
        GupArrayString lines = gup_file_read_lines_arena(a, "./resources/settings.toml");

        gup_assert(lines.count == 8);
        gup_assert(gup_array_char_eq_cstr(lines.data[0], "# This is a TOML file"));
        gup_assert(gup_array_char_eq_cstr(lines.data[1], ""));
        gup_assert(gup_array_char_eq_cstr(lines.data[2], "title = \"guppy.h\""));
        gup_assert(gup_array_char_eq_cstr(lines.data[3], "author = \"Christian Bouwense\""));
        gup_assert(gup_array_char_eq_cstr(lines.data[4], ""));
        gup_assert(gup_array_char_eq_cstr(lines.data[5], "[database]"));
        gup_assert(gup_array_char_eq_cstr(lines.data[6], "server = \"localhost\""));
        gup_assert(gup_array_char_eq_cstr(lines.data[7], "port = 5432"));
    }
}

void test_gup_file_read_lines_keep_newlines() {
    { // empty.txt
        GupArrayString lines = gup_file_read_lines_keep_newlines("./resources/empty.txt");

        gup_assert(lines.count == 0);
    }

    { // one_newline.txt
        GupArrayString lines = gup_file_read_lines_keep_newlines("./resources/one_newline.txt");

        gup_assert(lines.count == 1);
        gup_assert(gup_array_char_eq_cstr(lines.data[0], "\n"));

        gup_array_string_destroy(lines);
    }

    { // foo.txt
        GupArrayString lines = gup_file_read_lines_keep_newlines("./resources/foo.txt");

        gup_assert(lines.count == 4);
        gup_assert(gup_array_char_eq_cstr(lines.data[0], "one\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[1], "twotwo\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[2], "three three three\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[3], "\n"));

        gup_array_string_destroy(lines);
    }

    { // settings.toml
        GupArrayString lines = gup_file_read_lines_keep_newlines("./resources/settings.toml");

        gup_assert(lines.count == 8);
        gup_assert(gup_array_char_eq_cstr(lines.data[0], "# This is a TOML file\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[1], "\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[2], "title = \"guppy.h\"\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[3], "author = \"Christian Bouwense\"\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[4], "\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[5], "[database]\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[6], "server = \"localhost\"\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[7], "port = 5432\n"));

        gup_array_string_destroy(lines);
    }
}

void test_gup_file_read_lines_keep_newlines_arena(GupArena *a) {
    { // empty.txt
        GupArrayString lines = gup_file_read_lines_keep_newlines("./resources/empty.txt");

        gup_assert(lines.count == 0);
    }

    { // one_newline.txt
        GupArrayString lines = gup_file_read_lines_keep_newlines_arena(a, "./resources/one_newline.txt");

        gup_assert(lines.count == 1);
        gup_assert(gup_array_char_eq_cstr(lines.data[0], "\n"));
    }

    { // foo.txt
        GupArrayString lines = gup_file_read_lines_keep_newlines_arena(a, "./resources/foo.txt");

        gup_assert(lines.count == 4);
        gup_assert(gup_array_char_eq_cstr(lines.data[0], "one\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[1], "twotwo\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[2], "three three three\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[3], "\n"));
    }

    { // settings.toml
        GupArrayString lines = gup_file_read_lines_keep_newlines_arena(a, "./resources/settings.toml");

        gup_assert(lines.count == 8);
        gup_assert(gup_array_char_eq_cstr(lines.data[0], "# This is a TOML file\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[1], "\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[2], "title = \"guppy.h\"\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[3], "author = \"Christian Bouwense\"\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[4], "\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[5], "[database]\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[6], "server = \"localhost\"\n"));
        gup_assert(gup_array_char_eq_cstr(lines.data[7], "port = 5432\n"));
    }
}

void test_gup_file_read_lines_as_cstrs(void) {
    char **lines = NULL;

    { // empty.txt
        lines = gup_file_read_lines_as_cstrs("./resources/empty.txt");

        gup_assert(lines == NULL);
    }

    { // one_newline.txt
        lines = gup_file_read_lines_as_cstrs("./resources/one_newline.txt");

        gup_assert(strcmp(lines[0], "") == 0);
        gup_assert(lines[1] == NULL);

        free(lines[0]);
        free(lines);
    }

    { // foo.txt
        lines = gup_file_read_lines_as_cstrs("./resources/foo.txt");

        gup_assert(strcmp(lines[0], "one") == 0);
        gup_assert(strcmp(lines[1], "twotwo") == 0);
        gup_assert(strcmp(lines[2], "three three three") == 0);
        gup_assert(strcmp(lines[3], "") == 0);
        gup_assert(lines[4] == NULL);

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

        gup_assert(strcmp(lines[0], "# This is a TOML file") == 0);
        gup_assert(strcmp(lines[1], "") == 0);
        gup_assert(strcmp(lines[2], "title = \"guppy.h\"") == 0);
        gup_assert(strcmp(lines[3], "author = \"Christian Bouwense\"") == 0);
        gup_assert(strcmp(lines[4], "") == 0);
        gup_assert(strcmp(lines[5], "[database]") == 0);
        gup_assert(strcmp(lines[6], "server = \"localhost\"") == 0);
        gup_assert(strcmp(lines[7], "port = 5432") == 0);
        gup_assert(lines[8] == NULL);

        
        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
    }

}

void test_gup_file_read_lines_as_cstrs_arena(GupArena *a) {
    char **lines = NULL;

    { // empty.txt
        lines = gup_file_read_lines_as_cstrs_arena(a, "./resources/empty.txt");

        gup_assert(lines == NULL);
    }

    { // one_newline.txt
        lines = gup_file_read_lines_as_cstrs_arena(a, "./resources/one_newline.txt");

        gup_assert(strcmp(lines[0], "") == 0);
        gup_assert(lines[1] == NULL);
    }

    { // foo.txt
        lines = gup_file_read_lines_as_cstrs_arena(a, "./resources/foo.txt");

        gup_assert(strcmp(lines[0], "one") == 0);
        gup_assert(strcmp(lines[1], "twotwo") == 0);
        gup_assert(strcmp(lines[2], "three three three") == 0);
        gup_assert(strcmp(lines[3], "") == 0);
        gup_assert(lines[4] == NULL);
    }

    { // settings.toml
        lines = gup_file_read_lines_as_cstrs_arena(a, "./resources/settings.toml");
        
        #ifdef GUPPY_VERBOSE
        gup_file_print("./resources/settings.toml");
        for (int i = 0; i < line_count; i++) {
            printf("%s\n", lines[i]);
        }
        #endif

        gup_assert(strcmp(lines[0], "# This is a TOML file") == 0);
        gup_assert(strcmp(lines[1], "") == 0);
        gup_assert(strcmp(lines[2], "title = \"guppy.h\"") == 0);
        gup_assert(strcmp(lines[3], "author = \"Christian Bouwense\"") == 0);
        gup_assert(strcmp(lines[4], "") == 0);
        gup_assert(strcmp(lines[5], "[database]") == 0);
        gup_assert(strcmp(lines[6], "server = \"localhost\"") == 0);
        gup_assert(strcmp(lines[7], "port = 5432") == 0);
        gup_assert(lines[8] == NULL);
    }
}

void test_gup_file_read_lines_as_cstrs_keep_newlines(void) {
    char **lines = NULL;

    { // empty.txt
        lines = gup_file_read_lines_as_cstrs_keep_newlines("./resources/empty.txt");

        gup_assert(lines == NULL);
    }

    { // one_newline.txt
        lines = gup_file_read_lines_as_cstrs_keep_newlines("./resources/one_newline.txt");

        gup_assert(strcmp(lines[0], "\n") == 0);
        gup_assert(lines[1] == NULL);

        free(lines[0]);
        free(lines);
    }

    { // foo.txt
        lines = gup_file_read_lines_as_cstrs_keep_newlines("./resources/foo.txt");

        gup_assert(strcmp(lines[0], "one\n") == 0);
        gup_assert(strcmp(lines[1], "twotwo\n") == 0);
        gup_assert(strcmp(lines[2], "three three three\n") == 0);
        gup_assert(strcmp(lines[3], "\n") == 0);
        gup_assert(lines[4] == NULL);

        const int line_count = gup_file_line_count("./resources/foo.txt");
        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
    }

    { // settings.toml
        lines = gup_file_read_lines_as_cstrs_keep_newlines("./resources/settings.toml");

        gup_assert(strcmp(lines[0], "# This is a TOML file\n") == 0);
        gup_assert(strcmp(lines[1], "\n") == 0);
        gup_assert(strcmp(lines[2], "title = \"guppy.h\"\n") == 0);
        gup_assert(strcmp(lines[3], "author = \"Christian Bouwense\"\n") == 0);
        gup_assert(strcmp(lines[4], "\n") == 0);
        gup_assert(strcmp(lines[5], "[database]\n") == 0);
        gup_assert(strcmp(lines[6], "server = \"localhost\"\n") == 0);
        gup_assert(strcmp(lines[7], "port = 5432\n") == 0);
        gup_assert(lines[8] == NULL);

        const int line_count = gup_file_line_count("./resources/settings.toml");
        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
    }

}

void test_gup_file_read_lines_as_cstrs_keep_newlines_arena(GupArena *a) {
    char **lines = NULL;

    { // empty.txt
        lines = gup_file_read_lines_as_cstrs_keep_newlines_arena(a, "./resources/empty.txt");

        gup_assert(lines == NULL);
    }

    { // one_newline.txt
        lines = gup_file_read_lines_as_cstrs_keep_newlines_arena(a, "./resources/one_newline.txt");

        gup_assert(strcmp(lines[0], "\n") == 0);
        gup_assert(lines[1] == NULL);
    }

    { // foo.txt
        lines = gup_file_read_lines_as_cstrs_keep_newlines_arena(a, "./resources/foo.txt");

        gup_assert(strcmp(lines[0], "one\n") == 0);
        gup_assert(strcmp(lines[1], "twotwo\n") == 0);
        gup_assert(strcmp(lines[2], "three three three\n") == 0);
        gup_assert(strcmp(lines[3], "\n") == 0);
        gup_assert(lines[4] == NULL);
    }

    { // settings.toml
        lines = gup_file_read_lines_as_cstrs_keep_newlines_arena(a, "./resources/settings.toml");

        gup_assert(strcmp(lines[0], "# This is a TOML file\n") == 0);
        gup_assert(strcmp(lines[1], "\n") == 0);
        gup_assert(strcmp(lines[2], "title = \"guppy.h\"\n") == 0);
        gup_assert(strcmp(lines[3], "author = \"Christian Bouwense\"\n") == 0);
        gup_assert(strcmp(lines[4], "\n") == 0);
        gup_assert(strcmp(lines[5], "[database]\n") == 0);
        gup_assert(strcmp(lines[6], "server = \"localhost\"\n") == 0);
        gup_assert(strcmp(lines[7], "port = 5432\n") == 0);
        gup_assert(lines[8] == NULL);
    }

}

void test_gup_file_write(GupArena *a) {
    gup_file_delete("./resources/empty_write.txt");
    gup_file_delete("./resources/hello.txt");
    gup_file_delete("./resources/hello_world.txt");

    { // Empty line write
        GupString str = gup_string(a, "");
        GupString file_contents = {0};

        gup_assert(gup_file_write_arena(a, str, "./resources/empty_write.txt"));
        gup_assert(gup_file_read_arena(a, "./resources/empty_write.txt", &file_contents));

        gup_assert(gup_string_eq(file_contents, str));
    }

    { // Single line write
        GupString str = gup_string(a, "Hello");
        GupString file_contents = {0};

        gup_assert(gup_file_write_arena(a, str, "./resources/hello.txt"));
        gup_assert(gup_file_read_arena(a, "./resources/hello.txt", &file_contents));

        gup_assert(gup_string_eq(file_contents, str));
    }

    { // Multi line write
        GupString str = gup_string(a, "Hello\nWorld\n");
        GupString file_contents = {0};

        gup_assert(gup_file_write_arena(a, str, "./resources/hello_world.txt"));
        gup_assert(gup_file_read_arena(a, "./resources/hello_world.txt", &file_contents));

        gup_assert(gup_string_eq(file_contents, str));
    }
}

void test_gup_file_write_lines(GupArena *a) {
    char *file_contents = NULL;

    gup_file_delete("./resources/empty_write_lines.txt");
    gup_file_delete("./resources/hello_lines.txt");
    gup_file_delete("./resources/hello_world_lines.txt");

    { // No lines write
        GupArrayString lines = {0};

        gup_file_write_lines_arena(a, lines, "./resources/empty_write_lines.txt");
        gup_assert(gup_file_read_as_cstr_arena(a, "./resources/empty_write_lines.txt", &file_contents));

        gup_assert(strcmp(file_contents, "") == 0);
    }

    { // Single line write
        GupArrayString lines = gup_array_string_create_arena(a);
        gup_array_string_append_cstr_arena(a, &lines, "Hello");

        gup_file_write_lines_arena(a, lines, "./resources/hello_lines.txt");
        gup_assert(gup_file_read_as_cstr_arena(a, "./resources/hello_lines.txt", &file_contents));

        gup_assert(strcmp(file_contents, "Hello\n") == 0);
    }

    { // Multi line write
        GupArrayString lines = gup_array_string_create_arena(a);
        gup_array_string_append_cstr_arena(a, &lines, "Hello");
        gup_array_string_append_cstr_arena(a, &lines, "World");
        gup_array_string_append_cstr_arena(a, &lines, "!");

        gup_file_write_lines_arena(a, lines, "./resources/hello_world_lines.txt");
        gup_assert(gup_file_read_as_cstr_arena(a, "./resources/hello_world_lines.txt", &file_contents));

        gup_assert(strcmp(file_contents, "Hello\nWorld\n!\n") == 0);
    }
}

void test_gup_file_size() {
    long file_size = 0;
    
    gup_assert(gup_file_size("./resources/empty.txt", &file_size));
    gup_assert_verbose(file_size == 0, "Expected empty.txt to have 0 characters");

    gup_assert(gup_file_size("./resources/hello.txt", &file_size));
    gup_assert_verbose(file_size == 5, "Expected hello.txt to have 5 characters");
}

void test_gup_file_print() {
    gup_file_print("./resources/doesnotexist.txt");
    gup_file_print("./resources/empty.txt");
    gup_file_print("./resources/one_newline.txt");
    gup_file_print("./resources/foo.txt");
    gup_file_print("./resources/settings.toml");
}

void test_gup_file_print_lines() {
    gup_file_print_lines("./resources/doesnotexist.txt");
    gup_file_print_lines("./resources/empty.txt");
    gup_file_print_lines("./resources/one_newline.txt");
    gup_file_print_lines("./resources/foo.txt");
    gup_file_print_lines("./resources/settings.toml");
}

void test_gup_file(void) {
    GupArena a = gup_arena_create();

    test_gup_file_is_empty();
    test_gup_file_line_count();
    test_gup_file_read();
    test_gup_file_read_arena(&a);
    test_gup_file_read_as_cstr();
    test_gup_file_read_as_cstr_arena(&a);
    test_gup_file_read_lines();
    test_gup_file_read_lines_arena(&a);
    test_gup_file_read_lines_keep_newlines();
    test_gup_file_read_lines_keep_newlines_arena(&a);
    test_gup_file_read_lines_as_cstrs();
    test_gup_file_read_lines_as_cstrs_arena(&a);
    test_gup_file_read_lines_as_cstrs_keep_newlines();
    test_gup_file_read_lines_as_cstrs_keep_newlines_arena(&a);
    test_gup_file_size();
    test_gup_file_write(&a);
    test_gup_file_write_lines(&a);
    #ifdef GUPPY_VERBOSE
    test_gup_file_print();
    test_gup_file_print_lines();
    #endif // GUPPY_VERBOSE

    gup_arena_destroy(&a);
}
