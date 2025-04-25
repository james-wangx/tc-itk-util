#ifndef FILE_UTIL_HPP
#define FILE_UTIL_HPP

#include <stdio.h>

/**
 * @brief Safely closes a file pointer and sets it to NULL.
 *
 * This macro checks if the given file pointer is not NULL, then closes the file
 * using fclose and sets the pointer to NULL to avoid dangling pointers.
 *
 * @param file The file pointer to be closed.
 */
#define FILE_UTIL_CLOSE(file)   \
{                               \
    if(file)                    \
    {                           \
        fclose(file);           \
        file = NULL;            \
    }                           \
}                               \

#endif // !FILE_UTIL_HPP
