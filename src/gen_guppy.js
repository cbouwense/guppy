const capitalizeFirstLetter = (string) => {
    return string.charAt(0).toUpperCase() + string.slice(1);
}

const module_declarations = (t) => {
    const f = t.charAt(0);
    const T = capitalizeFirstLetter(t);

return (
`
{ // ${t}
    GupArray${T} xs = gup_array_from_${t}(static_${f}s, gup_array_size(static_${f}s));
    GupArray${T} ys = gup_array_from_${t}(static_${f}s, gup_array_size(static_${f}s));

    assert(gup_array_eq_${t}(xs, ys) == true);
    assert(gup_array_eq_${t}(ys, xs) == true);

    free(xs.data);
    free(ys.data);
}`)};

const primitives = [
    'bool',
    'char',
    'double',
    'float',
    'int',
    'long',
    'short',
].sort((a, b) => a.localeCompare(b));

primitives.forEach(p => {
    console.log(module_declarations(p));
});
