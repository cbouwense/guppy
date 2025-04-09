const gen = (upper, lower, type) => {
  console.log(`void gup_array_${lower}_remove_at_index_no_preserve_order(GupArray${upper} *xs, const int index) {`);
  console.log(`    _gup_array_sanity_check(xs);`);
  console.log(`    gup_assert_verbose(0 <= index && index < xs->count, "You're trying to remove an index from an array that is out of bounds.");`);
  console.log(``);
  console.log(`    // Copy the last element into the element to remove`);
  console.log(`    // [1, 2, 3, 4, 5], 1 -> [1, 5, 3, 4, 5]`);
  console.log(`    xs->data[index] = xs->data[xs->count-1];`);
  console.log(``);
  console.log(`    // Remove the last element by decrementing the count`);
  console.log(`    // [1, 5, 3, 4, 5] -> [1, 5, 3, 4]`);
  console.log(`    xs->count--;`);
  console.log(`}`);
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
