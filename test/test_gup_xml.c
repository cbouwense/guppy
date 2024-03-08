void test_gup_xml_parse(void) {
    GupXMLTag tag = gup_xml_parse("<foo>bar</foo>");

    assert(strcmp(tag.name, "foo") == 0);
    assert(strcmp(tag.data, "bar") == 0);

    gup_array_ptr_free(tag.attributes);
    gup_array_ptr_free(tag.children);
}

void test_gup_xml(void) {
    test_gup_xml_parse();
}
