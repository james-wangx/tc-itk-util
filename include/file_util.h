#ifndef FILE_UTIL_H
#define FILE_UTIL_H

/**
 * @brief Safely closes a file pointer and sets it to NULL.
 *
 * This macro checks if the given file pointer is not NULL, then closes the file
 * using fclose and sets the pointer to NULL to avoid dangling pointers.
 *
 * @param file The file pointer to be closed.
 */
#define FILE_UTIL_CLOSE(file)                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((file) != NULL)                                                                                            \
        {                                                                                                              \
            fclose(file);                                                                                              \
            (file) = NULL;                                                                                             \
        }                                                                                                              \
    } while (0);

int FILE_UTIL_base64(const char *file_path, char **base64);

#endif // !FILE_UTIL_H
