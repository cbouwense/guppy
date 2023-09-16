mkdir -p build/
gcc -Wall -Werror --pedantic -g -o build/test_guppy test/test_guppy.c
gdb build/test_guppy
