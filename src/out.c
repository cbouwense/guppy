void gup_array_bool_remove(GupArrayBool* xs, const bool x, const int max_count_to_remove) {
    bool new_data[xs->count];
    int removed_count = 0;
    int new_data_size = 0;

    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    memcpy(xs->data, new_data, new_data_size);
    xs->count = new_data_size;
}

void gup_array_char_remove(GupArrayChar* xs, const char x, const int max_count_to_remove) {
    char new_data[xs->count];
    int removed_count = 0;
    int new_data_size = 0;

    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    memcpy(xs->data, new_data, new_data_size);
    xs->count = new_data_size;
}

void gup_array_double_remove(GupArrayDouble* xs, const double x, const int max_count_to_remove) {
    double new_data[xs->count];
    int removed_count = 0;
    int new_data_size = 0;

    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    memcpy(xs->data, new_data, new_data_size);
    xs->count = new_data_size;
}

void gup_array_float_remove(GupArrayFloat* xs, const float x, const int max_count_to_remove) {
    float new_data[xs->count];
    int removed_count = 0;
    int new_data_size = 0;

    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    memcpy(xs->data, new_data, new_data_size);
    xs->count = new_data_size;
}

void gup_array_int_remove(GupArrayInt* xs, const int x, const int max_count_to_remove) {
    int new_data[xs->count];
    int removed_count = 0;
    int new_data_size = 0;

    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    memcpy(xs->data, new_data, new_data_size);
    xs->count = new_data_size;
}

void gup_array_long_remove(GupArrayLong* xs, const long x, const int max_count_to_remove) {
    long new_data[xs->count];
    int removed_count = 0;
    int new_data_size = 0;

    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    memcpy(xs->data, new_data, new_data_size);
    xs->count = new_data_size;
}

void gup_array_ptr_remove(GupArrayPtr* xs, const void* x, const int max_count_to_remove) {
    void* new_data[xs->count];
    int removed_count = 0;
    int new_data_size = 0;

    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    memcpy(xs->data, new_data, new_data_size);
    xs->count = new_data_size;
}

void gup_array_short_remove(GupArrayShort* xs, const short x, const int max_count_to_remove) {
    short new_data[xs->count];
    int removed_count = 0;
    int new_data_size = 0;

    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (xs->data[i] != x) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    memcpy(xs->data, new_data, new_data_size);
    xs->count = new_data_size;
}

void gup_array_string_remove(GupArrayString* xs, const GupString x, const int max_count_to_remove) {
    GupString new_data[xs->count];
    int removed_count = 0;
    int new_data_size = 0;

    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (gup_array_char_equals(xs->data[i], x)) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    memcpy(xs->data, new_data, new_data_size);
    xs->count = new_data_size;
}

void gup_array_cstr_remove(GupArrayCstr* xs, const char* x, const int max_count_to_remove) {
    char* new_data[xs->count];
    int removed_count = 0;
    int new_data_size = 0;

    for (int i = 0; i < xs->count && removed_count < count_to_remove; i++) {
        if (gup_cstr_equals(xs->data[i], x)) {
            new_data[new_data_size] = xs->data[i];
            new_data_size++;
        } else {
            removed_count++;
        }
    }

    memcpy(xs->data, new_data, new_data_size);
    xs->count = new_data_size;
}

