# ujson14-doc

## Functions

### `UJson14::NewJValue(UJson14::JType type)`

Creates a new `UJson14::JValue` with the specified type.

### `UJson14::NewJValue(double value)`

Creates a new `UJson14::JValue` with the `NUMBER` type and the specified `double` value.

### `UJson14::NewJValue(long value)`

Creates a new `UJson14::JValue` with the `NUMBER` type and the specified `long` value.

### `UJson14::NewJValue(const tstring_t& value)`

Creates a new `UJson14::JValue` with the `STRING` type and the specified `tstring_t` value.

### `UJson14::NewJValue(const tchar_t* value)`

Creates a new `UJson14::JValue` with the `STRING` type and the specified C-style string value.

### `UJson14::NewJValue(bool value)`

Creates a new `UJson14::JValue` with the `BOOL` type and the specified `bool` value.

### `UJson14::NewJValue(const std::vector<UJson14::JValue>& value)`

Creates a new `UJson14::JValue` with the `ARRAY` type and the specified vector of `JValue` objects.

### `UJson14::NewJValue(const std::unordered_map<tstring_t, UJson14::JValue>& value)`

Creates a new `UJson14::JValue` with the `OBJECT` type and the specified unordered map of `tstring_t` keys and `JValue` values.

## Classes

### `UJson14::JParser`

A class for parsing JSON strings into structured data.

- `JParser(const tstring_t& json)`: Constructor that takes a `tstring_t` JSON string as input.
- `JValue parse()`: Parses the JSON string and returns a `JValue` object representing the parsed data.
- `tstring_t stringify(const JValue& value, unsigned int indent, unsigned int currentIndent)`: Converts the `JValue` object into a formatted JSON string with the specified indentation level.

### `UJson14::JValue`

A class representing a JSON value.

- `enum JType { OBJECT, ARRAY, STRING, NUMBER, BOOL, NULL_VALUE }`: Enumeration representing the different types of JSON values.
- `JType type`: The type of the JSON value.
- `tstring_t strValue`: The string value of the JSON value (for `STRING` type).
- `double numValue`: The numeric value of the JSON value (for `NUMBER` type).
- `bool boolValue`: The boolean value of the JSON value (for `BOOL` type).
- `std::vector<JValue> arrayValue`: The array value of the JSON value (for `ARRAY` type).
- `std::unordered_map<tstring_t, JValue> objectValue`: The object value of the JSON value (for `OBJECT` type).

- Operators

     - `operator double() const` - **conversion operator to double (numValue)**.
     - `operator long() const` - **conversion operator to long ((long)numValue)**.
     - `operator tstring_t() const` - **conversion operator to tstring_t (strValue)**.
     - `operator tchar_t*() const` - **conversion operator to tchar_t\* (strValue.c_str)**.
     - `operator bool() const` - **conversion operator to bool (boolValue)**.
     - `operator jarray_t() const` - **conversion operator to jarray_t (arrayValue)**.
     - `operator jobj_t() const` - **conversion operator to jobj_t (objectValue)**.

## Namespaces

### `UJson14`

The namespace that contains the classes and functions for the UJson14 library.

- `UJson14::JValue`: The class representing a JSON value.
- `UJson14::JParser`: The class for parsing JSON strings.
- `UJson14::NewJValue`: Functions for creating `JValue` objects with specific types or values.

## Macros
### _T

**The `_T` macro takes arguments: `STR`**
---
> If the `_UNICODE` macro is set
     Returns `L##STR`
---
> Otherwise returns `STR`

### ujson

**The `ujson` macro contains the `UJson14` namespace**

## Data types
### tchar_t

**The `tchar_t` type is designed to compare whether the `_UNICODE` macro is defined or not**
---
> If this is true it will be equal to `wchar_t`
---
> If false then normal ASCII `char`

### tstring_t

**The `tstring_t` type works a little differently**
---
> If defined `__cplusplus` then:
- **A comparison is made whether the `_UNICODE` macro is set or not**
---
- **If this is true it will be equal to `std::wstring`**
---
- **Otherwise `std::string`**
---
> If there is no `__cplusplus` macro:
- **Equal to `tchar_t*`**

### jvalue_t

**The type `jvalue_t` is a direct type of JValue**

### jtype_t

**The type `jtype_t` is a direct JType**

### jobj_t

**The `jobj_t` type is a renamed `std::unordered_map<tstring_t, jvalue_t>`**
> *Used for shortening*

### jarray_t

**The `jarray_t` type is also a renamed `std::vector<jvalue_t>`**
> *Used for shortening*

### jnum_t

**The `jnum_t` type is the standard type of numeric values in the parser, definition: `double`**
