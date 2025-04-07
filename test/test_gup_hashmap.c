#include "../src/guppy.h"

void test_gup_hashmap_general(void) {
    GupHashmapInt hashmap = gup_hashmap_int_create(NULL);

    gup_assert(!gup_hashmap_int_get(hashmap, "foo", NULL));
    gup_assert(!gup_hashmap_int_get(hashmap, "bar", NULL));
    gup_assert(gup_hashmap_int_size(hashmap) == 0);

    gup_hashmap_int_set(NULL, &hashmap, "leet", 1337);

    int leet, answer = 0;
    gup_assert(gup_hashmap_int_get(hashmap, "leet", &leet));
    gup_assert(leet == 1337);
    gup_assert(!gup_hashmap_int_get(hashmap, "answer", &answer));
    gup_assert(answer == 0);
    gup_assert(gup_hashmap_int_size(hashmap) == 1);

    gup_hashmap_int_set(NULL, &hashmap, "answer", 42);
    
    gup_assert(gup_hashmap_int_get(hashmap, "leet", &leet));
    gup_assert(leet == 1337);
    gup_assert(gup_hashmap_int_get(hashmap, "answer", &answer));
    gup_assert(answer == 42);
    gup_assert(gup_hashmap_int_size(hashmap) == 2);

    gup_hashmap_int_remove(&hashmap, "leet");
    gup_assert(gup_hashmap_int_size(hashmap) == 1);

    gup_hashmap_int_destroy(hashmap);
}

void test_gup_hashmap_set_multiple_time_rewrites() {
    GupHashmapChar hashmap = gup_hashmap_char_create(NULL);
    char result = 0;

    gup_hashmap_char_set(NULL, &hashmap, "dupe", 'x');
    gup_hashmap_char_set(NULL, &hashmap, "dupe", 'y');
    gup_hashmap_char_set(NULL, &hashmap, "dupe", 'z');
    gup_hashmap_char_get(hashmap, "dupe", &result);

    gup_assert(result == 'z');

    gup_hashmap_char_destroy(hashmap);
}

void test_gup_hashmap(void) {
    test_gup_hashmap_general();
    test_gup_hashmap_set_multiple_time_rewrites();
}
