#include <iostream>
#include <ujson.h>
#include <ujson_ext/ujsonb.h>

int main() {
    // Create a JSON string.
    tstring_t json = _T("{\"name\": \"John Doe\", \"age\": 30, \"isMarried\": false, \"children\": [\"Alice\", \"Bob\"]}");

    // Parse the JSON string.
    ujson::JParser parser(json);
    ujson::JValue parsed = parser.parse();

    // Access the fields.
    tstring_t name = parsed(_T("name"));
    long age = parsed(_T("age"));
    bool isMarried = parsed(_T("isMarried"));

    // Print the results.
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Is Married: " << isMarried << std::endl;
    std::cout << "Children: " << std::endl;

    ujson::jarray_t childs = parsed(_T("children")).arrayValue;

    for (const ujson::jvalue_t& child : childs) {
        std::cout << (tchar_t *)child << std::endl;
    }

    return 0;
}
