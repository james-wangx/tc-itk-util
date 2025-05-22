/**
 * @brief Log util, log with info, warn, debug, error.
 *
 * TODO: Log with time, eg: 2021/05/24-08:40:06.218 UTC
 * TODO: Use logging framework (optional)
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#ifdef EXPORTLIBRARY
#undef EXPORTLIBRARY
#endif

#include <tc/emh.h>
#include <tc/tc_startup.h>
#include <tc/tc_util.h>

#include "mem_util.hpp"

/**
 * @brief Log info message
 *
 * This macro logs an info message using the specified format and arguments.
 * It logs the message to both the console and the system log.
 *
 * @param fmt The format string for the log message.
 * @param ... The arguments for the format string.
 */
#define LOGGER_INFO(fmt, ...)                           \
{                                                       \
    TC_printf("INFO  - " fmt "\n", ##__VA_ARGS__);      \
    TC_write_syslog("INFO  - " fmt "\n", ##__VA_ARGS__);\
}

/**
 * @brief Log warning message
 *
 * This macro logs a warning message using the specified format and arguments.
 * It logs the message to both the console and the system log.
 *
 * @param fmt The format string for the log message.
 * @param ... The arguments for the format string.
 */
#define LOGGER_WARN(fmt, ...)                           \
{                                                       \
    TC_printf("WARN  - " fmt "\n", ##__VA_ARGS__);      \
    TC_write_syslog("WARN  - " fmt "\n", ##__VA_ARGS__);\
}

/**
 * @brief Log debug message
 *
 * This macro logs a debug message using the specified format and arguments.
 * It logs the message to both the console and the system log if the debug flag is set.
 *
 * @param fmt The format string for the log message.
 * @param ... The arguments for the format string.
 */
#define LOGGER_DEBUG(fmt, ...)                              \
{                                                           \
    if (debug)                                              \
    {                                                       \
        TC_printf("DEBUG - " fmt "\n", ##__VA_ARGS__);      \
        TC_write_syslog("DEBUG - " fmt "\n", ##__VA_ARGS__);\
    }                                                       \
}

/**
 * @brief Log error message
 *
 * This macro logs an error message using the specified format and arguments.
 * It logs the message to both the console and the system log.
 *
 * @param fmt The format string for the log message.
 * @param ... The arguments for the format string.
 */
#define LOGGER_ERROR(fmt, ...)                          \
{                                                       \
    TC_printf("ERROR - " fmt "\n", ##__VA_ARGS__);      \
    TC_write_syslog("ERROR - " fmt "\n", ##__VA_ARGS__);\
}

/**
 * @brief Log itk call and goto CLEANUP after log error message
 *
 * This macro logs a debug message before calling the specified ITK function.
 * If the function returns a non-ITK_ok code, it retrieves the error message,
 * logs it as an error, frees the allocated memory for the error message, and
 * then jumps to the CLEANUP label.
 *
 * @param func The ITK function to be called.
 */
#define LOGGER_ITK_GOTO(func)                                               \
{                                                                           \
    LOGGER_DEBUG("Call %s; at %s:%d", #func, __FILE__, __LINE__);           \
    if((rcode = (func)) != ITK_ok)                                          \
    {                                                                       \
        char* error = nullptr;                                              \
        EMH_ask_error_text(rcode, &error);                                  \
        LOGGER_ERROR("Found error code: %d, message: %s\n", rcode, error);  \
        MEM_UTIL_FREE_ITK(error);                                           \
        goto CLEANUP;                                                       \
    }                                                                       \
}

/**
 * @brief Log itk call and log error message without goto CLEANUP
 *
 * This macro logs a debug message before calling the specified ITK function.
 * If the function returns a non-ITK_ok code, it retrieves the error message,
 * logs it as an error, and frees the allocated memory for the error message.
 *
 * @param func The ITK function to be called.
 */
#define LOGGER_ITK_PASS(func)                                               \
{                                                                           \
    LOGGER_DEBUG("Call %s; at %s:%d", #func, __FILE__, __LINE__);           \
    if((rcode = (func)) != ITK_ok)                                          \
    {                                                                       \
        char* error = nullptr;                                              \
        EMH_ask_error_text(rcode, &error);                                  \
        LOGGER_ERROR("Found error code: %d, message: %s\n", rcode, error);  \
        MEM_UTIL_FREE_ITK(error);                                           \
    }                                                                       \
}

/**
 * @brief Log custom call and goto CLEANUP without log error message
 *
 * This macro logs a debug message before calling the specified custom function.
 * If the function returns a non-ITK_ok code, it jumps to the CLEANUP label.
 * The custom function should call an ITK function inside.
 *
 * @param func The custom function to be called.
 */
#define LOGGER_CST_GOTO(func)                                       \
{                                                                   \
    LOGGER_DEBUG("Call %s; at %s:%d", #func, __FILE__, __LINE__);   \
    if((rcode = (func)) != ITK_ok)                                  \
    {                                                               \
        goto CLEANUP;                                               \
    }                                                               \
}

/**
 * @brief Log custom call without goto CLEANUP
 *
 * This macro logs a debug message before calling the specified custom function.
 * It assigns the return code of the function to the variable rcode.
 * The custom function should call an ITK function inside.
 *
 * @param func The custom function to be called.
 */
#define LOGGER_CST_PASS(func)                                       \
{                                                                   \
    LOGGER_DEBUG("Call %s; at %s:%d", #func, __FILE__, __LINE__);   \
    rcode = func;                                                   \
}

/**
 * @brief Log register call and goto CLEANUP after log error message
 *
 * This macro logs an info message before calling the specified register function.
 * If the function returns ITK_ok, it logs a success message. Otherwise, it retrieves
 * the error message, logs it as an error, frees the allocated memory for the error
 * message, and then jumps to the CLEANUP label.
 *
 * @param func The register function to be called.
 * @param reg_name The name of the register being logged.
 */
#define LOGGER_REG_GOTO(func, reg_name)                                     \
{                                                                           \
    LOGGER_INFO("Call %s; at %s:%d", #func, __FILE__, __LINE__);            \
    if ((rcode = func) == ITK_ok)                                           \
    {                                                                       \
        LOGGER_INFO("Registering " reg_name ", completed!");                \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        char* error = nullptr;                                              \
        EMH_ask_error_text(rcode, &error);                                  \
        LOGGER_ERROR("Registering " reg_name ", failed!");                  \
        LOGGER_ERROR("Found error code: %d, message: %s\n", rcode, error);  \
        MEM_UTIL_FREE_ITK(error);                                           \
        goto CLEANUP;                                                       \
    }                                                                       \
}

/**
 * @brief Log register call and error message without goto CLEANUP
 *
 * This macro logs an info message before calling the specified register function.
 * If the function returns ITK_ok, it logs a success message. Otherwise, it retrieves
 * the error message, logs it as an error, and frees the allocated memory for the error
 * message.
 *
 * @param func The register function to be called.
 * @param reg_name The name of the register being logged.
 */
#define LOGGER_REG_PASS(func, reg_name)                                     \
{                                                                           \
    LOGGER_INFO("Call %s; at %s:%d", #func, __FILE__, __LINE__);            \
    if ((rcode = func) == ITK_ok)                                           \
    {                                                                       \
        LOGGER_INFO("Registering " reg_name ", completed!");                \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        char* error = nullptr;                                              \
        EMH_ask_error_text(rcode, &error);                                  \
        LOGGER_ERROR("Registering " reg_name ", failed!");                  \
        LOGGER_ERROR("Found error code: %d, message: %s\n", rcode, error);  \
        MEM_UTIL_FREE_ITK(error);                                           \
    }                                                                       \
}

#endif // !LOGGER_HPP
