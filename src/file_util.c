#include <stdio.h>

#include <base_utils/Mem.h>
#include <common/basic_definitions.h>

#include "encode_util.h"
#include "file_util.h"
#include "logger.h"

int FILE_UTIL_base64(const char *filename, char **base64_string)
{
    int rcode = ITK_ok;

    unsigned char *buffer = NULL;

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        LOGGER_ERROR("Open file failed.")
        goto CLEANUP;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    buffer = (unsigned char *)MEM_alloc(filesize);
    if (!buffer)
    {
        LOGGER_ERROR("Read file failed.");
        goto CLEANUP;
    }

    fread(buffer, 1, filesize, file);

    size_t base64_len = 0;
    ENCODE_UTIL_base64(buffer, filesize, &base64_len, base64_string);

CLEANUP:
    MEM_UTIL_FREE_ITK(buffer);
    FILE_UTIL_CLOSE(file);
    return rcode;
}
