#include "logger.hpp"
#include "qry_util.hpp"
#include "session_util.hpp"

extern logical debug;
extern char *user;

int SESSION_UTIL_get_worklist(tag_t *worklist_tag) {
    int rcode = ITK_ok;
    std::map<std::string, std::string> params = {
        {"Type", "User_Inbox"},
        {"Owning User", user}
    };

    LOGGER_ITK_GOTO(QRY_UTIL_query_one("General...", params, worklist_tag));

CLEANUP:
    return rcode;
}

int SESSION_UTIL_get_session(tag_t *session_tag) {
    int rcode = ITK_ok;

    LOGGER_ITK_GOTO(POM_ask_session(session_tag));

CLEANUP:
    return rcode;
}

int SESSION_UTIL_get_fms_home(char **fms_home) {
    int rcode = ITK_ok;

    const char *fms_home_temp = TC_getenv("FMS_HOME");
    if (fms_home_temp == nullptr) {
        LOGGER_ERROR("FMS_HOME is not set");
        rcode = -1;
        goto CLEANUP;
    }

    *fms_home = _strdup(fms_home_temp);

CLEANUP:
    return rcode;
}
