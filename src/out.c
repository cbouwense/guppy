int gup_array_bool_find_index_of(const GupArrayBool* xs, const bool x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return i;
        }
    }
  
    return -1;
}

int gup_array_char_find_index_of(const GupArrayChar* xs, const char x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return i;
        }
    }
  
    return -1;
}

int gup_array_double_find_index_of(const GupArrayDouble* xs, const double x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return i;
        }
    }
  
    return -1;
}

int gup_array_float_find_index_of(const GupArrayFloat* xs, const float x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return i;
        }
    }
  
    return -1;
}

int gup_array_int_find_index_of(const GupArrayInt* xs, const int x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return i;
        }
    }
  
    return -1;
}

int gup_array_long_find_index_of(const GupArrayLong* xs, const long x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return i;
        }
    }
  
    return -1;
}

int gup_array_ptr_find_index_of(const GupArrayPtr* xs, const void* x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return i;
        }
    }
  
    return -1;
}

int gup_array_short_find_index_of(const GupArrayShort* xs, const short x) {
    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == x) {
            return i;
        }
    }
  
    return -1;
}

int gup_array_string_find_index_of(const GupArrayString* xs, const GupString x) {
    for (int i = 0; i < xs->count; i++) {
        if (gup_array_char_equals(xs->data[i], x)) {
            return i;
        }
    }
  
    return -1;
}

int gup_array_cstr_find_index_of(const GupArrayCstr* xs, const char* x) {
    for (int i = 0; i < xs->count; i++) {
        if (gup_cstr_equals(xs->data[i], x)) {
            return i;
        }
    }
  
    return -1;
}

