#include <iostream>
#include <cassert>
#include <ujson.h>

void testParsing() {
    std::string jsonString = R"({"key1": "value1", "key2": 42, "key3": true, "key4": null, "key5": [1, 2, 3], "key6": {"subkey": "subvalue"}})";
    UJson14::JParser parser(jsonString);
    UJson14::JValue parsedValue = parser.parse();

    assert(parsedValue.type == UJson14::JType::OBJECT);
    assert(parsedValue("key1").strValue == "value1");
    assert(static_cast<double>(parsedValue("key2")) == 42);
    assert(static_cast<bool>(parsedValue("key3")) == true);
    assert(parsedValue("key4").type == UJson14::JType::NULL_VALUE);
    assert((long)parsedValue("key5")[0] == 1);
    assert((long)parsedValue("key5")[1] == 2);
    assert((long)parsedValue("key5")[2] == 3);
    assert(parsedValue("key6", "subkey").strValue == "subvalue");
}

void testStringification() {
    UJson14::JValue value;
    value.type = UJson14::JType::OBJECT;

    value.objectValue["key1"] = UJson14::NewJValue(_T("value1"));
    value.objectValue["key2"] = UJson14::NewJValue(42L);
    value.objectValue["key3"] = UJson14::NewJValue(true);
    value.objectValue["key4"] = UJson14::NewJValue(UJson14::JType::NULL_VALUE);
    
    value.objectValue["key5"] = UJson14::NewJValue(UJson14::JType::ARRAY);

    value.objectValue["key5"].arrayValue.push_back(UJson14::NewJValue(1L));
    value.objectValue["key5"].arrayValue.push_back(UJson14::NewJValue(2L));
    value.objectValue["key5"].arrayValue.push_back(UJson14::NewJValue(3L));
    
    value.objectValue["key6"] = UJson14::NewJValue(UJson14::JType::OBJECT);
    value.objectValue["key6"].objectValue["subkey"] = UJson14::NewJValue(_T("subvalue"));
    
    assert(value.type == UJson14::JType::OBJECT);
    assert(value.objectValue.at("key1").type == UJson14::JType::STRING);
    assert(value.objectValue.at("key1").strValue == "value1");
    assert(value.objectValue.at("key2").type == UJson14::JType::NUMBER);
    assert(value.objectValue.at("key2").numValue == 42);
    assert(value.objectValue.at("key3").type == UJson14::JType::BOOL);
    assert(value.objectValue.at("key3").boolValue == true);
    assert(value.objectValue.at("key4").type == UJson14::JType::NULL_VALUE);
    assert(value.objectValue.at("key5").type == UJson14::JType::ARRAY);
    assert(value.objectValue.at("key5").arrayValue.at(0).numValue == 1);
    assert(value.objectValue.at("key5").arrayValue.at(1).numValue == 2);
    assert(value.objectValue.at("key5").arrayValue.at(2).numValue == 3);
    assert(value.objectValue.at("key6").type == UJson14::JType::OBJECT);
    assert(value.objectValue.at("key6").objectValue.at("subkey").type == UJson14::JType::STRING);
    assert(value.objectValue.at("key6").objectValue.at("subkey").strValue == "subvalue");
}

int main() {
    testParsing();
    testStringification();

    std::cout << __FILE__ << ": All tests passed successfully!" << std::endl;

    return 0;
}
