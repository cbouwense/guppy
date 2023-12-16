const capitalizeFirstLetter = (string) => {
    return string.charAt(0).toUpperCase() + string.slice(1);
}

const module_declarations = (type) => {
    const first = type.charAt(0);
    const upperType = capitalizeFirstLetter(type);
    const typedef = `GupArray${upperType}`

return (
`GupArray${upperType} gup_array_from_${type}(const ${type} xs[], const int size);`)};

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
