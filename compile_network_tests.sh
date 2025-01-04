mkdir -p build/
clang -g -Wall -Wextra --pedantic -fsanitize=address,undefined -o build/test_gupnet test/test_gup_networking.c
