#include "../src/guppy.h"

void test_gup_file_line_count(void) {
    int line_count = 0;

    line_count = gup_file_line_count("test/empty.txt");
    assert(line_count == 0);

    line_count = gup_file_line_count("test/one_newline.txt");
    assert(line_count == 2);

    line_count = gup_file_line_count("test/foo.txt");
    assert(line_count == 5);

    line_count = gup_file_line_count("test/stb.txt");
    assert(line_count == 13111);
}
