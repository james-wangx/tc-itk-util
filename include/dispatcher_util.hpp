#ifndef DISPATCHER_UTIL_HPP
#define DISPATCHER_UTIL_HPP

#include <unidefs.h>

int DISPATCHER_UTIL_create_request(const char* provider_name, const char* service_name, const int priority,
    const int obj_count, const tag_t* primary_objs, const int arg_count, const char** request_args, tag_t* request);

#endif // !DISPATCHER_UTIL_HPP
