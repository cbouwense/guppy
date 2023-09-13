clear && printf '\e[3J' # Clear the screen and scrollback buffer
mkdir -p build/
gcc -Wall -Werror --pedantic -o build/guppy_test test/guppy_test.c
build/guppy_test
