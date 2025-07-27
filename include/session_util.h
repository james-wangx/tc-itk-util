#ifndef SESSION_UTIL_HPP
#define SESSION_UTIL_HPP

#ifdef EXPORTLIBRARY
#undef EXPORTLIBRARY
#endif

#include <textsrv/libtextsrv_exports.h>
#include <unidefs.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    extern TEXTSRV_API int TXTSRV_get_current_locale(char **current_locale);

    extern TEXTSRV_API int TXTSRV_set_current_locale(const char *locale);

#ifdef __cplusplus
}
#endif // __cplusplus

int SESSION_UTIL_get_worklist(tag_t *worklist_tag);

int SESSION_UTIL_get_session(tag_t *session_tag);

int SESSION_UTIL_get_fms_home(char **fms_home);

int SESSION_UTIL_get_tc_root(char **tc_root);

int SESSION_UTIL_get_tc_bin(char **tc_bin);

int SESSION_UTIL_get_current_user(char **user_name, tag_t *user_tag);

int SESSION_UTIL_get_current_group(char **group_name);

#endif // !SESSION_UTIL_HPP
