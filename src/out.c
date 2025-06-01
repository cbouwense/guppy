#define gup_array_bool_debug(xs) _gup_array_bool_debug(xs, #xs)
void _gup_array_bool_debug(GupArrayBool* xs, const char* xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d\n", xs->capacity);
    printf("  count: %d\n", xs->count);
    printf("  data: %p\n", (void *)(xs->data));
    printf("}\n");
}

#define gup_array_char_debug(xs) _gup_array_char_debug(xs, #xs)
void _gup_array_char_debug(GupArrayChar* xs, const char* xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d\n", xs->capacity);
    printf("  count: %d\n", xs->count);
    printf("  data: %p\n", (void *)(xs->data));
    printf("}\n");
}

#define gup_array_double_debug(xs) _gup_array_double_debug(xs, #xs)
void _gup_array_double_debug(GupArrayDouble* xs, const char* xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d\n", xs->capacity);
    printf("  count: %d\n", xs->count);
    printf("  data: %p\n", (void *)(xs->data));
    printf("}\n");
}

#define gup_array_float_debug(xs) _gup_array_float_debug(xs, #xs)
void _gup_array_float_debug(GupArrayFloat* xs, const char* xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d\n", xs->capacity);
    printf("  count: %d\n", xs->count);
    printf("  data: %p\n", (void *)(xs->data));
    printf("}\n");
}

#define gup_array_int_debug(xs) _gup_array_int_debug(xs, #xs)
void _gup_array_int_debug(GupArrayInt* xs, const char* xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d\n", xs->capacity);
    printf("  count: %d\n", xs->count);
    printf("  data: %p\n", (void *)(xs->data));
    printf("}\n");
}

#define gup_array_long_debug(xs) _gup_array_long_debug(xs, #xs)
void _gup_array_long_debug(GupArrayLong* xs, const char* xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d\n", xs->capacity);
    printf("  count: %d\n", xs->count);
    printf("  data: %p\n", (void *)(xs->data));
    printf("}\n");
}

#define gup_array_ptr_debug(xs) _gup_array_ptr_debug(xs, #xs)
void _gup_array_ptr_debug(GupArrayPtr* xs, const char* xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d\n", xs->capacity);
    printf("  count: %d\n", xs->count);
    printf("  data: %p\n", (void *)(xs->data));
    printf("}\n");
}

#define gup_array_short_debug(xs) _gup_array_short_debug(xs, #xs)
void _gup_array_short_debug(GupArrayShort* xs, const char* xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d\n", xs->capacity);
    printf("  count: %d\n", xs->count);
    printf("  data: %p\n", (void *)(xs->data));
    printf("}\n");
}

#define gup_array_string_debug(xs) _gup_array_string_debug(xs, #xs)
void _gup_array_string_debug(GupArrayString* xs, const char* xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d\n", xs->capacity);
    printf("  count: %d\n", xs->count);
    printf("  data: %p\n", (void *)(xs->data));
    printf("}\n");
}

#define gup_array_cstr_debug(xs) _gup_array_cstr_debug(xs, #xs)
void _gup_array_cstr_debug(GupArrayCstr* xs, const char* xs_name) {
    printf("%s: {\n", xs_name);
    printf("  capacity: %d\n", xs->capacity);
    printf("  count: %d\n", xs->count);
    printf("  data: %p\n", (void *)(xs->data));
    printf("}\n");
}

