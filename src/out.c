bool gup_array_bool_equals(const GupArrayBool* xs, const GupArrayBool* ys) {
    if (xs->count != ys->count) return false;

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

bool gup_array_char_equals(const GupArrayChar* xs, const GupArrayChar* ys) {
    if (xs->count != ys->count) return false;

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

bool gup_array_double_equals(const GupArrayDouble* xs, const GupArrayDouble* ys) {
    if (xs->count != ys->count) return false;

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

bool gup_array_float_equals(const GupArrayFloat* xs, const GupArrayFloat* ys) {
    if (xs->count != ys->count) return false;

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

bool gup_array_int_equals(const GupArrayInt* xs, const GupArrayInt* ys) {
    if (xs->count != ys->count) return false;

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

bool gup_array_long_equals(const GupArrayLong* xs, const GupArrayLong* ys) {
    if (xs->count != ys->count) return false;

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

bool gup_array_ptr_equals(const GupArrayPtr* xs, const GupArrayPtr* ys) {
    if (xs->count != ys->count) return false;

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

bool gup_array_short_equals(const GupArrayShort* xs, const GupArrayShort* ys) {
    if (xs->count != ys->count) return false;

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] != ys->data[i]) return false;
    }

    return true;
}

bool gup_array_string_equals(const GupArrayString* xs, const GupArrayString* ys) {
    if (xs->count != ys->count) return false;

    for (int i = 0; i < xs->count; i++) {
        if (!gup_array_char_equals(xs->data[i], x)) return false;
    }

    return true;
}

bool gup_array_cstr_equals(const GupArrayCstr* xs, const GupArrayCstr* ys) {
    if (xs->count != ys->count) return false;

    for (int i = 0; i < xs->count; i++) {
        if (strcmp(xs->data[i], x) != 0) return false;
    }

    return true;
}

