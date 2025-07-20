// Orders false before true, (e.g. [false, false, true, true])
GupArrayBool* gup_array_bool_to_sorted(GupAllocator* a, const GupArrayBool* xs) {
    if (xs->count <= 1) return gup_array_bool_copy(a, xs);

    GupArrayBool* sorted = gup_array_bool_create(a);

    for (int i = 0; i < xs->count; i++) {
        if (xs->data[i] == false) {
            gup_array_bool_prepend(a, sorted, false);
        } else {
            gup_array_bool_append(a, sorted, true);
        }
    }

    return sorted;
}

GupArrayChar* gup_array_char_to_sorted(GupAllocator* a, const GupArrayChar* xs) {
    if (xs->count <= 1) return gup_array_char_copy(a, xs);

    GupArrayChar* sorted = gup_array_char_create(a);
    GupArrayChar* left   = gup_array_char_create(a);
    GupArrayChar* right  = gup_array_char_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs->count - 1;
    const char pivot = xs->data[pivot_idx];

    for (int i = 0; i < xs->count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

    if (xs->data[i] <= pivot) {
            gup_array_char_append(a, left, xs->data[i]);
        } else {
            gup_array_char_append(a, right, xs->data[i]);
        }
    }

    GupArrayChar* sorted_left  = gup_array_char_to_sorted(a, left);
    GupArrayChar* sorted_right = gup_array_char_to_sorted(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left->count; i++) {
            gup_array_char_append(a, sorted, sorted_left->data[i]);
        }

        gup_array_char_append(a, sorted, pivot);
        
        for (int i = 0; i < sorted_right->count; i++) {
            gup_array_char_append(a, sorted, sorted_right->data[i]);
        }
    }

    return sorted;
}

GupArrayDouble* gup_array_double_to_sorted(GupAllocator* a, const GupArrayDouble* xs) {
    if (xs->count <= 1) return gup_array_double_copy(a, xs);

    GupArrayDouble* sorted = gup_array_double_create(a);
    GupArrayDouble* left   = gup_array_double_create(a);
    GupArrayDouble* right  = gup_array_double_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs->count - 1;
    const double pivot = xs->data[pivot_idx];

    for (int i = 0; i < xs->count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

    if (xs->data[i] <= pivot) {
            gup_array_double_append(a, left, xs->data[i]);
        } else {
            gup_array_double_append(a, right, xs->data[i]);
        }
    }

    GupArrayDouble* sorted_left  = gup_array_double_to_sorted(a, left);
    GupArrayDouble* sorted_right = gup_array_double_to_sorted(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left->count; i++) {
            gup_array_double_append(a, sorted, sorted_left->data[i]);
        }

        gup_array_double_append(a, sorted, pivot);
        
        for (int i = 0; i < sorted_right->count; i++) {
            gup_array_double_append(a, sorted, sorted_right->data[i]);
        }
    }

    return sorted;
}

GupArrayFloat* gup_array_float_to_sorted(GupAllocator* a, const GupArrayFloat* xs) {
    if (xs->count <= 1) return gup_array_float_copy(a, xs);

    GupArrayFloat* sorted = gup_array_float_create(a);
    GupArrayFloat* left   = gup_array_float_create(a);
    GupArrayFloat* right  = gup_array_float_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs->count - 1;
    const float pivot = xs->data[pivot_idx];

    for (int i = 0; i < xs->count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

    if (xs->data[i] <= pivot) {
            gup_array_float_append(a, left, xs->data[i]);
        } else {
            gup_array_float_append(a, right, xs->data[i]);
        }
    }

    GupArrayFloat* sorted_left  = gup_array_float_to_sorted(a, left);
    GupArrayFloat* sorted_right = gup_array_float_to_sorted(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left->count; i++) {
            gup_array_float_append(a, sorted, sorted_left->data[i]);
        }

        gup_array_float_append(a, sorted, pivot);
        
        for (int i = 0; i < sorted_right->count; i++) {
            gup_array_float_append(a, sorted, sorted_right->data[i]);
        }
    }

    return sorted;
}

GupArrayInt* gup_array_int_to_sorted(GupAllocator* a, const GupArrayInt* xs) {
    if (xs->count <= 1) return gup_array_int_copy(a, xs);

    GupArrayInt* sorted = gup_array_int_create(a);
    GupArrayInt* left   = gup_array_int_create(a);
    GupArrayInt* right  = gup_array_int_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs->count - 1;
    const int pivot = xs->data[pivot_idx];

    for (int i = 0; i < xs->count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

    if (xs->data[i] <= pivot) {
            gup_array_int_append(a, left, xs->data[i]);
        } else {
            gup_array_int_append(a, right, xs->data[i]);
        }
    }

    GupArrayInt* sorted_left  = gup_array_int_to_sorted(a, left);
    GupArrayInt* sorted_right = gup_array_int_to_sorted(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left->count; i++) {
            gup_array_int_append(a, sorted, sorted_left->data[i]);
        }

        gup_array_int_append(a, sorted, pivot);
        
        for (int i = 0; i < sorted_right->count; i++) {
            gup_array_int_append(a, sorted, sorted_right->data[i]);
        }
    }

    return sorted;
}

GupArrayLong* gup_array_long_to_sorted(GupAllocator* a, const GupArrayLong* xs) {
    if (xs->count <= 1) return gup_array_long_copy(a, xs);

    GupArrayLong* sorted = gup_array_long_create(a);
    GupArrayLong* left   = gup_array_long_create(a);
    GupArrayLong* right  = gup_array_long_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs->count - 1;
    const long pivot = xs->data[pivot_idx];

    for (int i = 0; i < xs->count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

    if (xs->data[i] <= pivot) {
            gup_array_long_append(a, left, xs->data[i]);
        } else {
            gup_array_long_append(a, right, xs->data[i]);
        }
    }

    GupArrayLong* sorted_left  = gup_array_long_to_sorted(a, left);
    GupArrayLong* sorted_right = gup_array_long_to_sorted(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left->count; i++) {
            gup_array_long_append(a, sorted, sorted_left->data[i]);
        }

        gup_array_long_append(a, sorted, pivot);
        
        for (int i = 0; i < sorted_right->count; i++) {
            gup_array_long_append(a, sorted, sorted_right->data[i]);
        }
    }

    return sorted;
}

GupArrayPtr* gup_array_ptr_to_sorted(GupAllocator* a, const GupArrayPtr* xs) {
    if (xs->count <= 1) return gup_array_ptr_copy(a, xs);

    GupArrayPtr* sorted = gup_array_ptr_create(a);
    GupArrayPtr* left   = gup_array_ptr_create(a);
    GupArrayPtr* right  = gup_array_ptr_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs->count - 1;
    const void* pivot = xs->data[pivot_idx];

    for (int i = 0; i < xs->count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

    if (xs->data[i] <= pivot) {
            gup_array_ptr_append(a, left, xs->data[i]);
        } else {
            gup_array_ptr_append(a, right, xs->data[i]);
        }
    }

    GupArrayPtr* sorted_left  = gup_array_ptr_to_sorted(a, left);
    GupArrayPtr* sorted_right = gup_array_ptr_to_sorted(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left->count; i++) {
            gup_array_ptr_append(a, sorted, sorted_left->data[i]);
        }

        gup_array_ptr_append(a, sorted, pivot);
        
        for (int i = 0; i < sorted_right->count; i++) {
            gup_array_ptr_append(a, sorted, sorted_right->data[i]);
        }
    }

    return sorted;
}

GupArrayShort* gup_array_short_to_sorted(GupAllocator* a, const GupArrayShort* xs) {
    if (xs->count <= 1) return gup_array_short_copy(a, xs);

    GupArrayShort* sorted = gup_array_short_create(a);
    GupArrayShort* left   = gup_array_short_create(a);
    GupArrayShort* right  = gup_array_short_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs->count - 1;
    const short pivot = xs->data[pivot_idx];

    for (int i = 0; i < xs->count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

    if (xs->data[i] <= pivot) {
            gup_array_short_append(a, left, xs->data[i]);
        } else {
            gup_array_short_append(a, right, xs->data[i]);
        }
    }

    GupArrayShort* sorted_left  = gup_array_short_to_sorted(a, left);
    GupArrayShort* sorted_right = gup_array_short_to_sorted(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left->count; i++) {
            gup_array_short_append(a, sorted, sorted_left->data[i]);
        }

        gup_array_short_append(a, sorted, pivot);
        
        for (int i = 0; i < sorted_right->count; i++) {
            gup_array_short_append(a, sorted, sorted_right->data[i]);
        }
    }

    return sorted;
}

GupArrayString* gup_array_string_to_sorted(GupAllocator* a, const GupArrayString* xs) {
    if (xs->count <= 1) return gup_array_string_copy(a, xs);

    GupArrayString* sorted = gup_array_string_create(a);
    GupArrayString* left   = gup_array_string_create(a);
    GupArrayString* right  = gup_array_string_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs->count - 1;
    const GupString pivot = xs->data[pivot_idx];

    for (int i = 0; i < xs->count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

    if (gup_string_compare(a, xs->data[i], pivot) <= 0) {
            gup_array_string_append(a, left, xs->data[i]);
        } else {
            gup_array_string_append(a, right, xs->data[i]);
        }
    }

    GupArrayString* sorted_left  = gup_array_string_to_sorted(a, left);
    GupArrayString* sorted_right = gup_array_string_to_sorted(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left->count; i++) {
            gup_array_string_append(a, sorted, sorted_left->data[i]);
        }

        gup_array_string_append(a, sorted, pivot);
        
        for (int i = 0; i < sorted_right->count; i++) {
            gup_array_string_append(a, sorted, sorted_right->data[i]);
        }
    }

    return sorted;
}

GupArrayCstr* gup_array_cstr_to_sorted(GupAllocator* a, const GupArrayCstr* xs) {
    if (xs->count <= 1) return gup_array_cstr_copy(a, xs);

    GupArrayCstr* sorted = gup_array_cstr_create(a);
    GupArrayCstr* left   = gup_array_cstr_create(a);
    GupArrayCstr* right  = gup_array_cstr_create(a);

    // Choose the last item as the pivot for no particular reason.
    const int pivot_idx = xs->count - 1;
    const char* pivot = xs->data[pivot_idx];

    for (int i = 0; i < xs->count; i++) {
        // Don't include the pivot.
        if (i == pivot_idx) continue;

    if (strcmp(xs->data[i], pivot) <= 0) {
            gup_array_cstr_append(a, left, xs->data[i]);
        } else {
            gup_array_cstr_append(a, right, xs->data[i]);
        }
    }

    GupArrayCstr* sorted_left  = gup_array_cstr_to_sorted(a, left);
    GupArrayCstr* sorted_right = gup_array_cstr_to_sorted(a, right);

    { // Construct the final array from the left, pivot, and right.
        for (int i = 0; i < sorted_left->count; i++) {
            gup_array_cstr_append(a, sorted, sorted_left->data[i]);
        }

        gup_array_cstr_append(a, sorted, pivot);
        
        for (int i = 0; i < sorted_right->count; i++) {
            gup_array_cstr_append(a, sorted, sorted_right->data[i]);
        }
    }

    return sorted;
}

