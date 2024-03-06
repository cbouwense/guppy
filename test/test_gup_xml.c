void test_gup_xml_has_tag(void) {
    // assert(gup_xml_has_tag("<foo/>", "foo"));
    assert(gup_xml_has_tag("<foo />", "foo"));
    assert(gup_xml_has_tag("<foo></foo>", "foo"));
    assert(!gup_xml_has_tag("<foo></foo>", "bar"));
    assert(gup_xml_has_tag("<foo><bar /></foo>", "bar"));
    assert(gup_xml_has_tag("<foo><bar></bar></foo>", "bar"));
}

void test_gup_xml_get_tag_attributes(void) {
    GupArrayString attrs = gup_xml_get_tag_attributes("<foo bar=\"baz\" />", "foo");

    assert(attrs.count == 1);
}

void test_gup_xml_parse(void) {
    GupXMLTag tag = gup_xml_parse("<foo>bar</foo>");

    assert(gup_sv_eq_cstr(tag.name, "foo") == 0);

    gup_array_ptr_free(tag.attributes);
    gup_array_ptr_free(tag.children);
}

void test_gup_xml(void) {
    test_gup_xml_parse();
    // test_gup_xml_has_tag();
    // test_gup_xml_get_tag_attributes();
}
