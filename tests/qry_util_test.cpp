#include <gtest/gtest.h>

#include <tcdefs.h>
#include <tc/tc_startup.h>

#include "qry_util.hpp"

extern char *user;

TEST(qry_util_test, QRY_UTIL_query_one_by_name) {
    int rcode = ITK_ok;
    tag_t result_tag = NULLTAG;
    char *result_uid = nullptr;
    std::map<std::string, std::string> params = {
        {"Type", "User_Inbox"},
        {"Owning User", user}
    };

    rcode = QRY_UTIL_query_one("General...", params, &result_tag);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to query one by name";
    EXPECT_NE(result_tag, NULLTAG) << "Result tag is null";

    ITK__convert_tag_to_uid(result_tag, &result_uid);
    EXPECT_EQ(std::string("AwthCpYHJ72RwB"), result_uid);
}
