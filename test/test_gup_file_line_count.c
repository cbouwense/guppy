#include "../src/guppy.h"

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
