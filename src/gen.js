const gen = (upper, lower, type) => {
  console.log(`/**`);
  console.log(` * @return zero-indexed index of the element, -1 if not found.`);
  console.log(` */`);
  console.log(`void gup_array_${lower}_find_index_of(const GupArray${upper} *xs, ${type} x) {`);
  console.log(`  for (int i = 0; i < xs->count; i++) {`);
  console.log(`      if (xs->data[i] == x) {`);
  console.log(`          return i;`);
  console.log(`      }`);
  console.log(`  }`);
  console.log(``);
  console.log(`  return -1;`);
  console.log(`}`);
  console.log(``);
};

gen('Bool', 'bool', 'bool');
gen('Char', 'char', 'char');
gen('Double', 'double', 'double');
gen('Float', 'float', 'float');
gen('Int', 'int', 'int');
gen('Long', 'long', 'long');
gen('Ptr', 'ptr', 'void*');
gen('Short', 'short', 'short');
gen('String', 'string', 'GupString');
gen('Cstr', 'cstr', 'char*');
