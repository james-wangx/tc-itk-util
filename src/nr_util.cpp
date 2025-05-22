#include "property/nr.h"

#include "nr_util.hpp"
#include "../include/logger.hpp"

extern logical debug;

int NR_UTIL_get_rule_and_case(const char *type_name, const char *prop_name, tag_t *rule_tag, int *field_case) {
    int rcode = ITK_ok;

    // Cast away const-ness to match the function signature
    LOGGER_ITK_GOTO(
        NR_ask_rule_and_case(const_cast<char *>(type_name), const_cast<char *>(prop_name), rule_tag, field_case));

CLEANUP:
    return rcode;
}
