#ifndef QRY_UTIL_HPP
#define QRY_UTIL_HPP

#include <map>
#include <string>
#include <unidefs.h>

int QRY_UTIL_query_one(const char *name, std::map<std::string, std::string> &params, tag_t *result_tag);

#endif // !QRY_UTIL_HPP
