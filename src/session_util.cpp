#include "session_util.h"
#include "logger.h"
#include "qry_util.h"
#include "string_util.h"

extern logical debug;
extern char *user;

int SESSION_UTIL_get_worklist(tag_t *worklist_tag)
{
    int rcode = ITK_ok;
    const char *entries[] = {"Type", "Owning User"};
    const char *values[] = {"User_Inbox", user};

    LOGGER_ITK_GOTO(QRY_UTIL_query_one("General...", 2, entries, values, worklist_tag));

CLEANUP:
    return rcode;
}

int SESSION_UTIL_get_session(tag_t *session_tag)
{
    int rcode = ITK_ok;

    LOGGER_ITK_GOTO(POM_ask_session(session_tag));

CLEANUP:
    return rcode;
}

int SESSION_UTIL_get_fms_home(char **fms_home)
{
    int rcode = ITK_ok;

    const char *fms_home_temp = TC_getenv("FMS_HOME");
    if (fms_home_temp == NULL)
    {
        LOGGER_ERROR("FMS_HOME is not set");
        rcode = -1;
        goto CLEANUP;
    }

    LOGGER_CST_GOTO(STRING_UTIL_duplicate(fms_home_temp, fms_home));

CLEANUP:
    return rcode;
}

int SESSION_UTIL_get_tc_root(char **tc_root)
{
    int rcode = ITK_ok;
    size_t index = 0;
    char *fms_home = NULL;

    LOGGER_CST_GOTO(SESSION_UTIL_get_fms_home(&fms_home));
    LOGGER_CST_GOTO(STRING_UTIL_last_index_of(fms_home, '\\', &index));
    LOGGER_CST_GOTO(STRING_UTIL_substring(fms_home, 0, index, tc_root));

CLEANUP:
    return rcode;
}

int SESSION_UTIL_get_tc_bin(char **tc_bin)
{
    int rcode = ITK_ok;
    char *tc_root = NULL;
    size_t tc_bin_len = 0;

    LOGGER_CST_GOTO(SESSION_UTIL_get_tc_root(&tc_root));
    LOGGER_CST_GOTO(STRING_UTIL_append(tc_bin, &tc_bin_len, tc_root));
    LOGGER_CST_GOTO(STRING_UTIL_append(tc_bin, &tc_bin_len, "\\bin"));

CLEANUP:
    return rcode;
}

int SESSION_UTIL_get_current_user(char **user_name, tag_t *user_tag)
{
    int rcode = ITK_ok;

    LOGGER_ITK_GOTO(POM_get_user(user_name, user_tag));

CLEANUP:
    return rcode;
}
