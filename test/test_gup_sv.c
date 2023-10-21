#include "../src/guppy.h"

void test_gup_sv(void) {
    { // gup_sv_trim_left
        {
            Gup_String_View sv = gup_sv_from_cstr("  Hello, world!  ");
            Gup_String_View trimmed = gup_sv_trim_left(sv);

            assert(gup_sv_eq_cstr(trimmed, "Hello, world!  "));
        }

        {
            Gup_String_View sv = gup_sv_from_cstr("Hello, world!  ");
            Gup_String_View trimmed = gup_sv_trim_left(sv);

            assert(gup_sv_eq_cstr(trimmed, "Hello, world!  "));
        }

        { // Empty string
            Gup_String_View sv = gup_sv_from_cstr("");
            Gup_String_View trimmed = gup_sv_trim_left(sv);

            assert(gup_sv_eq_cstr(trimmed, ""));
        }

        { // Whitespace string
            Gup_String_View sv = gup_sv_from_cstr("  ");
            Gup_String_View trimmed = gup_sv_trim_left(sv);

            assert(gup_sv_eq_cstr(trimmed, ""));
        }
    }

    { // gup_sv_trim_right
        {
            Gup_String_View sv = gup_sv_from_cstr("  Hello, world!  ");
            Gup_String_View trimmed = gup_sv_trim_right(sv);

            assert(gup_sv_eq_cstr(trimmed, "  Hello, world!"));
        }

        {
            Gup_String_View sv = gup_sv_from_cstr("  Hello, world!");
            Gup_String_View trimmed = gup_sv_trim_right(sv);

            assert(gup_sv_eq_cstr(trimmed, "  Hello, world!"));
        }

        { // Empty string
            Gup_String_View sv = gup_sv_from_cstr("");
            Gup_String_View trimmed = gup_sv_trim_right(sv);

            assert(gup_sv_eq_cstr(trimmed, ""));
        }

        { // Whitespace string
            Gup_String_View sv = gup_sv_from_cstr("  ");
            Gup_String_View trimmed = gup_sv_trim_right(sv);

            assert(gup_sv_eq_cstr(trimmed, ""));
        }
    }

    { // gup_sv_trim
        {
            Gup_String_View sv = gup_sv_from_cstr("  Hello, world!  ");
            Gup_String_View trimmed = gup_sv_trim(sv);

            assert(gup_sv_eq_cstr(trimmed, "Hello, world!"));
        }

        {
            Gup_String_View sv = gup_sv_from_cstr("  Hello, world!");
            Gup_String_View trimmed = gup_sv_trim(sv);

            assert(gup_sv_eq_cstr(trimmed, "Hello, world!"));
        }

        {
            Gup_String_View sv = gup_sv_from_cstr("Hello, world!  ");
            Gup_String_View trimmed = gup_sv_trim(sv);

            assert(gup_sv_eq_cstr(trimmed, "Hello, world!"));
        }

        {
            Gup_String_View sv = gup_sv_from_cstr("Hello, world!");
            Gup_String_View trimmed = gup_sv_trim(sv);

            assert(gup_sv_eq_cstr(trimmed, "Hello, world!"));
        }

        { // Empty string
            Gup_String_View sv = gup_sv_from_cstr("");
            Gup_String_View trimmed = gup_sv_trim(sv);

            assert(gup_sv_eq_cstr(trimmed, ""));
        }

        { // Whitespace string
            Gup_String_View sv = gup_sv_from_cstr("  ");
            Gup_String_View trimmed = gup_sv_trim(sv);

            assert(gup_sv_eq_cstr(trimmed, ""));
        }
    }

    { // gup_sv_chop_by_delim
        { // Buffer gets the part before the delimiter
            Gup_String_View sv = gup_sv_from_cstr("Hello, world!");
            Gup_String_View buffer = gup_sv_chop_by_delim(&sv, ',');

            assert(gup_sv_eq_cstr(buffer, "Hello"));
            assert(gup_sv_eq_cstr(sv, " world!"));
        }

        { // Buffer gets the entire string if delim is not found
            Gup_String_View sv = gup_sv_from_cstr("Hello, world!");
            Gup_String_View buffer = gup_sv_chop_by_delim(&sv, '?');

            assert(gup_sv_eq_cstr(buffer, "Hello, world!"));
            assert(gup_sv_eq_cstr(sv, ""));
        }
    }

    { // gup_sv_try_chop_by_delim
        { // Buffer gets the part before the delimiter
            bool result;
            Gup_String_View sv = gup_sv_from_cstr("Hello, world!");
            Gup_String_View buffer = gup_sv();

            result = gup_sv_try_chop_by_delim(&sv, ',', &buffer);

            assert(result == true);
            assert(gup_sv_eq_cstr(buffer, "Hello"));
            assert(gup_sv_eq_cstr(sv, " world!"));
        }

        { // Buffer is empty if delim is not found
            bool result;
            Gup_String_View sv = gup_sv_from_cstr("Hello, world!");
            Gup_String_View buffer = gup_sv();
            
            result = gup_sv_try_chop_by_delim(&sv, '?', &buffer);

            assert(result == false);
            assert(gup_sv_is_empty(buffer));
            assert(gup_sv_eq_cstr(sv, "Hello, world!"));
        }
    }
}