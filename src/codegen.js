function generate(uppercase, lowercase, type) {
    console.log(`void gup_array_${lowercase}_prepend(GupArray${uppercase} *xs, ${type} x) {`);
    console.log(`    if (xs->count == xs->capacity) {`);
    console.log(`        const int new_capacity = xs->capacity == 0 ? 1 : xs->capacity * 2;`);
    console.log(`        xs->data = realloc(xs->data, new_capacity * sizeof(${type}));`);
    console.log(`        xs->capacity = new_capacity;`);
    console.log(`    }`);
    console.log(``);
    console.log(`    for (int i = xs->count; i > 0; i--) {`);
    console.log(`        xs->data[i] = xs->data[i-1];`);
    console.log(`    }`);
    console.log(`    xs->data[0] = x;`);
    console.log(`    xs->count++;`);
    console.log(`}`);
    console.log('')
}

generate('Bool', 'bool', 'bool');
generate('Char', 'char', 'char');
generate('Double', 'double', 'double');
generate('Float', 'float', 'float');
generate('Int', 'int', 'int');
generate('Long', 'long', 'long');
generate('Short', 'short', 'short');
generate('Ptr', 'ptr', 'void*');
generate('String', 'string', 'GupArrayChar');