#include "../src/guppy.h"

void test_gup_allocator_bucket_create(void) {
    GupAllocatorBucket a = gup_allocator_bucket_create();

    gup_assert(a.data->capacity == 256);
    gup_assert(a.data->count == 0);
    gup_assert(a.data->data != NULL);

    gup_allocator_bucket_destroy(&a);
}

// The real test here is that AddressSanitzer doesn't say there's a leak
// when this is run.
void test_gup_allocator_bucket_can_allocate_stuff_and_not_need_to_free_it(void) {
    GupAllocatorBucket a = gup_allocator_bucket_create();

    char* foo = gup_allocator_bucket_alloc(&a, strlen("foo") + 1);
    char* bar = gup_allocator_bucket_alloc(&a, strlen("bar") + 1);
    char* foobar = gup_allocator_bucket_alloc(&a, strlen("foo") + strlen("bar") + 1);
    
    strcpy(foo, "foo");
    strcpy(bar, "bar");
    strcpy(foobar, foo);
    strcat(foobar, bar);
    
    // Make sure that room was actually allocated properly for these.
    gup_assert(strcmp(foo, "foo") == 0);
    gup_assert(strcmp(bar, "bar") == 0);
    gup_assert(strcmp(foobar, "foobar") == 0);

    gup_allocator_bucket_destroy(&a);
}

// The real test here is that AddressSanitzer doesn't say there's a leak
// when this is run.
void test_gup_allocator_bucket_can_be_freed_and_not_leak_memory(void) {
    GupAllocatorBucket a = gup_allocator_bucket_create();

    const int count = 42;
    int** lots_of_ints = gup_allocator_bucket_alloc(&a, sizeof(int *) * count);
    for (int i = 0; i < count; i++) {
        lots_of_ints[i] = gup_allocator_bucket_alloc(&a, sizeof(int));
        *lots_of_ints[i] = i;
    }

    // This is the test.
    gup_allocator_bucket_clear(&a); 

    // This is manual cleanup.
    free(a.data->data);
    free(a.data);
    free(a.bytes->data);
    free(a.bytes);
}

void test_gup_allocator_bucket_can_allocate_a_bunch_of_strings(void) {
    GupAllocatorBucket a = gup_allocator_bucket_create();

    GupString str = gup_string((GupAllocator*)&a, "foo");
    gup_string_append((GupAllocator*)&a, &str, 'b');
    gup_string_append((GupAllocator*)&a, &str, 'a');
    gup_string_append((GupAllocator*)&a, &str, 'r');

    gup_allocator_bucket_destroy(&a);
}

// The file stuff was like spewing leaks so I put this test here
void test_gup_allocator_bucket_with_file_stuff(void) {
    GupAllocatorBucket a = gup_allocator_bucket_create();

    GupArrayString tokens;
    const char* key = "foo";
    GupArrayString file_lines = gup_file_read_lines(&(a.head), "./src/settings.txt");

    for (int i = 0; i < file_lines.count; i++) {
        GupString line = file_lines.data[i];
        tokens = gup_string_split(&(a.head), line, '=');

        // If we have two tokens, we define that as a key-value pair.
        if (tokens.count == 2) {
            GupString line_key = tokens.data[0];
            GupString line_value = tokens.data[1];

            if (gup_string_equals_cstr(line_key, key)) {
                gup_string_copy(&(a.head), line_value);
            }
        }
    }
    
    gup_allocator_bucket_destroy(&a);
}

void test_gup_allocator_bucket(void) {
    test_gup_allocator_bucket_create();
    test_gup_allocator_bucket_can_allocate_stuff_and_not_need_to_free_it();
    test_gup_allocator_bucket_can_be_freed_and_not_leak_memory();
    test_gup_allocator_bucket_can_allocate_a_bunch_of_strings();
    test_gup_allocator_bucket_with_file_stuff();
}
