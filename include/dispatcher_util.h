#ifndef DISPATCHER_UTIL_H
#define DISPATCHER_UTIL_H

#include <unidefs.h>

int DISPATCHER_UTIL_create_request(const char *provider_name, const char *service_name, int priority, int obj_count,
                                   const tag_t *primary_objs, int arg_count, const char **request_args, tag_t *request);

#endif // !DISPATCHER_UTIL_H
