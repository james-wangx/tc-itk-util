#include <gtest/gtest.h>

#include <tcdefs.h>

#include "session_util.hpp"
#include "mem_util.hpp"

TEST(session_util_test, TXTSRV_get_current_locale) {
    int rcode = ITK_ok;
    char *current_locale = nullptr;

    rcode = TXTSRV_get_current_locale(&current_locale);

    EXPECT_EQ(rcode, ITK_ok) << "Failed to get current locale";
    EXPECT_EQ(std::string(current_locale),
              std::string("en_US")) << "current locale: " << current_locale << ", expected: en_US";

    MEM_UTIL_FREE(current_locale);
}

TEST(session_util_test, TXTSRV_set_current_locale) {
    int rcode = ITK_ok;
    const auto locale = "zh_CN";
    char *current_locale = nullptr;

    rcode = TXTSRV_set_current_locale(locale);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to set current locale";

    rcode = TXTSRV_get_current_locale(&current_locale);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to get current locale";
    EXPECT_EQ(std::string(current_locale),
              std::string(locale)) << "current locale: " << current_locale << ", expected: " << locale;

    TXTSRV_set_current_locale("en_US");

    MEM_UTIL_FREE(current_locale);
}
