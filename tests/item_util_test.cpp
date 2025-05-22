#include <gtest/gtest.h>

#include <tc/tc_startup.h>

#include "item_util.hpp"

TEST(item_util_test, ITEM_UTIL_get_latest_released_revision) {
    int rcode = ITK_ok;
    const auto item_uid = "QEqhi$pvJ72RwB";
    const auto revision_uid = "w8ohi$pvJ72RwB";
    tag_t item_tag = NULLTAG;
    tag_t revision_tag = NULLTAG;
    tag_t revision_tag_exp = NULLTAG;

    ITK__convert_uid_to_tag(item_uid, &item_tag);
    ITK__convert_uid_to_tag(revision_uid, &revision_tag_exp);
    rcode = ITEM_UTIL_get_latest_released_revision(item_tag, "TCM Released", &revision_tag);

    EXPECT_EQ(rcode, ITK_ok) << "Failed to get latest released revision";
    EXPECT_EQ(revision_tag, revision_tag_exp) << "Revision tag is not the same as expected";
}
