bool gup_array_bool_contains(const GupArrayBool* xs, const bool x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_char_contains(const GupArrayChar* xs, const char x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_double_contains(const GupArrayDouble* xs, const double x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_float_contains(const GupArrayFloat* xs, const float x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_int_contains(const GupArrayInt* xs, const int x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_long_contains(const GupArrayLong* xs, const long x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_ptr_contains(const GupArrayPtr* xs, const void* x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_short_contains(const GupArrayShort* xs, const short x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return true;
        }
    }

    return false;
}

bool gup_array_string_contains(const GupArrayString* xs, const GupString x) {
    for (int i = 0; i < xs->count; i++) {
        if (gup_array_char_equals(xs->data[i], x)) {
            return true;
        }
    }

    return false;
}

bool gup_array_cstr_contains(const GupArrayCstr* xs, const char* x) {
    for (int i = 0; i < xs->count; i++) {
        if (strcmp(xs->data[i], x) == 0) {
            return true;
        }
    }

    return false;
}

