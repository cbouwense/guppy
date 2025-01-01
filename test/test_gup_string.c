#include "../src/guppy.h"

bool is_bang(char c) {
    return c == '!';
}

void test_gup_string_creates_an_empty_string(GupAllocator *a) {
    GupString str = gup_string(a, "");

    gup_assert(gup_string_equals_cstr(str, ""));
}

void test_creating_a_gup_string_from_a_cstr_equals_that_cstr(GupAllocator *a) {
    GupString str = gup_string(a, "Hello World!");
    
    gup_assert(gup_string_equals_cstr(str, "Hello World!"));
}

void test_gup_string_trim_functions(GupAllocator *a) {
    { // Trimming unfound characters does nothing
        GupString str = gup_string(a, "Hello");
        GupString trimmed = gup_string_trim_char(a, str, '!');

        gup_assert(gup_string_equals(str, trimmed));
    }

    { // Trimming takes off only those characters at the beginning and end of the string
        GupString str = gup_string(a, "!!!He!ll!o!!");
        GupString trimmed = gup_string_trim_char(a, str, '!');

        gup_assert(gup_string_equals_cstr(trimmed, "He!ll!o"));
    }

    { // Trimming by function unfound characters does nothing
        GupString str = gup_string(a, "Hello");
        GupString trimmed = gup_string_trim_fn(a, str, is_bang);

        gup_assert(gup_string_equals(str, trimmed));
    }

    { // Trimming by function takes off only those characters at the beginning and end of the string
        GupString str = gup_string(a, "!!!He!ll!o!!");
        GupString trimmed = gup_string_trim_fn(a, str, is_bang);

        gup_assert(gup_string_equals_cstr(trimmed, "He!ll!o"));
    }

    { // Trimming in place unfound characters does nothing
        GupString str = gup_string(a, "Hello");
        gup_string_trim_char_in_place(&str, '!');

        gup_assert(gup_string_equals_cstr(str, "Hello"));
    }

    { // Trimming in place takes off only those characters at the beginning and end of the string
        GupString str = gup_string(a, "!!!He!ll!o!!");
        gup_string_trim_char_in_place(&str, '!');

        gup_assert(gup_string_equals_cstr(str, "He!ll!o"));
    }

    { // Trimming by function in place unfound characters does nothing
        GupString str = gup_string(a, "Hello");
        gup_string_trim_fn_in_place(&str, is_bang);

        gup_assert(gup_string_equals_cstr(str, "Hello"));
    }

    { // Trimming by function in place takes off only those characters at the beginning and end of the string
        GupString str = gup_string(a, "!!!He!ll!o!!");
        gup_string_trim_fn_in_place(&str, is_bang);

        gup_assert(gup_string_equals_cstr(str, "He!ll!o"));
    }
}

void test_gup_string_split(GupAllocator *a) {
    { // No delimiters
        GupString str = gup_string(a, "foobar");
        GupArrayString tokens = gup_string_split(a, str, '=');

        gup_assert(gup_string_equals(str, tokens.data[0]));
        gup_assert(tokens.count == 1);
    }

    { // Some delimiters around the edges
        GupString str = gup_string(a, "=foobar==");
        GupArrayString tokens = gup_string_split(a, str, '=');

        gup_assert(gup_string_equals_cstr(tokens.data[0], "foobar"));
        gup_assert(tokens.count == 1);
    }

    { // A bunch of delimiters
        GupString str = gup_string(a, "==foo=bar=baz=shib=dib===");
        GupArrayString tokens = gup_string_split(a, str, '=');
        char *expected_array[5] = {"foo", "bar", "baz", "shib", "dib"};
        GupArrayString expected = gup_array_string_create_from_cstrs(a, expected_array, 5);

        gup_assert(gup_array_string_equals(tokens, expected));
    }
}

void test_gup_string_starts_with(GupAllocator *a) {
    { // A string starts with itself 
        GupString sub_str = gup_string(a, "Hello");
        GupString str = gup_string_copy(a, sub_str);

        gup_assert(gup_string_starts_with(str, sub_str) == true);
    }

    { // Even after appending it works
        GupString sub_str = gup_string(a, "Hello");
        GupString str = gup_string_copy(a, sub_str);
        gup_string_append(a, &str, '!');

        gup_assert(gup_string_starts_with(str, sub_str) == true);
    }

    { // After prepending something else it is false
        GupString sub_str = gup_string(a, "Hello");
        GupString str = gup_string_copy(a, sub_str);

        gup_string_prepend(a, &str, '!');

        gup_assert(gup_string_starts_with(str, sub_str) == false);
    }

    { // Don't count strings as technically starting with empty strings
        GupString sub_str = gup_string(a, "");
        GupString str = gup_string_copy(a, sub_str);

        gup_assert(gup_string_starts_with(str, sub_str) == false);
    }
}

void test_gup_string_starts_with_cstr(GupAllocator *a) {
    { // A string starts with itself 
        char *cstr = "Hello";
        GupString str = gup_string(a, cstr);

        gup_assert(gup_string_starts_with_cstr(str, cstr) == true);
    }

    { // Even after appending it works
        char *cstr = "Hello";
        GupString str = gup_string(a, cstr);
        gup_string_append(a, &str, '!');

        gup_assert(gup_string_starts_with_cstr(str, cstr) == true);
    }

    { // After prepending something else it is false
        char *cstr = "Hello";
        GupString str = gup_string(a, cstr);

        gup_string_prepend(a, &str, '!');

        gup_assert(gup_string_starts_with_cstr(str, cstr) == false);
    }

    { // Don't count strings as technically starting with empty strings
        char *cstr = "";
        GupString str = gup_string(a, cstr);

        gup_assert(gup_string_starts_with_cstr(str, cstr) == false);
    }
}

void test_gup_string_ends_with(GupAllocator *a) {
    { // A string ends with itself 
        GupString sub_str = gup_string(a, "Hello");
        GupString str = gup_string_copy(a, sub_str);

        gup_assert(gup_string_ends_with(str, sub_str) == true);
    }

    { // After appending something it returns false
        GupString sub_str = gup_string(a, "Hello");
        GupString str = gup_string_copy(a, sub_str);
        gup_string_append(a, &str, '!');

        gup_assert(gup_string_ends_with(str, sub_str) == false);
    }

    { // Prepending something doesn't change anything
        GupString sub_str = gup_string(a, "Hello");
        GupString str = gup_string_copy(a, sub_str);
        gup_string_prepend(a, &str, '!');

        gup_assert(gup_string_ends_with(str, sub_str) == true);
    }

    { // Don't count strings as technically ending with empty strings
        GupString sub_str = gup_string(a, "");
        GupString str = gup_string_copy(a, sub_str);

        gup_assert(gup_string_ends_with(str, sub_str) == false);
    }
}

void test_gup_string_ends_with_cstr(GupAllocator *a) {
    { // A string ends with itself 
        char *cstr = "Hello";
        GupString str = gup_string(a, cstr);

        gup_assert(gup_string_ends_with_cstr(str, cstr) == true);
    }

    { // After appending something it returns false
        char *cstr = "Hello";
        GupString str = gup_string(a, cstr);
        gup_string_append(a, &str, '!');

        gup_assert(gup_string_ends_with_cstr(str, cstr) == false);
    }

    { // Prepending something doesn't change anything
        char *cstr = "Hello";
        GupString str = gup_string(a, cstr);
        gup_string_prepend(a, &str, '!');

        gup_assert(gup_string_ends_with_cstr(str, cstr) == true);
    }

    { // Don't count strings as technically ending with empty strings
        char *cstr = "";
        GupString str = gup_string(a, cstr);

        gup_assert(gup_string_ends_with_cstr(str, cstr) == false);
    }
}

void test_gup_string_contains_substring(GupAllocator *a) {
    { // Never count containing empty strings
        GupString str = gup_string(a, "Hello");
        GupString sub_str = gup_string(a, "");

        gup_assert(false == gup_string_contains_substring(str, sub_str));
    }

    { // Strings contain themselves
        GupString str = gup_string(a, "Hello");

        gup_assert(true == gup_string_contains_substring(str, str));
    }

    { // Strings contain copies of themselves
        GupString str = gup_string(a, "Hello");
        GupString sub_str = gup_string_copy(a, str);

        gup_assert(true == gup_string_contains_substring(str, sub_str));
    }

    {
        GupString str = gup_string(a, "Hello");
        GupString sub_str = gup_string(a, "ello");

        gup_assert(true == gup_string_contains_substring(str, sub_str));
    }

    {
        GupString str = gup_string(a, "Hello");
        GupString sub_str = gup_string(a, "Helloooooo");

        gup_assert(false == gup_string_contains_substring(str, sub_str));
    }

    

    {
        GupString str = gup_string(a, "Hello");
        GupString sub_str = gup_string(a, "Chello");

        gup_assert(false == gup_string_contains_substring(str, sub_str));
    }
}

void test_gup_string_to_int(GupAllocator *a) {
    int actual = 0;
    GupString str = gup_string(a, "1337");

    gup_assert_verbose(gup_string_to_int(str, &actual), "Should've been able to parse an int from the string but couldn't");
    gup_assert_verbose(actual == 1337, "Didn't successfully parse 1337 from the string that was \"1337\"");
}

void test_gup_string(void) {
    GupArena a = gup_arena_create();

    test_gup_string_creates_an_empty_string((GupAllocator *)&a);
    test_creating_a_gup_string_from_a_cstr_equals_that_cstr((GupAllocator *)&a);
    test_gup_string_trim_functions((GupAllocator *)&a);
    test_gup_string_split((GupAllocator *)&a);
    test_gup_string_starts_with((GupAllocator *)&a);
    test_gup_string_starts_with_cstr((GupAllocator *)&a);
    test_gup_string_ends_with((GupAllocator *)&a);
    test_gup_string_ends_with_cstr((GupAllocator *)&a);
    test_gup_string_contains_substring((GupAllocator *)&a);
    test_gup_string_to_int((GupAllocator *)&a);

    gup_arena_destroy(&a);
}
