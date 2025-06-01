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
        console.log(gen_gup_array_function_defs(...kind));
        // console.log(gen_gup_array_create(...kind));
        // console.log(gen_gup_array_destroy(...kind));
    }
}

const gen_gup_array_function_defs = (up, low, t) => {
    let template = ``;
    template += `GupArray${up}*\tgup_array_${low}_create(GupAllocator* a);\n`
    template += `GupArray${up}*\tgup_array_${low}_create_from_array(GupAllocator* a, const ${t} xs[], const int size);\n`
    if (up === 'Char')
    template += `GupArrayChar*\tgup_array_char_create_from_cstr(GupAllocator* a, char xs[]);\n`
    if (up === 'String')
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

const gen_gup_array_destroy = (up, low, t) =>
`void gup_array_${low}_destroy(GupArray${up}* xs) {
    free(xs);
}
`;

main();
