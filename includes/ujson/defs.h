
#pragma once

#ifndef _UJSON_DEFS_REQUIRED
# define _UJSON_DEFS_REQUIRED 0.9f

#ifdef __cplusplus
# include <string>
# include <sstream>
#endif

#undef _T
#undef _TCHAR

#ifndef _T
# ifdef _UNICODE
#  define _T(STR)           L##STR
#  define _TCHAR            wchar_t

# ifdef __cplusplus
#  define _TSTRING          std::wstring
#  define _TSTRINGSTREAM    std::wstringstream
# endif

# else
#  define _T(STR)           STR
#  define _TCHAR            char

# ifdef __cplusplus
#  define _TSTRING          std::string
#  define _TSTRINGSTREAM    std::stringstream
# endif

# endif

# ifndef __cplusplus
#  define _TSTRING          _TCHAR*
# endif

#endif

typedef _TCHAR              tchar_t;
typedef _TSTRING            tstring_t;
typedef _TSTRINGSTREAM      tstring_stream_t;

#endif // !_UJSON_DEFS_REQUIRED