#ifndef TC_ITK_UTIL_TCUTIL_HXX
#define TC_ITK_UTIL_TCUTIL_HXX

#include <map>
#include <string>
#include <vector>

#include <tc/tc_arguments.h>
#include <unidefs.h>

#define LOGGER_DEBUG(fmt, ...)                                 \
    {                                                          \
        logger->debug(__FILE__, __LINE__, fmt, ##__VA_ARGS__); \
    }

#define LOGGER_INFO(fmt, ...)                                 \
    {                                                         \
        logger->info(__FILE__, __LINE__, fmt, ##__VA_ARGS__); \
    }

#define LOGGER_ERROR(code, fmt, ...)                                 \
    {                                                                \
        logger->error(__FILE__, __LINE__, code, fmt, ##__VA_ARGS__); \
    }

#define LOGGER_ERROR_GOTO(code, fmt, ...)                  \
    {                                                      \
        LOGGER_ERROR(code, fmt, ##__VA_ARGS__);            \
        char msg[1024];                                    \
        snprintf(msg, sizeof(msg), fmt, ##__VA_ARGS__);    \
        EMH_store_error_s1(EMH_severity_error, code, msg); \
        rcode = code;                                      \
        goto CLEANUP;                                      \
    }

#define LOGGER_ITK(func)                \
    {                                   \
        LOGGER_DEBUG("Call %s", #func); \
        ok = func;                      \
    }

#define LOGGER_REG(func, regName)                           \
    {                                                       \
        LOGGER_DEBUG("Call %s", #func);                     \
        ok = func;                                          \
        LOGGER_INFO("Registering " regName ", completed!"); \
    }

extern "C"
{
    int POM_AM__ask_application_bypass(logical* hasBypass);
    int POM_AM__set_application_bypass(logical bypass);
}

class TcUtil
{
public:
    static void addReleaseStatus(const std::vector<tag_t>& workspaceObjects, const std::string& statusType,
                                 logical retainReleasedDate);
    static std::map<std::string, std::string> askArgumentNamedValue(TC_argument_list_t* arguments);
    static std::vector<std::string> askPrefValues(const std::string& prefName);
    static std::vector<tag_t> askReleasedStatus(tag_t workspaceObject);
    static date_t askValueDate(tag_t object, const std::string& propName);
    static std::string askValueString(tag_t object, const std::string& propName);
    static std::vector<std::string> askValueStrings(tag_t object, const std::string& propName);
    static std::vector<tag_t> askValueTags(tag_t object, const std::string& propName);
    static std::string TcUtil::date2string(const date_t& date, const std::string& formatSt);
    static bool checkType(tag_t object, const std::string& typeName);
    static void deleteReleaseStatus(const std::vector<tag_t>& workspaceObjects, const std::string& statusType);
    static std::vector<tag_t> findRelatedTagsByType(tag_t primaryObject, const std::string& relationTypeName);
    static logical isTypeOf(tag_t object, const std::string& parentTypeName);
    static tag_t queryOne(const std::string& queryName, const std::vector<std::string>& entries,
                          const std::vector<std::string>& values);
    static std::vector<tag_t> where_used_top(tag_t object, const std::string& typeName);
};

#endif // TC_ITK_UTIL_TCUTIL_HXX
