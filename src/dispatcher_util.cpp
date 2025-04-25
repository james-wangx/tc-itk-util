#include <unidefs.h>
#include <dispatcher/dispatcher_itk.h>

#include "dispatcher_util.hpp"
#include "logger.hpp"

extern logical debug;

int DISPATCHER_UTIL_create_request(const char* provider_name, const char* service_name, const int priority,
    const int obj_count, const tag_t* primary_objs, const int arg_count, const char** request_args, tag_t* request)
{
    int
        rcode = ITK_ok;

    LOGGER_ITK_GOTO(DISPATCHER_create_request(provider_name, service_name, priority, 0, 0, 0, obj_count, primary_objs,
        NULL, arg_count, request_args, "TRANSLATION", 0, NULL, NULL, request));

CLEANUP:
    return rcode;
}
