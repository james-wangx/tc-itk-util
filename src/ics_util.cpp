#include <ics/ics.h>
#include <ics/ics2.h>
#include <ics/ics_defines.h>
#include <fclasses/tc_string.h>

#include "../include/ics_util.hpp"
#include "mem_util.hpp"
#include "logger.hpp"

extern logical debug;

int ICS_UTIL_search_ico(const char* class_id, int* ico_count, tag_t** ico_tags, char*** ico_uids, char*** ico_ids,
    char*** class_ids, tag_t** wso_tags, char*** wso_uids)
{
    int
        rcode = ITK_ok,
        expr_count = 1,
        options = ICS_SEARCH_THIS_CLASS_ONLY;

    int
        attr_ids[] = { ICS_UNCT_CID };

    char
        ** attr_expr = NULL;

    attr_expr = (char**)MEM_alloc(expr_count * sizeof(char*));
    attr_expr[0] = (char*)MEM_alloc(tc_strlen(class_id) + 1);
    tc_strcpy(attr_expr[0], class_id);

    LOGGER_ITK_GOTO(ICS_ico_search(expr_count, attr_ids, attr_expr, options, ico_count, ico_tags, ico_uids, ico_ids,
        class_ids, wso_tags, wso_uids));

CLEANUP:
    MEM_UTIL_FREE(attr_expr);
    return rcode;
}

int ICS_UTIL_get_struct(const char* class_id)
{
    int
        rcode = ITK_ok,
        child_count = 0;

    char
        ** child_class_ids = NULL;

    LOGGER_ITK_GOTO(ICS_class_ask_children(class_id, ICS_CHILD_type_class, &child_count, &child_class_ids));
    if (child_count == 0)
    {
        LOGGER_INFO("Found bottom");
    }
    else
    {
        LOGGER_INFO("Found %d children of %s", child_count, class_id);
        for (int i = 0; i < child_count; i++)
        {
            LOGGER_INFO("Found child: %s", child_class_ids[i]);
            LOGGER_ITK_GOTO(ICS_UTIL_get_struct(child_class_ids[i]));
        }
    }

CLEANUP:
    MEM_UTIL_FREE(child_class_ids);
    return rcode;
}

int ICS_UTIL_get_class_attr(const tag_t ico_tag, int* attr_count, char*** attr_names, char*** attr_values)
{
    int
        rcode = ITK_ok;

    int
        * attr_ids = NULL,
        * attr_val_counts = NULL;

    char
        *** attr_val_values = NULL;

    LOGGER_ITK_GOTO(ICS_ico_ask_attributes(ico_tag, attr_count, &attr_ids, &attr_val_counts, &attr_val_values));

    *attr_names = (char**)MEM_alloc(*attr_count * sizeof(char*));
    *attr_values = (char**)MEM_alloc(*attr_count * sizeof(char*));
    for (int i = 0; i < *attr_count; i++)
    {
        int value_length = 0;
        LOGGER_ITK_GOTO(ICS_attribute_ask_property(attr_ids[i], "NAME", &(*attr_names)[i]));
        // "v1,v2,v3,v4,v5"
        for (int j = 0; j < attr_val_counts[i]; j++)
        {
            value_length += tc_strlen(attr_val_values[i][j]);
        }
        (*attr_values)[i] = (char*)MEM_alloc(value_length + attr_val_counts[i]);
        for (int j = 0; j < attr_val_counts[i]; j++)
        {
            if (j == 0)
            {
                tc_strcpy((*attr_values)[i], attr_val_values[i][j]);
            }
            else
            {
                tc_strcat((*attr_values)[i], ",");
                tc_strcat((*attr_values)[i], attr_val_values[i][j]);
            }
        }
    }

CLEANUP:
    MEM_UTIL_FREE(attr_ids);
    MEM_UTIL_FREE(attr_val_counts);
    MEM_UTIL_FREE(attr_val_values);
    return rcode;
}
