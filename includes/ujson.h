#if !defined(_UJSON_REQUIRED)
# include "ujson/json.h"
#endif // !_UJSON_REQUIRED

#if !defined(_UJSON_PKG_REQUIRED)
# define _UJSON_PKG_REQUIRED    _UJSON_REQUIRED
#else

#if defined(_MSC_VER) || defined(__INTEL_COMPILER) || defined(__BORLANDC__)
# pragma message("The macro `_UJSON_PKG_REQUIRED` is already defined in the project")
#else
# warning "The macro `_UJSON_PKG_REQUIRED` is already defined in the project"
#endif

#endif // !_UJSON_PKG_REQUIRED

#if !defined(ujson)
# define ujson                  UJson14
#else

#if defined(_MSC_VER) || defined(__INTEL_COMPILER) || defined(__BORLANDC__)
# pragma message("The macro `ujson` is already defined in the project")
#else
# warning "The macro `ujson` is already defined in the project"
#endif

#endif // !ujson