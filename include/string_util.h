#ifndef STRING_UTIL_H
#define STRING_UTIL_H

int STRING_UTIL_append(char **buffer, size_t *buf_len, const char *to_append);

int STRING_UTIL_duplicate(const char *source, char **duplicate);

int STRING_UTIL_is_empty(const char *string);

int STRING_UTIL_last_index_of(const char *str, char ch, size_t *index);

int STRING_UTIL_substring(const char *str, size_t start, size_t end, char **result);

#endif // !STRING_UTIL_H
