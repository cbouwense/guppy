#include "../src/guppy.h"

bool is_bang(char c) {
    return c == '!';
}

void test_gup_string_creates_an_empty_string(void) {
    GupString str = gup_string_create();

    gup_assert(gup_string_eq_cstr(str, ""));
}

void test_creating_a_gup_string_from_a_cstr_equals_that_cstr(void) {
    GupString str = gup_string_create_from_cstr("Hello World!");
    
    gup_assert(gup_string_eq_cstr(str, "Hello World!"));
}

void test_gup_string_array_flatten(void) {
    { // Empty array
        char *array[] = {NULL};
        char *string = gup_string_array_flatten(array);

        gup_assert(strcmp(string, "") == 0);
    }

    { // One element
        char *array[] = {"one", NULL};
        char *string = gup_string_array_flatten(array);

        gup_assert(strcmp(string, "one") == 0);
    }

    { // Multiple elements
        char *array[] = {"one", "two", "three", NULL};
        char *string = gup_string_array_flatten(array);

        gup_assert(strcmp(string, "onetwothree") == 0);
    }
}

void test_gup_string_trim_functions(void) {
    { // Trimming unfound characters does nothing
        GupString str = gup_string_create_from_cstr("Hello");
        GupString trimmed = gup_string_trim_char(str, '!');

        gup_assert(gup_string_eq(str, trimmed));
    }

    { // Trimming takes off only those characters at the beginning and end of the string
        //                                              He!ll!o!!o
        GupString str = gup_string_create_from_cstr("!!!He!ll!o!!");
        GupString trimmed = gup_string_trim_char(str, '!');

        gup_assert(gup_string_eq_cstr(trimmed, "He!ll!o"));
    }

    { // Trimming by function unfound characters does nothing
        GupString str = gup_string_create_from_cstr("Hello");
        GupString trimmed = gup_string_trim_fn(str, is_bang);

        gup_assert(gup_string_eq(str, trimmed));
    }

    { // Trimming by function takes off only those characters at the beginning and end of the string
        GupString str = gup_string_create_from_cstr("!!!He!ll!o!!");
        GupString trimmed = gup_string_trim_fn(str, is_bang);

        gup_assert(gup_string_eq_cstr(trimmed, "He!ll!o"));
    }

    { // Trimming in place unfound characters does nothing
        GupString str = gup_string_create_from_cstr("Hello");
        gup_string_trim_char_in_place(&str, '!');

        gup_assert(gup_string_eq_cstr(str, "Hello"));
    }

    { // Trimming in place takes off only those characters at the beginning and end of the string
        GupString str = gup_string_create_from_cstr("!!!He!ll!o!!");
        gup_string_trim_char_in_place(&str, '!');

        gup_assert(gup_string_eq_cstr(str, "He!ll!o"));
    }

    { // Trimming by function in place unfound characters does nothing
        GupString str = gup_string_create_from_cstr("Hello");
        gup_string_trim_fn_in_place(&str, is_bang);

        gup_assert(gup_string_eq_cstr(str, "Hello"));
    }

    { // Trimming by function in place takes off only those characters at the beginning and end of the string
        GupString str = gup_string_create_from_cstr("!!!He!ll!o!!");
        gup_string_trim_fn_in_place(&str, is_bang);

        gup_assert(gup_string_eq_cstr(str, "He!ll!o"));
    }
}

void test_gup_string_split(void) {
    { // No delimiters
        GupString str = gup_string_create_from_cstr("foobar");
        GupArrayString tokens = gup_string_split(str, '=');

        gup_assert(gup_string_eq(str, tokens.data[0]));
        gup_assert(tokens.count == 1);
    }

    { // Some delimiters around the edges
        GupString str = gup_string_create_from_cstr("=foobar==");
        GupArrayString tokens = gup_string_split(str, '=');

        gup_assert(gup_string_eq_cstr(tokens.data[0], "foobar"));
        gup_assert(tokens.count == 1);
    }

    { // A bunch of delimiters
        GupString str = gup_string_create_from_cstr("==foo=bar=baz=shib=dib===");
        GupArrayString tokens = gup_string_split(str, '=');
        char *expected_array[5] = {"foo", "bar", "baz", "shib", "dib"};
        GupArrayString expected = gup_array_string_create_from_cstrs(expected_array, 5);

        gup_assert(gup_array_string_eq(tokens, expected));
    }
}

void test_gup_string_starts_with(GupArena *a) {
    { // A string starts with itself 
        GupString sub_str = gup_string_create_from_cstr_arena(a, "Hello");
        GupString str = gup_string_copy_arena(a, sub_str);

        gup_assert(gup_string_starts_with(str, sub_str) == true);
    }

    { // Even after appending it works
        GupString sub_str = gup_string_create_from_cstr_arena(a, "Hello");
        GupString str = gup_string_copy_arena(a, sub_str);
        gup_string_append_arena(a, &str, '!');

        gup_assert(gup_string_starts_with(str, sub_str) == true);
    }

    { // After prepending something else it is false
        GupString sub_str = gup_string_create_from_cstr_arena(a, "Hello");
        GupString str = gup_string_copy_arena(a, sub_str);

        gup_string_prepend_arena(a, &str, '!');

        gup_assert(gup_string_starts_with(str, sub_str) == false);
    }

    { // Don't count strings as technically starting with empty strings
        GupString sub_str = gup_string_create_from_cstr_arena(a, "");
        GupString str = gup_string_copy_arena(a, sub_str);

        gup_assert(gup_string_starts_with(str, sub_str) == false);
    }
}

void test_gup_string_starts_with_cstr(GupArena *a) {
    { // A string starts with itself 
        char *cstr = "Hello";
        GupString str = gup_string_create_from_cstr_arena(a, cstr);

        gup_assert(gup_string_starts_with_cstr(str, cstr) == true);
    }

    { // Even after appending it works
        char *cstr = "Hello";
        GupString str = gup_string_create_from_cstr_arena(a, cstr);
        gup_string_append_arena(a, &str, '!');

        gup_assert(gup_string_starts_with_cstr(str, cstr) == true);
    }

    { // After prepending something else it is false
        char *cstr = "Hello";
        GupString str = gup_string_create_from_cstr_arena(a, cstr);

        gup_string_prepend_arena(a, &str, '!');

        gup_assert(gup_string_starts_with_cstr(str, cstr) == false);
    }

    { // Don't count strings as technically starting with empty strings
        char *cstr = "";
        GupString str = gup_string_create_from_cstr_arena(a, cstr);

        gup_assert(gup_string_starts_with_cstr(str, cstr) == false);
    }
}

void test_gup_string_ends_with(GupArena *a) {
    { // A string ends with itself 
        GupString sub_str = gup_string_create_from_cstr_arena(a, "Hello");
        GupString str = gup_string_copy_arena(a, sub_str);

        gup_assert(gup_string_ends_with(str, sub_str) == true);
    }

    { // After appending something it returns false
        GupString sub_str = gup_string_create_from_cstr_arena(a, "Hello");
        GupString str = gup_string_copy_arena(a, sub_str);
        gup_string_append_arena(a, &str, '!');

        gup_assert(gup_string_ends_with(str, sub_str) == false);
    }

    { // Prepending something doesn't change anything
        GupString sub_str = gup_string_create_from_cstr_arena(a, "Hello");
        GupString str = gup_string_copy_arena(a, sub_str);
        gup_string_prepend_arena(a, &str, '!');

        gup_assert(gup_string_ends_with(str, sub_str) == true);
    }

    { // Don't count strings as technically ending with empty strings
        GupString sub_str = gup_string_create_from_cstr_arena(a, "");
        GupString str = gup_string_copy_arena(a, sub_str);

        gup_assert(gup_string_ends_with(str, sub_str) == false);
    }
}

void test_gup_string_ends_with_cstr(GupArena *a) {
    { // A string ends with itself 
        char *cstr = "Hello";
        GupString str = gup_string_create_from_cstr_arena(a, cstr);

        gup_assert(gup_string_ends_with_cstr(str, cstr) == true);
    }

    { // After appending something it returns false
        char *cstr = "Hello";
        GupString str = gup_string_create_from_cstr_arena(a, cstr);
        gup_string_append_arena(a, &str, '!');

        gup_assert(gup_string_ends_with_cstr(str, cstr) == false);
    }

    { // Prepending something doesn't change anything
        char *cstr = "Hello";
        GupString str = gup_string_create_from_cstr_arena(a, cstr);
        gup_string_prepend_arena(a, &str, '!');

        gup_assert(gup_string_ends_with_cstr(str, cstr) == true);
    }

    { // Don't count strings as technically ending with empty strings
        char *cstr = "";
        GupString str = gup_string_create_from_cstr_arena(a, cstr);

        gup_assert(gup_string_ends_with_cstr(str, cstr) == false);
    }
}

void test_gup_string(void) {
    GupArena a = gup_arena_create();

    test_gup_string_creates_an_empty_string();
    test_creating_a_gup_string_from_a_cstr_equals_that_cstr();
    test_gup_string_array_flatten();
    test_gup_string_trim_functions();
    test_gup_string_split();
    test_gup_string_starts_with(&a);
    test_gup_string_starts_with_cstr(&a);
    test_gup_string_ends_with(&a);
    test_gup_string_ends_with_cstr(&a);

    gup_arena_destroy(a);
}
