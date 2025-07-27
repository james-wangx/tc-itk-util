#include <qry/qry.h>

#include "logger.h"
#include "qry_util.h"

extern logical debug;

int QRY_UTIL_query_one(const char *name, const int entries_count, const char **entries, const char **values,
                       tag_t *result_tag)
{
    int rcode = ITK_ok, result_count = 0;
    tag_t query_tag = NULLTAG;
    tag_t *result_tags = NULL;

    LOGGER_ITK_GOTO(QRY_find2(name, &query_tag));
    if (query_tag == NULLTAG)
    {
        LOGGER_ERROR("Query not found: %s", name);
        rcode = -1;
        goto CLEANUP;
    }

    LOGGER_ITK_GOTO(QRY_execute(query_tag, entries_count, entries, values, &result_count, &result_tags));
    if (result_count == 0)
    {
        LOGGER_WARN("Found no results");
        rcode = -2;
        goto CLEANUP;
    }
    if (result_count > 1)
    {
        LOGGER_WARN("Found multiple results: %d", result_count);
    }

    *result_tag = result_tags[0];

CLEANUP:
    MEM_UTIL_FREE_ITK(result_tags);
    return rcode;
}
