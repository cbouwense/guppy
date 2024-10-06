#include "../src/guppy.h"

bool is_bang(char c) {
    return c == '!';
}

void test_gup_string_creates_an_empty_string(void) {
    GupString str = gup_string_create();

    gup_assert(gup_string_eq_cstr(str, ""));

    gup_string_destroy(str);
}

void test_creating_a_gup_string_from_a_cstr_equals_that_cstr(void) {
    GupString str = gup_string_create_from_cstr("Hello World!");
    
    gup_assert(gup_string_eq_cstr(str, "Hello World!"));

    gup_string_destroy(str);
}

void test_gup_string_array_flatten(void) {
    { // Empty array
        char *array[] = {NULL};
        char *string = gup_string_array_flatten(array);

        assert(strcmp(string, "") == 0);

        free(string);
    }

    { // One element
        char *array[] = {"one", NULL};
        char *string = gup_string_array_flatten(array);

        assert(strcmp(string, "one") == 0);

        free(string);
    }

    { // Multiple elements
        char *array[] = {"one", "two", "three", NULL};
        char *string = gup_string_array_flatten(array);

        assert(strcmp(string, "onetwothree") == 0);

        free(string);
    }
}

void test_gup_string_trim_functions(void) {
    { // Trimming unfound characters does nothing
        GupString str = gup_string_create_from_cstr("Hello");
        GupString trimmed = gup_string_trim_char(str, '!');

        gup_assert(gup_string_eq(str, trimmed));

        gup_string_destroy(str);
        gup_string_destroy(trimmed);
    }

    { // Trimming takes off only those characters at the beginning and end of the string
        GupString str = gup_string_create_from_cstr("!!!He!ll!o!!");
        GupString trimmed = gup_string_trim_char(str, '!');

        gup_assert(gup_string_eq_cstr(trimmed, "He!ll!o"));

        gup_string_destroy(str);
        gup_string_destroy(trimmed);
    }

    { // Trimming by function unfound characters does nothing
        GupString str = gup_string_create_from_cstr("Hello");
        GupString trimmed = gup_string_trim_fn(str, is_bang);

        gup_assert(gup_string_eq(str, trimmed));

        gup_string_destroy(str);
        gup_string_destroy(trimmed);
    }

    { // Trimming by function takes off only those characters at the beginning and end of the string
        GupString str = gup_string_create_from_cstr("!!!He!ll!o!!");
        GupString trimmed = gup_string_trim_fn(str, is_bang);

        gup_assert(gup_string_eq_cstr(trimmed, "He!ll!o"));

        gup_string_destroy(str);
        gup_string_destroy(trimmed);
    }

    { // Trimming in place unfound characters does nothing
        GupString str = gup_string_create_from_cstr("Hello");
        gup_string_trim_char_in_place(&str, '!');

        gup_assert(gup_string_eq_cstr(str, "Hello"));

        gup_string_destroy(str);
    }

    { // Trimming in place takes off only those characters at the beginning and end of the string
        GupString str = gup_string_create_from_cstr("!!!He!ll!o!!");
        gup_string_trim_char_in_place(&str, '!');

        gup_assert(gup_string_eq_cstr(str, "He!ll!o"));

        gup_string_destroy(str);
    }

    { // Trimming by function in place unfound characters does nothing
        GupString str = gup_string_create_from_cstr("Hello");
        gup_string_trim_fn_in_place(&str, is_bang);

        gup_assert(gup_string_eq_cstr(str, "Hello"));

        gup_string_destroy(str);
    }

    { // Trimming by function in place takes off only those characters at the beginning and end of the string
        GupString str = gup_string_create_from_cstr("!!!He!ll!o!!");
        gup_string_trim_fn_in_place(&str, is_bang);

        gup_assert(gup_string_eq_cstr(str, "He!ll!o"));

        gup_string_destroy(str);
    }
}

void test_gup_string_split(void) {
    { // Two tokens
        GupString str = gup_string_create_from_cstr("foo=bar");
        GupArrayString tokens = gup_string_split(str, '=');
        char *expected_array[2] = {"foo", "bar"};
        GupArrayString expected = gup_array_string_create_from_cstrs(expected_array, 2);

        gup_assert(gup_array_string_eq(tokens, expected));

        gup_array_string_destroy(expected);
        gup_array_string_destroy(tokens);
        gup_string_destroy(str);
    }

    { // Five tokens
        GupString str = gup_string_create_from_cstr("foo=bar=baz=shib=dib");
        GupArrayString tokens = gup_string_split(str, '=');
        char *expected_array[5] = {"foo", "bar", "baz", "shib", "dib"};
        GupArrayString expected = gup_array_string_create_from_cstrs(expected_array, 5);

        gup_assert(gup_array_string_eq(tokens, expected));

        gup_array_string_destroy(expected);
        gup_array_string_destroy(tokens);
        gup_string_destroy(str);
    }
}

void test_gup_string(void) {
    test_gup_string_creates_an_empty_string();
    test_creating_a_gup_string_from_a_cstr_equals_that_cstr();
    test_gup_string_array_flatten();
    test_gup_string_trim_functions();
    test_gup_string_split();
}
