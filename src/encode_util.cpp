#include <stdint.h>
#include <stdlib.h>

#include <base_utils/Mem.h>
#include <common/basic_definitions.h>
#include <tccore/tctype.h>

#include "encode_util.h"
#include "logger.h"
#include "mem_util.h"

static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int ENCODE_UTIL_base64(const unsigned char *input_data, const size_t input_length, size_t *output_length,
                       char **output_data)
{
    int rcode = ITK_ok;

    *output_length = 4 * ((input_length + 2) / 3);
    *output_data = (char *)MEM_alloc(*output_length + 1);
    if (*output_data == NULL)
    {
        LOGGER_ERROR("failed to allocate memory for base64 output data");
        rcode = -1;
        goto CLEANUP;
    }

    for (size_t i = 0, j = 0; i < input_length;)
    {
        const uint32_t octet_a = i < input_length ? input_data[i++] : 0;
        const uint32_t octet_b = i < input_length ? input_data[i++] : 0;
        const uint32_t octet_c = i < input_length ? input_data[i++] : 0;

        const uint32_t triple = octet_a << 16 | octet_b << 8 | octet_c;

        (*output_data)[j++] = base64_table[triple >> 18 & 0x3F];
        (*output_data)[j++] = base64_table[triple >> 12 & 0x3F];
        if (i > input_length + 1)
            (*output_data)[j++] = '=';
        else
            (*output_data)[j++] = base64_table[triple >> 6 & 0x3F];
        if (i > input_length)
            (*output_data)[j++] = '=';
        else
            (*output_data)[j++] = base64_table[triple & 0x3F];
    }

    (*output_data)[*output_length] = '\0';

CLEANUP:
    return rcode;
}

int ENCODE_UTIL_utf8_to_gbk(const char *utf8_str, char **gbk_str)
{
    int rcode = ITK_ok;

    wchar_t *wide_str = NULL;

    const int wide_len = MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, NULL, 0);
    if (wide_len == 0)
    {
        rcode = -1;
        LOGGER_ERROR("failed to convert utf8 string to wide string");
        goto CLEANUP;
    }

    wide_str = (wchar_t *)MEM_alloc(wide_len * sizeof(wchar_t));
    if (!wide_str)
    {
        rcode = -1;
        LOGGER_ERROR("failed to allocate memory for gbk string");
        goto CLEANUP;
    }

    MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, wide_str, wide_len);

    const int gbk_len = WideCharToMultiByte(CP_ACP, 0, wide_str, -1, NULL, 0, NULL, NULL);
    if (gbk_len == 0)
    {
        rcode = -1;
        LOGGER_ERROR("failed to convert wide string to gbk string");
        goto CLEANUP;
    }

    *gbk_str = (char *)MEM_alloc(gbk_len);
    if (!*gbk_str)
    {
        rcode = -1;
        LOGGER_ERROR("failed to allocate memory for gbk string");
        goto CLEANUP;
    }

    WideCharToMultiByte(CP_ACP, 0, wide_str, -1, *gbk_str, gbk_len, NULL, NULL);

CLEANUP:
    MEM_UTIL_FREE_ITK(wide_str);
    return rcode;
}

int ENCODE_UTIL_gbk_to_utf8(const char *gbk_str, char **utf8_str)
{
    int rcode = ITK_ok;

    wchar_t *wide_str = NULL;

    const int wide_len = MultiByteToWideChar(CP_ACP, 0, gbk_str, -1, NULL, 0);
    if (wide_len == 0)
    {
        rcode = -1;
        LOGGER_ERROR("failed to convert gbk string to wide string");
        goto CLEANUP;
    }

    wide_str = (wchar_t *)MEM_alloc(wide_len * sizeof(wchar_t));
    if (!wide_str)
    {
        rcode = -1;
        LOGGER_ERROR("failed to allocate memory for wide string");
        goto CLEANUP;
    }

    if (MultiByteToWideChar(CP_ACP, 0, gbk_str, -1, wide_str, wide_len) == 0)
    {
        rcode = -1;
        LOGGER_ERROR("failed to convert gbk string to wide string");
        goto CLEANUP;
    }

    const int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wide_str, -1, NULL, 0, NULL, NULL);
    if (utf8_len == 0)
    {
        rcode = -1;
        LOGGER_ERROR("failed to convert wide string to utf8 string");
        goto CLEANUP;
    }

    *utf8_str = (char *)MEM_alloc(utf8_len);
    if (!*utf8_str)
    {
        rcode = -1;
        LOGGER_ERROR("failed to allocate memory for utf8 string");
        goto CLEANUP;
    }

    if (WideCharToMultiByte(CP_UTF8, 0, wide_str, -1, *utf8_str, utf8_len, NULL, NULL) == 0)
    {
        rcode = -1;
        LOGGER_ERROR("failed to convert wide string to utf8 string");
    }

CLEANUP:
    MEM_UTIL_FREE_ITK(wide_str);
    return rcode;
}
