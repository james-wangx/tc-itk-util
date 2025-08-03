#include <time.h>

#include <common/basic_definitions.h>

#include "time_util.h"

#include "logger.h"

#include <base_utils/Mem.h>

int TIME_UTIL_get_formatted_time(const char *format, char **formatted_time)
{
    int rcode = ITK_ok;

    const time_t now = time(NULL);
    struct tm tm_info;

    if (!localtime_s(&tm_info, &now))
    {
        LOGGER_ERROR("localtime_s() failed");
        rcode = -1;
        goto CLEANUP;
    }

    const size_t size = 128;
    *formatted_time = (char *)MEM_alloc(size);
    strftime(*formatted_time, size, format, &tm_info);

CLEANUP:
    return rcode;
}
