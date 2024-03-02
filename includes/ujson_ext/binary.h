#pragma once

#include "../ujson/defs.h"

#include <vector>
#include <string>
#include <sstream>

#define jbyte_t                  unsigned tchar_t
typedef std::vector<jbyte_t>     jbytes_t;

namespace UJson14 {
    namespace Binary {
        tstring_t deserialize(const jbytes_t& bytes) {
            return tstring_t(bytes.begin(), bytes.end());
        }

        jbytes_t serialize(const tstring_t& str) {
            return jbytes_t(str.begin(), str.end());
        }
    }
}