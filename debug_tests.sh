mkdir -p build/
clang -Wall -Wextra --pedantic -g -o build/test_guppy test/test_guppy.c
gdb -q build/test_guppy
