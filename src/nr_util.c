#include "property/nr.h"

#include "../include/logger.h"
#include "nr_util.h"

extern logical debug;

int NR_UTIL_get_rule_and_case(const char *type_name, const char *prop_name,
                              tag_t *rule_tag, int *field_case) {
  int rcode = ITK_ok;

  LOGGER_ITK_GOTO(NR_ask_rule_and_case((char *)type_name, (char *)prop_name,
                                       rule_tag, field_case));

CLEANUP:
  return rcode;
}
