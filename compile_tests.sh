mkdir -p build/
clang -g -Wall -Wextra --pedantic -fsanitize=address,undefined -o build/test_guppy test/test_guppy.c -lm
