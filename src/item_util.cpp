#include <tccore/item.h>
#include <base_utils/ResultCheck.hxx>
#include <tccore/aom.h>
#include <tccore/aom_prop.h>
#include <fclasses/tc_string.h>

#include "item_util.hpp"
#include "logger.hpp"

extern logical debug;

int ITEM_UTIL_get_latest_released_revision(const tag_t item_tag, const char *status_name, tag_t *revision_tag) {
    int rcode = ITK_ok;
    int revision_count = 0;
    tag_t *revision_tags = nullptr;

    LOGGER_ITK_GOTO(ITEM_list_all_revs(item_tag, &revision_count, &revision_tags));
    for (int i = revision_count - 1; i >= 0; i--) {
        int release_status_count = 0;
        tag_t *release_status_tags = nullptr;
        const tag_t revision_tag_temp = revision_tags[i];
        LOGGER_ITK_GOTO(
            AOM_ask_value_tags(revision_tag_temp, "release_status_list", &release_status_count, &release_status_tags));
        for (int j = 0; j < release_status_count; j++) {
            const tag_t release_status_tag = release_status_tags[j];
            char *status_name_temp = nullptr;
            LOGGER_ITK_GOTO(AOM_ask_value_string(release_status_tag, "object_name", &status_name_temp));
            if (tc_strcmp(status_name_temp, status_name) == 0) {
                *revision_tag = revision_tag_temp;
                MEM_UTIL_FREE_ITK(revision_tags);
                MEM_UTIL_FREE_ITK(release_status_tags);
                MEM_UTIL_FREE_ITK(status_name_temp);
                goto CLEANUP;
            }
            MEM_UTIL_FREE_ITK(status_name_temp);
        }
        MEM_UTIL_FREE_ITK(release_status_tags);
    }

CLEANUP:
    MEM_UTIL_FREE_ITK(revision_tags);
    return rcode;
}
