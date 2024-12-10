#include "../src/guppy.h"

void test_gup_hashmap_general(void) {
    GupHashmapInt hashmap = gup_hashmap_int_create();

    gup_assert(!gup_hashmap_int_get(hashmap, "foo", NULL));
    gup_assert(!gup_hashmap_int_get(hashmap, "bar", NULL));
    gup_assert(gup_hashmap_int_size(hashmap) == 0);

    gup_hashmap_int_set(&hashmap, "leet", 1337);

    int leet, answer = 0;
    gup_assert(gup_hashmap_int_get(hashmap, "leet", &leet));
    gup_assert(leet == 1337);
    gup_assert(!gup_hashmap_int_get(hashmap, "answer", &answer));
    gup_assert(answer == 0);
    gup_assert(gup_hashmap_int_size(hashmap) == 1);

    gup_hashmap_int_set(&hashmap, "answer", 42);
    
    gup_assert(gup_hashmap_int_get(hashmap, "leet", &leet));
    gup_assert(leet == 1337);
    gup_assert(gup_hashmap_int_get(hashmap, "answer", &answer));
    gup_assert(answer == 42);
    gup_assert(gup_hashmap_int_size(hashmap) == 2);

    gup_hashmap_int_destroy(hashmap);
}

void test_gup_hashmap(void) {
    test_gup_hashmap_general();
}
