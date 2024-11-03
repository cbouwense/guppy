#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *foo = malloc(1);
    foo[0] = '\0';
    if (strcmp(foo, "foo") == 0) {
        printf("they are the same\n");
    } else {
        printf("they are different\n");
    }

    return 0;
}