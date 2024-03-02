
#pragma once

/**
 * @file json.h (#include <ujson/json.h>)
 * @author Reslaid
 * @mainpage https://github.com/reslaid/ujson14.git
 * @brief This file contains the declaration of the JValue struct and JParser class.
 */

#ifndef _UJSON_REQUIRED
# define _UJSON_REQUIRED 1.3f

#pragma region includes

#include "defs.h"

#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <type_traits>
#include <locale>

#pragma endregion // !includes

#pragma region enums & structures

namespace UJson14
{
    /**
     * @brief Enumeration for different types of JSON values.
     */
    enum class JType {
        OBJECT, ///< Object type
        ARRAY, ///< Array type
        STRING, ///< String type
        NUMBER, ///< Number type
        BOOL, ///< Boolean type
        NULL_VALUE ///< Null value type
    };

    /**
     * @brief Structure representing a JSON value.
     */
    struct JValue {
        JType type; ///< Type of the JSON value
        tstring_t strValue; ///< String value
        double numValue; ///< Numeric value
        bool boolValue; ///< Boolean value
        std::unordered_map<tstring_t, JValue> objectValue; ///< Object value
        std::vector<JValue> arrayValue; ///< Array value

        /**
         * @brief Accessor for nested JSON values.
         * @tparam Args Variadic template arguments for the keys.
         * @param args Keys to access nested values.
         * @return JValue The nested JSON value.
         */
        template<typename... Args>
        const JValue operator()(Args&&... args) const {
            std::vector<tstring_t> keys{std::forward<Args>(args)...};
            auto current = &objectValue;
            for (size_t i = 0; i < keys.size() - 1; ++i) {
                current = &(*current).at(keys[i]).objectValue;
            }
            return (*current).at(keys.back());
        }

        /**
         * @brief Accessor for array values.
         * @param arrayIndex Index of the array element.
         * @return JValue The array element.
         */
        const JValue operator[](const size_t arrayIndex) const {
            return arrayValue.at(arrayIndex);
        }

        /**
         * @brief Conversion operator to double.
         * @return double The numeric value as double.
         */
        operator double() const {
            return this->numValue;
        }

        /**
         * @brief Conversion operator to long.
         * @return long The numeric value as long.
         */
        operator long() const {
            return (long)(double)*this;
        }

        /**
         * @brief Conversion operator to string.
         * @return tstring_t The string value.
         */
        operator tstring_t () const {
            return this->strValue;
        }

        /**
         * @brief Conversion operator to char*.
         * @return char* The string value as char*.
         */
        operator char* () const {
            return (char *)this->strValue.c_str();
        }

        /**
         * @brief Conversion operator to bool.
         * @return bool The boolean value.
         */
        operator bool () const {
            return this->boolValue;
        }

        /**
         * @brief Conversion operator to jarray_t.
         * @return jarray_t The array value.
         */
        operator std::vector<JValue>() const {
            return this->arrayValue;
        }

        /**
         * @brief Conversion operator to jobj_t.
         * @return jobj_t The object value.
         */
        operator std::unordered_map<tstring_t, JValue> () const {
            return this->objectValue;
        }
    };

    #pragma endregion // !enum & !structures

    #pragma region classes

    /**
     * @brief Class for parsing JSON strings.
     */
    class JParser {
    public:
        /**
         * @brief Constructor for JParser.
         * @param json The JSON string to parse.
         */
        JParser(const tstring_t& json);

        /**
         * @brief Parse the JSON string.
         * @return JValue The parsed JSON value.
         */
        JValue parse();

        /**
         * @brief Convert a JValue to a string.
         * @param value The JValue to stringify.
         * @param indent The indentation level.
         * @param currentIndent The current indentation level.
         * @return tstring_t The stringified JSON.
         */
        tstring_t stringify(const JValue& value, unsigned int indent = 0, unsigned int currentIndent = 0);

    private:
        tstring_t json; ///< The JSON string to parse.
        size_t index; ///< The current index in the JSON string.

        /**
         * @brief Skip whitespace characters in the JSON string.
         */
        void skipWhitespace();

        /**
         * @brief Parse a JSON object.
         * @return JValue The parsed JSON object.
         */
        JValue parseObject();

        /**
         * @brief Parse a JSON array.
         * @return JValue The parsed JSON array.
         */
        JValue parseArray();

        /**
         * @brief Parse a JSON string.
         * @return JValue The parsed JSON string.
         */
        JValue parseString();

        /**
         * @brief Parse a JSON number.
         * @return JValue The parsed JSON number.
         */
        JValue parseNumber();

        /**
         * @brief Parse a JSON boolean.
         * @return JValue The parsed JSON boolean.
         */
        JValue parseBool();

        /**
         * @brief Parse a JSON null value.
         * @return JValue The parsed JSON null value.
         */
        JValue parseNull();

        /**
         * @brief Stringify a JValue.
         * @param value The JValue to stringify.
         * @param ss The tstring_stream_t to append the stringified value to.
         * @param indent The indentation level.
         * @param currentIndent The current indentation level.
         */
        void stringifyValue(const JValue& value, tstring_stream_t& ss, unsigned int indent = 0, unsigned int currentIndent = 0);
    };

    typedef JValue                                  jvalue_t;
    typedef JType                                   jtype_t;
    typedef double                                  jnum_t;
    typedef std::unordered_map<tstring_t, jvalue_t> jobj_t;
    typedef std::vector<jvalue_t>                   jarray_t;
}

#pragma endregion // !classes

#endif // !_UJSON_REQUIRED