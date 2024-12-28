#ifndef MEM_UTIL_HPP
#define MEM_UTIL_HPP

#include <base_utils/Mem.h>

/**
 * @brief Safely frees a memory pointer and sets it to NULL.
 *
 * This macro checks if the given pointer is not NULL, then frees the memory
 * using MEM_free and sets the pointer to NULL to avoid dangling pointers.
 *
 * @param ptr The pointer to be freed.
 */
#define MEM_UTIL_FREE(ptr)  \
{                           \
    if(ptr)                 \
    {                       \
        MEM_free(ptr);      \
        ptr = NULL;         \
    }                       \
}                           \

#endif // !MEM_UTIL_HPP
