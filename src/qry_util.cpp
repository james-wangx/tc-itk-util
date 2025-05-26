#include <map>
#include <string>
#include <tcdefs.h>
#include <qry/qry.h>

#include "qry_util.hpp"
#include "logger.hpp"

extern logical debug;

int QRY_UTIL_query_one(const char *name, std::map<std::string, std::string> &params, tag_t *result_tag) {
    int rcode = ITK_ok;
    int index = 0;
    int result_count = 0;
    tag_t query_tag = NULLTAG;
    tag_t *result_tags = nullptr;
    const auto entries = new char *[params.size() + 1];
    const auto values = new char *[params.size() + 1];

    LOGGER_ITK_GOTO(QRY_find2(name, &query_tag));
    if (query_tag == NULLTAG) {
        LOGGER_ERROR("Query not found: %s", name);
        rcode = -1;
        goto CLEANUP;
    }

    index = 0;
    for (const auto &[k, v]: params) {
        entries[index] = _strdup(k.c_str());
        values[index] = _strdup(v.c_str());
        index++;
    }

    LOGGER_ITK_GOTO(QRY_execute(query_tag, params.size(), entries, values, &result_count, &result_tags));
    if (result_count == 0) {
        LOGGER_WARN("Found no results");
        rcode = -2;
        goto CLEANUP;
    }
    if (result_count > 1) {
        LOGGER_WARN("Found multiple results: %d", result_count);
    }

    *result_tag = result_tags[0];

CLEANUP:
    for (int i = 0; i < params.size(); i++) {
        MEM_UTIL_FREE_CST(entries[i]);
        MEM_UTIL_FREE_CST(values[i]);
    }
    delete[] entries;
    delete[] values;
    MEM_UTIL_FREE_ITK(result_tags);
    return rcode;
}
