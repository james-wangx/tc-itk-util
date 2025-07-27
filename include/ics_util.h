#ifndef ICS_UTIL_HPP
#define ICS_UTIL_HPP

#include <unidefs.h>

/**
 * @brief Searches for ICOs based on the provided class ID.
 * 
 * @param class_id The class ID to search for.
 * @param ico_count Pointer to an integer to store the count of ICOs found.
 * @param ico_tags Pointer to an array of tags to store the ICO tags.
 * @param ico_uids Pointer to an array of strings to store the ICO UIDs.
 * @param ico_ids Pointer to an array of strings to store the ICO IDs.
 * @param class_ids Pointer to an array of strings to store the class IDs.
 * @param wso_tags Pointer to an array of tags to store the WSO tags.
 * @param wso_uids Pointer to an array of strings to store the WSO UIDs.
 * @return int Status code of the operation.
 */
int ICS_UTIL_search_ico(const char *class_id, int *ico_count, tag_t **ico_tags, char ***ico_uids, char ***ico_ids,
                        char ***class_ids, tag_t **wso_tags, char ***wso_uids);

/**
 * @brief Retrieves the class structure associated with the given class ID.
 * 
 * @param class_id The class ID to retrieve the structure for.
 * @return int Status code of the operation.
 */
int ICS_UTIL_get_struct(const char *class_id);

/**
 * @brief Retrieves the class attributes of a given ICO tag.
 * 
 * @param ico_tag The ICO tag to retrieve attributes for.
 * @param attr_count Pointer to an integer to store the count of attributes.
 * @param attr_names Pointer to an array of strings to store the attribute names.
 * @param attr_values Pointer to an array of strings to store the attribute values.
 * @return int Status code of the operation.
 */
int ICS_UTIL_get_class_attr(tag_t ico_tag, int *attr_count, char ***attr_names, char ***attr_values);

#endif // !ICS_UTIL_HPP
