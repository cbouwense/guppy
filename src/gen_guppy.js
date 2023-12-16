const capitalizeFirstLetter = (string) => {
    return string.charAt(0).toUpperCase() + string.slice(1);
}

const module_declarations = (type) => {
    const first = type.charAt(0);
    const upper = capitalizeFirstLetter(type);
    const typedef = `GupArray${upper}`

return (
`void gup_array_append_${type}(GupArray${upper} *xs, ${type} x);`)};

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
