#ifndef SESSION_UTIL_HPP
#define SESSION_UTIL_HPP

#ifdef EXPORTLIBRARY
#undef EXPORTLIBRARY
#endif

#include <unidefs.h>
#include <textsrv/libtextsrv_exports.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern TEXTSRV_API int TXTSRV_get_current_locale(char **current_locale);

extern TEXTSRV_API int TXTSRV_set_current_locale(const char *locale);

#ifdef __cplusplus
}
#endif // __cplusplus

int SESSION_UTIL_get_worklist(tag_t *worklist_tag);

#endif // !SESSION_UTIL_HPP
