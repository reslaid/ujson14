#pragma once

#ifndef _UJSON_BINARY_EXTENSION
#define _UJSON_BINARY_EXTENSION 0.8f

#include "../ujson/defs.h"

#include <vector>

typedef __uint8_t                jbyte_t;
typedef std::vector<jbyte_t>     jbytes_t;

namespace UJson14 {
    namespace Binary {

        /**
         * @brief Converts a string to a byte vector.
         * @param str The string to convert.
         * @return bytes_t The byte vector.
         */
        jbytes_t strToByteVector(const tstring_t& str) {
            jbytes_t bytes(str.size());
            std::copy(str.begin(), str.end(), bytes.begin());
            return bytes;
        }

        /**
         * @brief Converts a byte vector to a string.
         * @param bytes The byte vector to convert.
         * @return tstring_t The resulting string.
         */
        tstring_t byteVectorToStr(const jbytes_t& bytes) {
            return tstring_t(bytes.begin(), bytes.end());
        }
    }
}

#endif // !_UJSON_BINARY_EXTENSION
