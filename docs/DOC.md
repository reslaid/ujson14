# ujson14-doc

## Main classes and structures

### JValue

**The `JValue` structure represents a JSON value. It has the following fields**:

- `type` - **value type** (`JType`).
- `strValue` - **string value** (if applicable).
- `numValue` - **numeric value** (if applicable).
- `boolValue` - **boolean value** (if applicable).
- `objectValue` - **JSON object** (if applicable).
- `arrayValue` - **JSON array** (if applicable).

**The `JValue` structure also has the following conversion operators**:

- `operator double() const` - **conversion operator to double (numValue)**.
- `operator long() const` - **conversion operator to long ((long)numValue)**.
- `operator tstring_t() const` - **conversion operator to tstring_t (strValue)**.
- `operator tchar_t*() const` - **conversion operator to tchar_t\* (strValue.c_str)**.
- `operator bool() const` - **conversion operator to bool (boolValue)**.
- `operator jarray_t() const` - **conversion operator to jarray_t (arrayValue)**.
- `operator jobj_t() const` - **conversion operator to jobj_t (objectValue)**.

### JParser

**The `JParser` class is used to parse JSON strings. It has the following methods**:

- `JParser(const tstring_t& json)` - **constructor**.
- `JValue parse()` - **method for parsing JSON string**.
- `tstring_t stringify(const JValue& value, unsigned int indent = 0, unsigned int currentIndent = 0)` - **method for converting `JValue` to a string**.

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
