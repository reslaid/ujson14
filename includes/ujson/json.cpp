#include "json.h"

UJson14::JParser::JParser(const tstring_t& json) : json(json), index(0) {}

UJson14::JValue UJson14::JParser::parse() {
    skipWhitespace();
    char currentChar = json[index];

    if (currentChar == _T('{')) {
        return parseObject();
    } else if (currentChar == _T('[')) {
        return parseArray();
    } else if (currentChar == _T('"')) {
        return parseString();
    } else if (currentChar == _T('-') || (currentChar >= _T('0') && currentChar <= _T('9'))) {
        return parseNumber();
    } else if (currentChar == _T('t') || currentChar == _T('f')) {
        return parseBool();
    } else if (currentChar == _T('n')) {
        return parseNull();
    }

    // Handle unexpected character
    throw std::runtime_error("Unexpected character");
}

tstring_t UJson14::JParser::stringify(const JValue& value, unsigned int indent, unsigned int currentIndent) {
    tstring_stream_t ss;
    stringifyValue(value, ss, indent, 0);
    return ss.str();
}

void UJson14::JParser::skipWhitespace() {
    while (isspace(json[index])) {
        index++;
    }
}

UJson14::JValue UJson14::JParser::parseObject() {
    JValue result;
    result.type = JType::OBJECT;

    index++;

    while (json[index] != _T('}')) {
        skipWhitespace();

        tstring_t key = parseString().strValue;

        skipWhitespace();
        if (json[index] != _T(':')) {
            throw std::runtime_error("Expected ':'");
        }
        index++;

        JValue value = parse();

        result.objectValue[key] = value;

        skipWhitespace();
        if (json[index] == _T(',')) {
            index++;
        } else if (json[index] != _T('}')) {
            throw std::runtime_error("Expected '}' or ','");
        }
    }

    index++;

    return result;
}

UJson14::JValue UJson14::JParser::parseArray() {
    JValue result;
    result.type = JType::ARRAY;

    index++;

    while (json[index] != _T(']')) {
        skipWhitespace();

        JValue value = parse();

        result.arrayValue.push_back(value);

        skipWhitespace();
        if (json[index] == _T(',')) {
            index++;
        } else if (json[index] != _T(']')) {
            throw std::runtime_error("Expected ']' or ','");
        }
    }

    index++;

    return result;
}

UJson14::JValue UJson14::JParser::parseString() {
    JValue result;
    result.type = JType::STRING;

    index++;

    size_t start = index;
    while (json[index] != _T('"')) {
        index++;
    }
    result.strValue = json.substr(start, index - start);

    index++;

    return result;
}

UJson14::JValue UJson14::JParser::parseNumber() {
    JValue result;
    result.type = JType::NUMBER;

    size_t start = index;
    while (isdigit(json[index]) || json[index] == _T('.') || json[index] == _T('e') || json[index] == _T('E') || json[index] == _T('+') || json[index] == _T('-')) {
        index++;
    }
    result.strValue = json.substr(start, index - start);

    try {
        result.numValue = std::stod(result.strValue);
    } catch (...) {
        throw std::runtime_error("Invalid number format");
    }

    return result;
}

UJson14::JValue UJson14::JParser::parseBool() {
    JValue result;
    result.type = JType::BOOL;

    if (json.substr(index, 4) == _T("true")) {
        result.boolValue = true;
        index += 4;
    } else if (json.substr(index, 5) == _T("false")) {
        result.boolValue = false;
        index += 5;
    } else {
        throw std::runtime_error("Invalid boolean value");
    }

    return result;
}

UJson14::JValue UJson14::JParser::parseNull() {
    JValue result;
    result.type = JType::NULL_VALUE;

    if (json.substr(index, 4) == _T("null")) {
        index += 4;
    } else {
        throw std::runtime_error("Invalid null value");
    }

    return result;
}

void UJson14::JParser::stringifyValue(const UJson14::JValue& value, tstring_stream_t& ss, unsigned int indent, unsigned int currentIndent) {
    switch (value.type) {
        case JType::OBJECT:
            ss << _T("{");
            if (indent > 0) ss << _T("\n");
            for (auto it = value.objectValue.begin(); it != value.objectValue.end(); ++it) {
                if (it != value.objectValue.begin()) {
                    ss << _T(",");
                    if (indent > 0) ss << _T("\n");
                }
                if (indent > 0) ss << tstring_t(currentIndent + indent, _T(' '));
                ss << _T("\"") << it->first << _T("\":");
                stringifyValue(it->second, ss, indent, currentIndent + indent);
            }
            if (indent > 0) ss << _T("\n") << tstring_t(currentIndent, _T(' '));
            ss << _T("}");
            break;
        case JType::ARRAY:
            ss << _T("[");
            if (indent > 0) ss << _T("\n");
            for (size_t i = 0; i < value.arrayValue.size(); ++i) {
                if (i != 0) {
                    ss << _T(",");
                    if (indent > 0) ss << _T("\n");
                }
                if (indent > 0) ss << tstring_t(currentIndent + indent, _T(' '));
                stringifyValue(value.arrayValue[i], ss, indent, currentIndent + indent);
            }
            if (indent > 0) ss << _T("\n") << tstring_t(currentIndent, _T(' '));
            ss << _T("]");
            break;
        case JType::STRING:
            ss << _T("\"") << value.strValue << _T("\"");
            break;
        case JType::NUMBER:
            ss << value.numValue;
            break;
        case JType::BOOL:
            ss.write(value.boolValue ? _T("true") : _T("false"), value.boolValue ? 4 : 5);
            break;
        case JType::NULL_VALUE:
            ss << _T("null");
            break;
    }
}