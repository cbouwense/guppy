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
        //console.log(gen_gup_array_equals(...kind));
        // console.log(gen_gup_array_print(...kind));
        // console.log(gen_gup_array_debug(...kind));
        console.log(gen_gup_array_append(...kind));
    }
}

const gen_gup_array_function_defs = (up, low, t) => {
    let template = ``;
    template += `GupArray${up}*\tgup_array_${low}_create(GupAllocator* a);\n`
    template += `GupArray${up}*\tgup_array_${low}_create_from_array(GupAllocator* a, const ${t} xs[], const int size);\n`
    if (up === 'Char')
    template += `GupArrayChar*\tgup_array_char_create_from_cstr(GupAllocator* a, char xs[]);\n`
    template += `GupArray${up}*\tgup_array_${low}_copy(GupAllocator* a, const GupArray${up}* xs);\n`
    template += `bool          \tgup_array_${low}_contains(const GupArray${up}* xs, const ${t} x);\n`
    template += `void          \tgup_array_${low}_destroy(GupArray${up}* xs);\n`
    template += `bool          \tgup_array_${low}_equals(const GupArray${up}* xs, const GupArray${up}* ys);\n`
    if (up === 'Char')
    template += `bool         \tgup_array_char_equals_cstr(GupArrayChar* xs, const char* cstr);\n`
    template += `void          \tgup_array_${low}_print(const GupArray${up}* xs);\n`
    template += `void          \tgup_array_${low}_append(GupAllocator* a, GupArray${up}* xs, const ${t} x);\n`
    if (up === 'String')
    template += `void          \tgup_array_string_append_cstr(GupAllocator* a, GupArrayString* xs, const char cstr[]);\n`
    template += `void          \tgup_array_${low}_prepend(GupAllocator* a, GupArray${up}* xs, const ${t} x);\n`
    template += `int           \tgup_array_${low}_find_index_of(const GupArray${up}* xs, const ${t} x);\n`
    template += `void          \tgup_array_${low}_remove(GupArray${up}* xs, const ${t} x, const int count_to_remove);\n`
    template += `void          \tgup_array_${low}_remove_all(GupArray${up}* xs, const ${t} x);\n`
    template += `void          \tgup_array_${low}_remove_at_index_preserve_order(GupArray${up}* xs, const int index);\n`
    template += `void          \tgup_array_${low}_remove_at_index_no_preserve_order(GupArray${up}* xs, const int index);\n`
    template += `GupArray${up}*\tgup_array_${low}_sort(GupAllocator* a, const GupArray${up}* xs);\n`
    if (up === 'Char')
    template += `char*        \tgup_array_char_to_cstr(GupAllocator* a, GupArrayChar* chars);\n`
    if (up === 'String')
    template += `char**       \tgup_array_string_to_cstrs(GupAllocator* a, GupArrayString strs);\n`
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

const gen_gup_array_create_from_array = (up, low, t) =>
`GupArray${up}* gup_array_${low}_create_from_array(GupAllocator* a, const ${t} xs[], const int size) {
    const int capacity       = size > GUP_ARRAY_DEFAULT_CAPACITY ? size : GUP_ARRAY_DEFAULT_CAPACITY;
    const int bytes_to_alloc = capacity * sizeof(${t});
    const int bytes_to_copy  = size * sizeof(${t});

    GupArray${up} *new;
    new           = gup_alloc(a, sizeof(*new) + sizeof(${t}) * bytes_to_alloc);
    new->capacity = capacity;
    new->count    = size;

    if (new->data != NULL) {
        memcpy(new->data, xs, bytes_to_copy);
    }

    return new;
}
`;

const gen_gup_array_copy = (up, low, t) => {
    let template = ``;
    template += `GupArray${up}* gup_array_${low}_copy(GupAllocator* a, const GupArray${up}* xs) {\n`;
    template += `    GupArray${up}* new = gup_alloc(a, sizeof(GupArray${up}) + sizeof(${t}) * xs->capacity);\n`;
    template += `\n`;
    template += `    new->capacity = xs->capacity;\n`;
    template += `    new->count    = xs->count;\n`;
    template += `\n`;
    if (up === 'String') {
        template += `    for (int i = 0; i < xs->count; i++) {\n`;
        template += `        new->data[i] = gup_array_char_copy(a, xs->data[i]);\n`;
        template += `    }\n`;
    } else {
        template += `    if (new->data != NULL) {\n`;
        template += `        memcpy(new->data, xs->data, xs->count * sizeof(${t}));\n`;
        template += `    }\n`;
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
    template += `bool gup_array_${low}_contains(const GupArray${up}* xs, const ${t} x) {\n`;
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
    if (up === 'String')    template += `        if (!gup_array_char_equals(xs->data[i], x)) return false;\n`
    else if (up === 'Cstr') template += `        if (strcmp(xs->data[i], x) != 0) return false;\n`
    else                    template += `        if (xs->data[i] != ys->data[i]) return false;\n`;
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
    else if (up === 'Double' || up === 'Float' || up === 'Short') {
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
    else if (up === 'String') {
        template += `       printf("  \\"");\n`;
        template += `       for (int j = 0; j < xs->data[i].count; j++) {\n`;
        template += `           printf("%c", xs->data[i].data[j]);\n`;
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
    if (up === 'String') {
        template += `/** Appends the struct, does NOT copy. */\n`;
    }
    template += `void gup_array_${low}_append(GupAllocator* a, GupArray${up}* xs, const ${t} x) {\n`;
    template += `    GUP_RESIZE_ARRAY_IF_NEEDED(a, xs, ${t});\n`;
    template += `\n`;
    template += `    xs->data[xs->count] = x;\n`;
    template += `    xs->count++;\n`;
    template += `}\n`;
    return template;
};

main(); 
