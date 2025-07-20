const kinds = [
    ['Bool', 'bool', 'bool'],
    ['Char', 'char', 'char'],
    ['Double', 'double', 'double'],
    ['Float', 'float', 'float'],
    ['Int', 'int', 'int'],
    ['Long', 'long', 'long'],
    ['Ptr', 'ptr', 'void*'],
    ['Short', 'short', 'short'],
    ['String', 'string', 'GupString'],
    ['Cstr', 'cstr', 'char*'],
];

function main() {
    for (const kind of kinds) {
        // console.log(gen_gup_array_function_defs(...kind));
        // console.log(gen_gup_array_create(...kind));
        // console.log(gen_gup_array_destroy(...kind));
        // console.log(gen_gup_array_create_from_array(...kind));
        // console.log(gen_gup_array_copy(...kind));
        // console.log(gen_gup_array_contains(...kind));
        // console.log(gen_gup_array_equals(...kind));
        // console.log(gen_gup_array_print(...kind));
        // console.log(gen_gup_array_debug(...kind));
        // console.log(gen_gup_array_append(...kind));
        // console.log(gen_gup_array_prepend(...kind));
        // console.log(gen_gup_array_find_index_of(...kind));
        // console.log(gen_gup_array_remove(...kind));
        // console.log(gen_gup_array_remove_all(...kind));
        // console.log(gen_gup_array_remove_at_index_preserve_order(...kind));
        // console.log(gen_gup_array_remove_at_index_no_preserve_order(...kind));
        console.log(gen_gup_array_to_sorted(...kind));
    }
}

const gen_gup_array_function_defs = (up, low, t) => {
    let template = ``;

    template += `GupArray${up}*\tgup_array_${low}_create(GupAllocator* a);\n`
    
    if (up === 'String') {
      template += `GupArrayString*\tgup_array_string_create_from_array(GupAllocator* a, const GupString* xs[], const int xs_count);\n` 
      template += `GupArrayString* gup_array_string_create_from_cstrs(GupAllocator* a, const char** cstrs, const int cstrs_count);\n`
    } else {
      template += `GupArray${up}*\tgup_array_${low}_create_from_array(GupAllocator* a, const ${t} xs[], const int xs_count);\n`
    }

    if (up === 'Char') template += `GupArrayChar*\tgup_array_char_create_from_cstr(GupAllocator* a, char xs[]);\n`
    
    template += `GupArray${up}*\tgup_array_${low}_copy(GupAllocator* a, const GupArray${up}* xs);\n`
    
    if (up === 'String') template += `bool          \tgup_array_${low}_contains(const GupArray${up}* xs, const ${t}* x);\n`
    else                 template += `bool          \tgup_array_${low}_contains(const GupArray${up}* xs, const ${t} x);\n`
    
    template += `void          \tgup_array_${low}_destroy(GupArray${up}* xs);\n`
    template += `bool          \tgup_array_${low}_equals(const GupArray${up}* xs, const GupArray${up}* ys);\n`
    
    if (up === 'Char') template += `bool         \tgup_array_char_equals_cstr(const GupArrayChar* xs, const char* cstr);\n`
    
    template += `void          \tgup_array_${low}_print(const GupArray${up}* xs);\n`
    
    if (up === 'String') {
      template += `void          \tgup_array_${low}_append(GupAllocator* a, GupArray${up}* xs, ${t}* x);\n`
    } else if (up === 'Ptr' || up === 'Cstr') {
      template += `void          \tgup_array_${low}_append(GupAllocator* a, GupArray${up}* xs, ${t} x);\n`
    } else {
      template += `void          \tgup_array_${low}_append(GupAllocator* a, GupArray${up}* xs, const ${t} x);\n`
    }

    if (up === 'String') template += `void          \tgup_array_string_append_cstr(GupAllocator* a, GupArrayString* xs, const char cstr[]);\n`
    
    if (up === 'Ptr' || up === 'String' || up === 'Cstr') {
      template += `void          \tgup_array_${low}_prepend(GupAllocator* a, GupArray${up}* xs, ${t} x);\n`
    } else {
      template += `void          \tgup_array_${low}_prepend(GupAllocator* a, GupArray${up}* xs, const ${t} x);\n`
    }
    
    template += `int           \tgup_array_${low}_find_index_of(const GupArray${up}* xs, const ${t} x);\n`
    template += `void          \tgup_array_${low}_remove(GupArray${up}* xs, const ${t} x, const int count_to_remove);\n`
    template += `void          \tgup_array_${low}_remove_all(GupArray${up}* xs, const ${t} x);\n`
    template += `void          \tgup_array_${low}_remove_at_index_preserve_order(GupArray${up}* xs, const int index);\n`
    template += `void          \tgup_array_${low}_remove_at_index_no_preserve_order(GupArray${up}* xs, const int index);\n`
    template += `GupArray${up}*\tgup_array_${low}_to_sorted(GupAllocator* a, const GupArray${up}* xs);\n`
    
    if (up === 'Char')   template += `char*        \tgup_array_char_to_cstr(GupAllocator* a, const GupArrayChar* chars);\n`
    if (up === 'String') template += `char**       \tgup_array_string_to_cstrs(GupAllocator* a, const GupArrayString* strs);\n`

    return template;
}

const gen_gup_array_create = (up, low, t) =>
`GupArray${up}* gup_array_${low}_create(GupAllocator* a) {
    GupArray${up} *xs;

    xs = gup_alloc(a, sizeof(*xs) + sizeof(${t}) * GUP_ARRAY_DEFAULT_CAPACITY);
    xs->capacity = GUP_ARRAY_DEFAULT_CAPACITY;
    xs->count = 0; 

    return xs;
}
`;

const gen_gup_array_create_from_array = (up, low, t) => {
  let template = ``;

  if (up === 'String') template += `GupArray${up}* gup_array_${low}_create_from_array(GupAllocator* a, const ${t}* xs[], const int xs_count) {\n`;
  else                 template += `GupArray${up}* gup_array_${low}_create_from_array(GupAllocator* a, const ${t} xs[], const int xs_count) {\n`;

  template += `    const int capacity       = xs_count > GUP_ARRAY_DEFAULT_CAPACITY ? xs_count : GUP_ARRAY_DEFAULT_CAPACITY;\n`;
  
  if (up === 'String') {
    template += `    const int bytes_to_alloc = capacity * sizeof(${t}*);\n`;
  } else {
    template += `    const int bytes_to_alloc = capacity * sizeof(${t});\n`;
    if (up !== ('Cstr')) template += `    const int bytes_to_copy  = xs_count * sizeof(${t});\n`;
  }
  
  template += `\n`;
  template += `    GupArray${up}* new;\n`;

  if (up === 'String') template += `    new = gup_alloc(a, sizeof(*new) + sizeof(${t}*) * bytes_to_alloc);\n`;
  else                 template += `    new = gup_alloc(a, sizeof(*new) + sizeof(${t}) * bytes_to_alloc);\n`;

  template += `    gup_assert(new != NULL);\n`;
  template += `\n`;
  template += `    new->capacity = capacity;\n`;
  template += `    new->count    = xs_count;\n`;

  if (up === 'String') {
    template += `\n`;
    template += `    for (int i = 0; i < xs->count; i++) {\n`;
    template += `        new->data[i] = gup_array_char_copy(a, xs[i]);\n`;
    template += `    }\n`;
  } else if (up === 'Cstr') {
    template += `\n`;
    template += `    for (int i = 0; i < xs->count; i++) {\n`;
    template += `        new->data[i] = gup_alloc(a, gup_cstr_length_including_null(xs[i]));\n`
    template += `        gup_cstr_copy(new->data[i], xs[i]);\n`;
    template += `    }\n`;
  } else {
    template += `    memcpy(new->data, xs, bytes_to_copy);\n`;
  }
  
  template += `\n`;
  template += `    return new;\n`;
  template += `}\n`;
 
  return template;
}

const gen_gup_array_copy = (up, low, t) => {
    let template = ``;

    template += `GupArray${up}* gup_array_${low}_copy(GupAllocator* a, const GupArray${up}* xs) {\n`;
    template += `    GupArray${up}* new = gup_alloc(a, sizeof(GupArray${up}) + sizeof(${t}) * xs->capacity);\n`;
    template += `    gup_assert(new != NULL);\n`;
    template += `\n`;
    template += `    new->capacity = xs->capacity;\n`;
    template += `    new->count    = xs->count;\n`;
    if (up === 'String') {
        template += `\n`;
        template += `    for (int i = 0; i < xs->count; i++) {\n`;
        template += `        new->data[i] = gup_array_char_copy(a, xs->data[i]);\n`;
        template += `    }\n`;
    } else if (up === 'Cstr') {
        template += `\n`;
        template += `    for (int i = 0; i < xs->count; i++) {\n`;
        template += `        new->data[i] = gup_alloc(a, gup_cstr_length_including_null(xs->data[i]));\n`
        template += `        gup_cstr_copy(new->data[i], xs->data[i]);\n`;
        template += `    }\n`;
    } else {
        template += `    memcpy(new->data, xs->data, xs->count * sizeof(${t}));\n`;
    }
    template += `\n`;
    template += `    return new;\n`;
    template += `}\n`;

    return template;
};

const gen_gup_array_destroy = (up, low, t) =>
`void gup_array_${low}_destroy(GupArray${up}* xs) {
    free(xs);
}
`;

const gen_gup_array_contains = (up, low, t) => {
    let template = ``;

    if (up === 'String') template += `bool gup_array_${low}_contains(const GupArray${up}* xs, const ${t}* x) {\n`;
    else                 template += `bool gup_array_${low}_contains(const GupArray${up}* xs, const ${t} x) {\n`;
    
    template += `    for (int i = 0; i < xs->count; i++) {\n`;
    
    if (up === 'String')    template += `        if (gup_array_char_equals(xs->data[i], x)) {\n`
    else if (up === 'Cstr') template += `        if (strcmp(xs->data[i], x) == 0) {\n`
    else                    template += `        if (xs->data[i] == x) {\n`;
    
    template += `            return true;\n`;
    template += `        }\n`;
    template += `    }\n`;
    template += `\n`;
    template += `    return false;\n`;
    template += `}\n`;

    return template;
}

const gen_gup_array_equals = (up, low, t) => {
    let template = ``;

    template += `bool gup_array_${low}_equals(const GupArray${up}* xs, const GupArray${up}* ys) {\n`;
    template += `    if (xs->count != ys->count) return false;\n`;
    template += `\n`;
    template += `    for (int i = 0; i < xs->count; i++) {\n`;

    if      (up === 'String') template += `        if (!gup_array_char_equals(xs->data[i], ys->data[i])) return false;\n`
    else if (up === 'Cstr')   template += `        if (strcmp(xs->data[i], ys->data[i]) != 0) return false;\n`
    else                      template += `        if (xs->data[i] != ys->data[i]) return false;\n`;

    template += `    }\n`;
    template += `\n`;
    template += `    return true;\n`;
    template += `}\n`;

    return template;
}

const gen_gup_array_print = (up, low, t) => {
    let template = ``;

    template += `#define gup_array_${low}_print(xs) _gup_array_${low}_print(xs, #xs)\n`;
    template += `void _gup_array_${low}_print(const GupArray${up}* xs, const char* xs_name) {\n`;
    template += `    printf("%s: [", xs_name);\n`;
    template += `    for (int i = 0; i < xs->count; i++) {\n`;
    if (up === 'Bool') {
        template += `       if (xs->data[i])\n`;
        template += `           printf("true");\n`;
        template += `       else\n`;
        template += `           printf("false");\n`;
    }
    else if (up === 'Char') {
        template += `       printf("'%c'", xs->data[i]);\n`;
        template += `\n`;
        template += `       if (i != xs->count-1) printf(", ");\n`;
    }
    else if (up === 'Double' || up === 'Float') {
        template += `       printf("%f", xs->data[i]);\n`;
        template += `\n`;
        template += `       if (i != xs->count-1) printf(", ");\n`;
    }
    else if (up === 'Int') {
        template += `       printf("%d", xs->data[i]);\n`;
        template += `\n`;
        template += `       if (i != xs->count-1) printf(", ");\n`;
    }
    else if (up === 'Long') {
        template += `       printf("%ld", xs->data[i]);\n`;
        template += `\n`;
        template += `       if (i != xs->count-1) printf(", ");\n`;
    }
    else if (up === 'Ptr') {
        template += `       printf("%p", xs->data[i]);\n`;
        template += `\n`;
        template += `       if (i != xs->count-1) printf(", ");\n`;
    }
    else if (up === 'Short') {
      template += `       printf("%hd", xs->data[i]);\n`;
      template += `\n`;
      template += `       if (i != xs->count-1) printf(", ");\n`;
    }
    else if (up === 'String') {
        template += `       printf("  \\"");\n`;
        template += `       for (int j = 0; j < xs->data[i]->count; j++) {\n`;
        template += `           printf("%c", xs->data[i]->data[j]);\n`;
        template += `       }\n`;
        template += `       printf("\\"");\n`;
        template += `       if (i != xs->count-1) printf(",");\n`;
        template += `       printf("\\n");\n`;
    }
    else if (up === 'Cstr') {
        template += `       printf("\\"%s\\"", xs->data[i]);\n`;
        template += `\n`;
        template += `       if (i != xs->count-1) printf(", ");\n`;
    }
    template += `    }\n`;
    template += `    printf("]\\n");\n`;
    template += `}\n`;

    return template;
}

const gen_gup_array_debug = (up, low, t) =>
`#define gup_array_${low}_debug(xs) _gup_array_${low}_debug(xs, #xs)
void _gup_array_${low}_debug(GupArray${up}* xs, const char* xs_name) {
    printf("%s: {\\n", xs_name);
    printf("  capacity: %d\\n", xs->capacity);
    printf("  count: %d\\n", xs->count);
    printf("  data: %p\\n", (void *)(xs->data));
    printf("}\\n");
}
`;

const gen_gup_array_append = (up, low, t) => {
    let template = ``;

    if (up === 'String') template += `/** Appends the struct, does NOT copy. */\n`;

    // Can't make the thing to append const unfortunately for these.
    if (up === 'String') {
      template += `void gup_array_${low}_append(GupAllocator* a, GupArray${up}* xs, ${t}* x) {\n`;
    } else if (up === 'Ptr' || up === 'Cstr') {
      template += `void gup_array_${low}_append(GupAllocator* a, GupArray${up}* xs, ${t} x) {\n`;
    } else {
      template += `void gup_array_${low}_append(GupAllocator* a, GupArray${up}* xs, const ${t} x) {\n`;
    }
    
    template += `    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, ${t});\n`;
    template += `\n`;
    template += `    xs->data[xs->count] = x;\n`;
    template += `    xs->count++;\n`;
    template += `}\n`;

    return template;
};

const gen_gup_array_prepend = (up, low, t) => {
    let template = ``;

    // Can't make the thing to append const unfortunately for these.
    if (up === 'Ptr' || up === 'String' || up === 'Cstr') {
      template += `void gup_array_${low}_prepend(GupAllocator* a, GupArray${up}* xs, ${t} x) {\n`;
    } else {
      template += `void gup_array_${low}_prepend(GupAllocator* a, GupArray${up}* xs, const ${t} x) {\n`;
    }
    
    template += `    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, ${t});\n`;
    template += `\n`;
    template += `    for (int i = xs->count; i > 0; i--) {\n`;
    template += `        xs->data[i] = xs->data[i-1];\n`;
    template += `    }\n`;
    template += `    xs->data[0] = x;\n`;
    template += `    xs->count++;\n`;
    template += `}\n`;

    return template;
}

const gen_gup_array_find_index_of = (up, low, t) => {
    let template = ``;

    template += `int gup_array_${low}_find_index_of(const GupArray${up}* xs, const ${t} x) {\n`;
    template += `    for (int i = 0; i < xs->count; i++) {\n`;
    if      (up === 'String') template += `        if (gup_array_char_equals(xs->data[i], x)) {\n`;
    else if (up === 'Cstr')   template += `        if (gup_cstr_equals(xs->data[i], x)) {\n`;
    else                      template += `        if (xs->data[i] == x) {\n`;
    template += `            return i;\n`;
    template += `        }\n`;
    template += `    }\n`;
    template += `  \n`;
    template += `    return -1;\n`;
    template += `}\n`;

    return template;
}

const gen_gup_array_remove = (up, low, t) => {
    let template = ``;

    template += `void gup_array_${low}_remove(GupArray${up}* xs, const ${t} x, const int max_count_to_remove) {\n`;
    template += `    ${t} new_data[xs->count];\n`;
    template += `    int removed_count = 0;\n`;
    template += ``;
    template += `    int new_data_size = 0;\n`;
    template += `\n`;
    template += `    for (int i = 0; i < xs->count && removed_count < max_count_to_remove; i++) {\n`;

    if      (up === 'String') template += `        if (gup_array_char_equals(xs->data[i], x)) {\n`;
    else if (up === 'Cstr')   template += `        if (gup_cstr_equals(xs->data[i], x)) {\n`;
    else                      template += `        if (xs->data[i] != x) {\n`;

    template += `            new_data[new_data_size] = xs->data[i];\n`;
    template += `            new_data_size++;\n`;
    template += `        } else {\n`;
    template += `            removed_count++;\n`;
    template += `        }\n`;
    template += `    }\n`;
    template += `\n`;
    template += `    memcpy(xs->data, new_data, new_data_size);\n`;
    template += `    xs->count = new_data_size;\n`;
    template += `}\n`;

    return template;
}

const gen_gup_array_remove_all = (up, low, t) => {
    let template = ``;

    template += `void gup_array_${low}_remove_all(GupArray${up}* xs, const ${t} x) {\n`;
    template += `    ${t} new_data[xs->count];\n`;
    template += `\n`;
    template += `    int new_data_size = 0;\n`;
    template += `    for (int i = 0; i < xs->count; i++) {\n`;

    if      (up === 'String') template += `        if (!gup_array_char_equals(xs->data[i], x)) {\n`;
    else if (up === 'Cstr')   template += `        if (strcmp(xs->data[i], x) != 0) {\n`;
    else                      template += `        if (xs->data[i] != x) {\n`;

    if (up === 'String') template += `            new_data[new_data_size] = *xs->data[i];\n`;
    else                 template += `            new_data[new_data_size] = xs->data[i];\n`;

    template += `            new_data_size++;\n`;
    template += `        }\n`;

    if (up === 'String') template += `        gup_array_char_destroy(xs->data[i]);\n`;

    template += `    }\n`;
    template += `\n`;
    template += `    xs->count = new_data_size;\n`;
    template += `    memcpy(xs->data, new_data, new_data_size * sizeof(bool));\n`;
    template += `}\n`;

    return template;
}

const gen_gup_array_remove_at_index_preserve_order = (up, low, t) =>
`void gup_array_${low}_remove_at_index_preserve_order(GupArray${up}* xs, const int index) {
    for (int i = index; i < xs->count-1; i++) {
        xs->data[i] = xs->data[i+1];
    }
    xs->count--;
}
`;

const gen_gup_array_remove_at_index_no_preserve_order = (up, low, t) =>
`void gup_array_${low}_remove_at_index_no_preserve_order(GupArray${up}* xs, const int index) {
    _gup_array_populated_sanity_check(xs);
    gup_assert_verbose(0 <= index && index < xs->count, "You're trying to remove an index from an array that is out of bounds.");

    // Copy the last element into the element to remove
    // (xs: [1, 2, 3, 4, 5], index: 1) -> xs: [1, 5, 3, 4, 5]
    xs->data[index] = xs->data[xs->count-1];

    // Remove the last element by decrementing the count
    // xs: [1, 5, 3, 4, 5] -> xs: [1, 5, 3, 4]
    xs->count--;
}
`;

const gen_gup_array_to_sorted = (up, low, t) => {
    let template = ``;

    if (up === 'Bool') template += `// Orders false before true, (e.g. [false, false, true, true])\n`;

    template += `GupArray${up}* gup_array_${low}_to_sorted(GupAllocator* a, const GupArray${up}* xs) {\n`;
    template += `    if (xs->count <= 1) return gup_array_${low}_copy(a, xs);\n`;
    template += `\n`;
    template += `    GupArray${up}* sorted = gup_array_${low}_create(a);\n`;
    
    // Since booleans only have two values, we don't have to do quicksort on the array.
    if (up === 'Bool') {
      template += `\n`;
      template += `    for (int i = 0; i < xs->count; i++) {\n`;
      template += `        if (xs->data[i] == false) {\n`;
      template += `            gup_array_${low}_prepend(a, sorted, false);\n`;
      template += `        } else {\n`;
      template += `            gup_array_${low}_append(a, sorted, true);\n`;
      template += `        }\n`;
      template += `    }\n`;
    } else {
      template += `    GupArray${up}* left   = gup_array_${low}_create(a);\n`;
      template += `    GupArray${up}* right  = gup_array_${low}_create(a);\n`;
      template += `\n`;
      template += `    // Choose the last item as the pivot for no particular reason.\n`;
      template += `    const int pivot_idx = xs->count - 1;\n`;

      if (up === 'String') template += `    ${t}* pivot = xs->data[pivot_idx];\n`;
      else                 template += `    ${t} pivot = xs->data[pivot_idx];\n`;

      template += `\n`;
      template += `    for (int i = 0; i < xs->count; i++) {\n`;
      template += `        // Don't include the pivot.\n`;
      template += `        if (i == pivot_idx) continue;\n`;
      template += `\n`;
      
      if      (up === 'String') template += `    if (gup_string_compare(a, xs->data[i], *pivot) <= 0) {\n`;
      else if (up === 'Cstr')   template += `    if (strcmp(xs->data[i], pivot) <= 0) {\n`;
      else                      template += `    if (xs->data[i] <= pivot) {\n`;
      
      template += `            gup_array_${low}_append(a, left, xs->data[i]);\n`;
      template += `        } else {\n`;
      template += `            gup_array_${low}_append(a, right, xs->data[i]);\n`;
      template += `        }\n`;
      template += `    }\n`;
      template += `\n`;
      template += `    GupArray${up}* sorted_left  = gup_array_${low}_to_sorted(a, left);\n`;
      template += `    GupArray${up}* sorted_right = gup_array_${low}_to_sorted(a, right);\n`;
      template += `\n`;
      template += `    { // Construct the final array from the left, pivot, and right.\n`;
      template += `        for (int i = 0; i < sorted_left->count; i++) {\n`;
      template += `            gup_array_${low}_append(a, sorted, sorted_left->data[i]);\n`;
      template += `        }\n`;
      template += `\n`;
      template += `        gup_array_${low}_append(a, sorted, pivot);\n`;
      template += `        \n`;
      template += `        for (int i = 0; i < sorted_right->count; i++) {\n`;
      template += `            gup_array_${low}_append(a, sorted, sorted_right->data[i]);\n`;
      template += `        }\n`;
      template += `    }\n`;
    }

    template += `\n`;
    template += `    return sorted;\n`;
    template += `}\n`;

    return template;
}

main(); 
