function generate(u, l, t) {
    console.log(`${t} gup_array_reduce_${l}(GupArray${u} xs, ${t} (*fn)(${t}, ${t}), ${t} start) {`);
    console.log(`    ${t} result = start;`);
    console.log(`    for (int i = 0; i < xs.count; i++) {`);
    console.log(`        result = fn(result, xs.data[i]);`);
    console.log(`    }`);
    console.log(`    return result;`);
    console.log(`}`);
    console.log(``);
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