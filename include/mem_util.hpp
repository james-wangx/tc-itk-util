#ifndef MEM_UTIL_HPP
#define MEM_UTIL_HPP

#ifdef EXPORTLIBRARY
#undef EXPORTLIBRARY
#endif

#include <base_utils/Mem.h>

/**
 * @brief Macro to free memory and set pointer to nullptr.
 *
 * This macro checks if the pointer is not null before freeing it,
 * and then sets the pointer to nullptr to avoid dangling pointers.
 *
 * @param ptr Pointer to be freed.
 */
#define MEM_UTIL_FREE_ITK(ptr)  \
{                               \
    if(ptr)                     \
    {                           \
        MEM_free(ptr);          \
        ptr = nullptr;          \
    }                           \
}

/**
 * @brief Macro to free memory and set pointer to nullptr.
 *
 * This macro checks if the pointer is not null before freeing it,
 * and then sets the pointer to nullptr to avoid dangling pointers.
 *
 * @param ptr Pointer to be freed.
 */
#define MEM_UTIL_FREE_CST(ptr)  \
{                               \
    if(ptr)                     \
    {                           \
        free(ptr);              \
        ptr = nullptr;          \
    }                           \
}

#endif // !MEM_UTIL_HPP
