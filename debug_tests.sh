mkdir -p build/
gcc -Wall -Werror --pedantic -g -o build/guppy_test test/guppy_test.c
gdb build/guppy_test
