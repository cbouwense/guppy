test_guppy: test/%.c
	clang -g -Wall -Wextra --pedantic -fsanitize=address -o test_guppy test/%.c

run: test_guppy
	./test_guppy