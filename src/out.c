void gup_array_bool_prepend(GupAllocator* a, GupArrayBool* xs, bool x){
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, bool);

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_char_prepend(GupAllocator* a, GupArrayChar* xs, char x){
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, char);

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_double_prepend(GupAllocator* a, GupArrayDouble* xs, double x){
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, double);

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_float_prepend(GupAllocator* a, GupArrayFloat* xs, float x){
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, float);

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_int_prepend(GupAllocator* a, GupArrayInt* xs, int x){
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, int);

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_long_prepend(GupAllocator* a, GupArrayLong* xs, long x){
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, long);

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_ptr_prepend(GupAllocator* a, GupArrayPtr* xs, void* x){
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, void*);

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_short_prepend(GupAllocator* a, GupArrayShort* xs, short x){
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, short);

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_string_prepend(GupAllocator* a, GupArrayString* xs, GupString x){
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, GupString);

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

void gup_array_cstr_prepend(GupAllocator* a, GupArrayCstr* xs, char* x){
    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, char*);

    for (int i = xs->count; i > 0; i--) {
        xs->data[i] = xs->data[i-1];
    }
    xs->data[0] = x;
    xs->count++;
}

