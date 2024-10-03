function generate(uppercase, lowercase, type) {
    console.log(`GupArray${uppercase} gup_array_${lowercase}_filter(GupArray${uppercase} xs, bool (*fn)(${type})) {`);
    console.log(`    GupArray${uppercase} new = gup_array_${lowercase}_create();`);
    console.log(``);
    console.log(`    for (int i = 0; i < xs.count; i++) {`);
    console.log(`        if (fn(xs.data[i])) {`);
    console.log(`            gup_array_${lowercase}_append(&new, xs.data[i]);`);
    console.log(`        }`);
    console.log(`    }`);
    console.log(``);
    console.log(`    return new;`);
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