#ifndef NR_UTIL_HPP
#define NR_UTIL_HPP

#include <unidefs.h>

/**
 * @brief Retrieves the rule and case for a given type and property name.
 * 
 * @param type_name The name of the type.
 * @param prop_name The name of the property.
 * @param rule_tag Pointer to a tag to store the rule tag.
 * @param field_case Pointer to an integer to store the field case.
 * @return int Status code of the operation.
 */
int NR_UTIL_get_rule_and_case(const char* type_name, const char* prop_name, tag_t* rule_tag, int* field_case);

#endif // !NR_UTIL_HPP
