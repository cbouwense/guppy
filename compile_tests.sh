mkdir -p build/
clang-19 -g -Wall -Wextra -Werror --pedantic -ferror-limit=0 -fsanitize=address,undefined -o build/test_guppy test/test_guppy.c -lm
