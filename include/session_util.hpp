#ifndef SESSION_UTIL_HPP
#define SESSION_UTIL_HPP

#ifdef EXPORTLIBRARY
#undef EXPORTLIBRARY
#endif

#include <textsrv/libtextsrv_exports.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern TEXTSRV_API int TXTSRV_get_current_locale(char **current_locale);

extern TEXTSRV_API int TXTSRV_set_current_locale(const char *locale);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !SESSION_UTIL_HPP
