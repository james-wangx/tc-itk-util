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

int SESSION_UTIL_get_fms_home(std::string &fms_home) {
    int rcode = ITK_ok;

    const char *fms_home_temp = TC_getenv("FMS_HOME");
    if (fms_home_temp == nullptr) {
        LOGGER_ERROR("FMS_HOME is not set");
        rcode = -1;
        goto CLEANUP;
    }

    fms_home = fms_home_temp;

CLEANUP:
    return rcode;
}

int SESSION_UTIL_get_tc_root(std::string &tc_root) {
    int rcode = ITK_ok;
    std::string fms_home;

    LOGGER_CST_GOTO(SESSION_UTIL_get_fms_home(fms_home));
    if (const size_t pos = fms_home.rfind("\\"); pos != std::string::npos) {
        tc_root = fms_home.substr(0, pos);
    }

CLEANUP:
    return rcode;
}

int SESSION_UTIL_get_tc_bin(std::string &tc_bin) {
    int rcode = ITK_ok;
    std::string tc_root;

    LOGGER_ITK_GOTO(SESSION_UTIL_get_tc_root(tc_root));
    tc_bin = tc_root + "\\bin";

CLEANUP:
    return rcode;
}
