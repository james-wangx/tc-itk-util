#include <gtest/gtest.h>

#include <tccore/aom_prop.h>

#include "logger.h"
#include "mem_util.h"
#include "session_util.h"

extern logical debug;

TEST(session_util_test, TXTSRV_get_current_locale)
{
    int rcode = ITK_ok;
    char *current_locale = nullptr;

    rcode = TXTSRV_get_current_locale(&current_locale);

    EXPECT_EQ(rcode, ITK_ok) << "Failed to get current locale";
    EXPECT_EQ(std::string(current_locale), std::string("en_US"))
        << "current locale: " << current_locale << ", expected: en_US";

    MEM_UTIL_FREE_ITK(current_locale);
}

TEST(session_util_test, TXTSRV_set_current_locale)
{
    int rcode = ITK_ok;
    const auto locale = "zh_CN";
    char *current_locale = nullptr;

    rcode = TXTSRV_set_current_locale(locale);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to set current locale";

    rcode = TXTSRV_get_current_locale(&current_locale);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to get current locale";
    EXPECT_EQ(std::string(current_locale), std::string(locale))
        << "current locale: " << current_locale << ", expected: " << locale;

    TXTSRV_set_current_locale("en_US");

    MEM_UTIL_FREE_ITK(current_locale);
}

TEST(session_util_test, SESSION_UTIL_get_worklist)
{
    int rcode = ITK_ok;
    tag_t worklist_tag = NULLTAG;
    char *worklist_string = nullptr;

    rcode = SESSION_UTIL_get_worklist(&worklist_tag);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to get worklist";

    LOGGER_ITK_PASS(AOM_ask_value_string(worklist_tag, "object_string", &worklist_string));
    EXPECT_EQ(std::string("My Worklist"), std::string(worklist_string))
        << "Worklist string: " << worklist_string << ", expected: My Worklist";

    MEM_UTIL_FREE_ITK(worklist_string);
}

TEST(session_util_test, SESSION_UTIL_get_session)
{
    int rcode = ITK_ok;
    tag_t session_tag = NULLTAG;

    rcode = SESSION_UTIL_get_session(&session_tag);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to get session";
    EXPECT_NE(session_tag, NULLTAG) << "Session tag is NULLTAG";
}

TEST(session_util_test, SESSION_UTIL_get_fms_home)
{
    int rcode = ITK_ok;
    char* fms_home;

    rcode = SESSION_UTIL_get_fms_home(&fms_home);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to get FMS_HOME";
    EXPECT_EQ(fms_home, std::string(R"(D:\Siemens\Teamcenter2412FourTier\tccs)"))
        << "fms_home: " << fms_home << R"(, expected: D:\Siemens\Teamcenter2412FourTier\tccs)";
}

TEST(session_util_test, SESSION_UTIL_get_tc_root)
{
    int rcode = ITK_ok;
    char* tc_root;

    rcode = SESSION_UTIL_get_tc_root(&tc_root);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to get TC_ROOT";
    EXPECT_EQ(tc_root, std::string(R"(D:\Siemens\Teamcenter2412FourTier)"))
        << "tc_root: " << tc_root << R"(, expected: D:\Siemens\Teamcenter2412FourTier)";
}

TEST(session_util_test, SESSION_UTIL_get_tc_bin)
{
    int rcode = ITK_ok;
    char* tc_bin;

    rcode = SESSION_UTIL_get_tc_bin(&tc_bin);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to get TC_BIN";
    EXPECT_EQ(tc_bin, std::string(R"(D:\Siemens\Teamcenter2412FourTier\bin)"))
        << "tc_bin: " << tc_bin << R"(, expected: D:\Siemens\Teamcenter2412FourTier\bin)";
}

TEST(session_util_test, SESSION_UTIL_get_current_user)
{
    int rcode = ITK_ok;
    char* user_name;
    tag_t user_tag = NULLTAG;

    rcode = SESSION_UTIL_get_current_user(&user_name, &user_tag);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to get current user";
    EXPECT_EQ(user_name, std::string("王舰")) << "user_name: " << user_name << ", expected: 王舰";
    EXPECT_NE(user_tag, NULLTAG) << "user_tag is NULLTAG";
}
