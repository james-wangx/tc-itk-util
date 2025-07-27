#include <base_utils/Mem.h>
#include <common/basic_definitions.h>
#include <fclasses/tc_string.h>

#include "logger.h"
#include "string_util.h"

int STRING_UTIL_append(char **buffer, size_t *buf_len, const char *to_append)
{
    if (!to_append)
        return 0;

    const size_t append_len = tc_strlen(to_append);
    const size_t old_len = *buf_len;
    const size_t new_len = old_len + append_len;

    char *temp = MEM_realloc(*buffer, new_len + 1);
    if (!temp)
    {
        return -1;
    }

    *buffer = temp;

    if (old_len == 0)
    {
        (*buffer)[0] = '\0';
    }

    tc_strcat(*buffer, to_append);
    *buf_len = new_len;

    return 0;
}

int STRING_UTIL_duplicate(const char *source, char **duplicate)
{
    int rcode = ITK_ok;

    if (source == NULL)
    {
        duplicate = NULL;
        goto CLEANUP;
    }

    const size_t len = tc_strlen(source);
    *duplicate = (char *)MEM_alloc(len + 1);
    if (!*duplicate)
    {
        rcode = -1;
        LOGGER_ERROR("Failed to allocate memory for string duplication");
        goto CLEANUP;
    }
    tc_strcpy(*duplicate, source);

CLEANUP:
    return rcode;
}

int STRING_UTIL_is_empty(const char *string)
{
    return string == NULL || tc_strlen(string) == 0;
}

int STRING_UTIL_last_index_of(const char *str, const char ch, size_t *index)
{
    int rcode = ITK_ok;

    const char *p = strrchr(str, ch);
    if (p == NULL)
    {
        *index = -1;
        LOGGER_ERROR("Not found character '%c' in string: %s", ch, str);
        rcode = -1;
        goto CLEANUP;
    }

    *index = p - str;

CLEANUP:
    return rcode;
}

int STRING_UTIL_substring(const char *str, const size_t start, const size_t end, char **result)
{
    int rcode = ITK_ok;

    if (str == NULL || start >= end || end > tc_strlen(str))
    {
        LOGGER_ERROR("Invalid parameters for substring operation");
        rcode = -1;
        goto CLEANUP;
    }

    const size_t len = end - start;
    *result = (char *)MEM_alloc(len + 1);
    if (*result == NULL)
    {
        LOGGER_ERROR("Failed to allocate memory for substring");
        rcode = -1;
        goto CLEANUP;
    }

    tc_strncpy(*result, str + start, len);
    (*result)[len] = '\0';

CLEANUP:
    return rcode;
}
