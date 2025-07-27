#include <gtest/gtest.h>

#include <tc/tc_startup.h>
#include <tccore/aom_prop.h>

#include "logger.h"
#include "qry_util.h"

extern logical debug;
extern char *user;

TEST(qry_util_test, QRY_UTIL_query_one)
{
    int rcode = ITK_ok;
    tag_t result_tag = NULLTAG;
    char *result_string = nullptr;
    const char *entries[] = {"Type", "Owning User"};
    const char *values[] = {"User_Inbox", user};

    rcode = QRY_UTIL_query_one("General...", 2, entries, values, &result_tag);
    EXPECT_EQ(rcode, ITK_ok) << "Failed to query one";
    EXPECT_NE(result_tag, NULLTAG) << "Result tag is null";

    LOGGER_ITK_PASS(AOM_ask_value_string(result_tag, "object_string", &result_string));
    EXPECT_EQ(std::string("My Worklist"), std::string(result_string));
}
