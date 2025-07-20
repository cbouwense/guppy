GupArrayBool* gup_array_bool_create_from_array(GupAllocator* a, const bool xs[], const int xs_count) {
    const int capacity       = xs_count > GUP_ARRAY_DEFAULT_CAPACITY ? xs_count : GUP_ARRAY_DEFAULT_CAPACITY;
    const int bytes_to_alloc = capacity * sizeof(bool);
    const int bytes_to_copy  = xs_count * sizeof(bool);

    GupArrayBool* new;
    new = gup_alloc(a, sizeof(*new) + sizeof(bool) * bytes_to_alloc);
    gup_assert(new != NULL);

    new->capacity = capacity;
    new->count    = xs_count;
    memcpy(new->data, xs, bytes_to_copy);

    return new;
}

GupArrayChar* gup_array_char_create_from_array(GupAllocator* a, const char xs[], const int xs_count) {
    const int capacity       = xs_count > GUP_ARRAY_DEFAULT_CAPACITY ? xs_count : GUP_ARRAY_DEFAULT_CAPACITY;
    const int bytes_to_alloc = capacity * sizeof(char);
    const int bytes_to_copy  = xs_count * sizeof(char);

    GupArrayChar* new;
    new = gup_alloc(a, sizeof(*new) + sizeof(char) * bytes_to_alloc);
    gup_assert(new != NULL);

    new->capacity = capacity;
    new->count    = xs_count;
    memcpy(new->data, xs, bytes_to_copy);

    return new;
}

GupArrayDouble* gup_array_double_create_from_array(GupAllocator* a, const double xs[], const int xs_count) {
    const int capacity       = xs_count > GUP_ARRAY_DEFAULT_CAPACITY ? xs_count : GUP_ARRAY_DEFAULT_CAPACITY;
    const int bytes_to_alloc = capacity * sizeof(double);
    const int bytes_to_copy  = xs_count * sizeof(double);

    GupArrayDouble* new;
    new = gup_alloc(a, sizeof(*new) + sizeof(double) * bytes_to_alloc);
    gup_assert(new != NULL);

    new->capacity = capacity;
    new->count    = xs_count;
    memcpy(new->data, xs, bytes_to_copy);

    return new;
}

GupArrayFloat* gup_array_float_create_from_array(GupAllocator* a, const float xs[], const int xs_count) {
    const int capacity       = xs_count > GUP_ARRAY_DEFAULT_CAPACITY ? xs_count : GUP_ARRAY_DEFAULT_CAPACITY;
    const int bytes_to_alloc = capacity * sizeof(float);
    const int bytes_to_copy  = xs_count * sizeof(float);

    GupArrayFloat* new;
    new = gup_alloc(a, sizeof(*new) + sizeof(float) * bytes_to_alloc);
    gup_assert(new != NULL);

    new->capacity = capacity;
    new->count    = xs_count;
    memcpy(new->data, xs, bytes_to_copy);

    return new;
}

GupArrayInt* gup_array_int_create_from_array(GupAllocator* a, const int xs[], const int xs_count) {
    const int capacity       = xs_count > GUP_ARRAY_DEFAULT_CAPACITY ? xs_count : GUP_ARRAY_DEFAULT_CAPACITY;
    const int bytes_to_alloc = capacity * sizeof(int);
    const int bytes_to_copy  = xs_count * sizeof(int);

    GupArrayInt* new;
    new = gup_alloc(a, sizeof(*new) + sizeof(int) * bytes_to_alloc);
    gup_assert(new != NULL);

    new->capacity = capacity;
    new->count    = xs_count;
    memcpy(new->data, xs, bytes_to_copy);

    return new;
}

GupArrayLong* gup_array_long_create_from_array(GupAllocator* a, const long xs[], const int xs_count) {
    const int capacity       = xs_count > GUP_ARRAY_DEFAULT_CAPACITY ? xs_count : GUP_ARRAY_DEFAULT_CAPACITY;
    const int bytes_to_alloc = capacity * sizeof(long);
    const int bytes_to_copy  = xs_count * sizeof(long);

    GupArrayLong* new;
    new = gup_alloc(a, sizeof(*new) + sizeof(long) * bytes_to_alloc);
    gup_assert(new != NULL);

    new->capacity = capacity;
    new->count    = xs_count;
    memcpy(new->data, xs, bytes_to_copy);

    return new;
}

GupArrayPtr* gup_array_ptr_create_from_array(GupAllocator* a, const void* xs[], const int xs_count) {
    const int capacity       = xs_count > GUP_ARRAY_DEFAULT_CAPACITY ? xs_count : GUP_ARRAY_DEFAULT_CAPACITY;
    const int bytes_to_alloc = capacity * sizeof(void*);
    const int bytes_to_copy  = xs_count * sizeof(void*);

    GupArrayPtr* new;
    new = gup_alloc(a, sizeof(*new) + sizeof(void*) * bytes_to_alloc);
    gup_assert(new != NULL);

    new->capacity = capacity;
    new->count    = xs_count;
    memcpy(new->data, xs, bytes_to_copy);

    return new;
}

GupArrayShort* gup_array_short_create_from_array(GupAllocator* a, const short xs[], const int xs_count) {
    const int capacity       = xs_count > GUP_ARRAY_DEFAULT_CAPACITY ? xs_count : GUP_ARRAY_DEFAULT_CAPACITY;
    const int bytes_to_alloc = capacity * sizeof(short);
    const int bytes_to_copy  = xs_count * sizeof(short);

    GupArrayShort* new;
    new = gup_alloc(a, sizeof(*new) + sizeof(short) * bytes_to_alloc);
    gup_assert(new != NULL);

    new->capacity = capacity;
    new->count    = xs_count;
    memcpy(new->data, xs, bytes_to_copy);

    return new;
}

GupArrayString* gup_array_string_create_from_array(GupAllocator* a, const GupString* xs[], const int xs_count) {
    const int capacity       = xs_count > GUP_ARRAY_DEFAULT_CAPACITY ? xs_count : GUP_ARRAY_DEFAULT_CAPACITY;
    const int bytes_to_alloc = capacity * sizeof(GupString*);
    const int bytes_to_copy  = xs_count * sizeof(GupString*);

    GupArrayString* new;
    new = gup_alloc(a, sizeof(*new) + sizeof(GupString*) * bytes_to_alloc);
    gup_assert(new != NULL);

    new->capacity = capacity;
    new->count    = xs_count;
    memcpy(new->data, xs, bytes_to_copy);

    return new;
}

GupArrayCstr* gup_array_cstr_create_from_array(GupAllocator* a, const char* xs[], const int xs_count) {
    const int capacity       = xs_count > GUP_ARRAY_DEFAULT_CAPACITY ? xs_count : GUP_ARRAY_DEFAULT_CAPACITY;
    const int bytes_to_alloc = capacity * sizeof(char*);
    const int bytes_to_copy  = xs_count * sizeof(char*);

    GupArrayCstr* new;
    new = gup_alloc(a, sizeof(*new) + sizeof(char*) * bytes_to_alloc);
    gup_assert(new != NULL);

    new->capacity = capacity;
    new->count    = xs_count;
    memcpy(new->data, xs, bytes_to_copy);

    return new;
}

