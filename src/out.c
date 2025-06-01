#define gup_array_bool_print(xs) _gup_array_bool_print(xs, #xs)
void _gup_array_bool_print(const GupArrayBool* xs, const char* xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
       if (xs->data[i])
           printf("true");
       else
           printf("false");
    }
    printf("]\n");
}

#define gup_array_char_print(xs) _gup_array_char_print(xs, #xs)
void _gup_array_char_print(const GupArrayChar* xs, const char* xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
       printf("'%c'", xs->data[i]);

       if (i != xs->count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_double_print(xs) _gup_array_double_print(xs, #xs)
void _gup_array_double_print(const GupArrayDouble* xs, const char* xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
       printf("%f", xs->data[i]);

       if (i != xs->count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_float_print(xs) _gup_array_float_print(xs, #xs)
void _gup_array_float_print(const GupArrayFloat* xs, const char* xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
       printf("%f", xs->data[i]);

       if (i != xs->count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_int_print(xs) _gup_array_int_print(xs, #xs)
void _gup_array_int_print(const GupArrayInt* xs, const char* xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
       printf("%d", xs->data[i]);

       if (i != xs->count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_long_print(xs) _gup_array_long_print(xs, #xs)
void _gup_array_long_print(const GupArrayLong* xs, const char* xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
       printf("%ld", xs->data[i]);

       if (i != xs->count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_ptr_print(xs) _gup_array_ptr_print(xs, #xs)
void _gup_array_ptr_print(const GupArrayPtr* xs, const char* xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
       printf("%p", xs->data[i]);

       if (i != xs->count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_short_print(xs) _gup_array_short_print(xs, #xs)
void _gup_array_short_print(const GupArrayShort* xs, const char* xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
       printf("%f", xs->data[i]);

       if (i != xs->count-1) printf(", ");
    }
    printf("]\n");
}

#define gup_array_string_print(xs) _gup_array_string_print(xs, #xs)
void _gup_array_string_print(const GupArrayString* xs, const char* xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
       printf("  \"");
       for (int j = 0; j < xs->data[i].count; j++) {
           printf("%c", xs->data[i].data[j]);
       }
       printf("\"");
       if (i != xs->count-1) printf(",");
       printf("\n");
    }
    printf("]\n");
}

#define gup_array_cstr_print(xs) _gup_array_cstr_print(xs, #xs)
void _gup_array_cstr_print(const GupArrayCstr* xs, const char* xs_name) {
    printf("%s: [", xs_name);
    for (int i = 0; i < xs->count; i++) {
       printf("\"%s\"", xs->data[i]);

       if (i != xs->count-1) printf(", ");
    }
    printf("]\n");
}

