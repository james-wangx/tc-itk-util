#ifndef DATASET_UTIL_H
#define DATASET_UTIL_H

#include <unidefs.h>

int DATASET_UTIL_find_by_type(const tag_t rev_tag, const char* relation_type_name, const char* dataset_type_name, tag_t* dataset_tag);

int DATASET_UTIL_is_ref_exist(const tag_t dataset_tag, logical* is_ref_exist);

int DATASET_UTIL_download(const tag_t dataset_tag, const char* file_path);

int DATASET_UTIL_create(const tag_t rev_tag, const char* dataset_type_name, const char* dataset_name, const char* relation_type_name, tag_t* dataset_tag);

int DATASET_UTIL_upload(const tag_t dataset_tag, const char* file_path, const int file_type, const char* reference_name);

#endif // !DATASET_UTIL_H
