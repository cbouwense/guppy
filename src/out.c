void gup_array_bool_append(GupAllocator* a, GupArrayBool* xs, const bool x) {
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, bool);

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_char_append(GupAllocator* a, GupArrayChar* xs, const char x) {
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, char);

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_double_append(GupAllocator* a, GupArrayDouble* xs, const double x) {
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, double);

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_float_append(GupAllocator* a, GupArrayFloat* xs, const float x) {
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, float);

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_int_append(GupAllocator* a, GupArrayInt* xs, const int x) {
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, int);

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_long_append(GupAllocator* a, GupArrayLong* xs, const long x) {
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, long);

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_ptr_append(GupAllocator* a, GupArrayPtr* xs, const void* x) {
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, void*);

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_short_append(GupAllocator* a, GupArrayShort* xs, const short x) {
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, short);

    xs->data[xs->count] = x;
    xs->count++;
}

/** Appends the struct, does NOT copy. */
void gup_array_string_append(GupAllocator* a, GupArrayString* xs, const GupString x) {
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, GupString);

    xs->data[xs->count] = x;
    xs->count++;
}

void gup_array_cstr_append(GupAllocator* a, GupArrayCstr* xs, const char* x) {
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, char*);

    xs->data[xs->count] = x;
    xs->count++;
}

