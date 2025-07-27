#include <io.h>

#include <ae/dataset.h>
#include <ae/datasettype.h>
#include <sa/tcfile.h>
#include <tccore/aom.h>
#include <tccore/grm.h>
#include <tccore/tctype.h>

#include "dataset_util.h"
#include "logger.h"

extern logical debug;

int DATASET_UTIL_find_by_type(const tag_t rev_tag, const char *relation_type_name, const char *dataset_type_name,
                              tag_t *dataset_tag)
{
    int rcode = ITK_ok, secondary_object_count = 0;

    tag_t relation_type = NULLTAG, secondary_object_tag = NULLTAG, secondary_object_type = NULLTAG;

    tag_t *secondary_object_tags = NULL;

    char *secondary_object_type_name = NULL;

    LOGGER_ITK_GOTO(GRM_find_relation_type(relation_type_name, &relation_type));
    LOGGER_ITK_GOTO(
        GRM_list_secondary_objects_only(rev_tag, relation_type, &secondary_object_count, &secondary_object_tags));
    for (int i = 0; i < secondary_object_count; i++)
    {
        secondary_object_tag = secondary_object_tags[i];
        LOGGER_ITK_GOTO(TCTYPE_ask_object_type(secondary_object_tag, &secondary_object_type));
        LOGGER_ITK_GOTO(TCTYPE_ask_class_name2(secondary_object_type, &secondary_object_type_name));
        if (tc_strcmp(secondary_object_type_name, dataset_type_name))
        {
            *dataset_tag = secondary_object_tag;
        }
    }

CLEANUP:
    return rcode;
}

int DATASET_UTIL_is_ref_exist(const tag_t dataset_tag, logical *is_ref_exist)
{
    int rcode = ITK_ok, ref_count = 0;

    *is_ref_exist = false;
    LOGGER_ITK_GOTO(AE_ask_dataset_ref_count(dataset_tag, &ref_count));
    if (ref_count > 0)
    {
        *is_ref_exist = true;
    }

CLEANUP:
    return rcode;
}

int DATASET_UTIL_download(const tag_t dataset_tag, const char *file_path)
{
    int rcode = ITK_ok;

    char *ref_name = NULL;

    AE_reference_type_t ref_type;

    tag_t ref_tag = NULLTAG;

    if (_access(file_path, 0) == 0)
    {
        remove(file_path);
    }

    LOGGER_ITK_GOTO(AE_find_dataset_named_ref2(dataset_tag, 0, &ref_name, &ref_type, &ref_tag));
    LOGGER_ITK_GOTO(IMF_export_file(ref_tag, file_path));

CLEANUP:
    MEM_UTIL_FREE_ITK(ref_name);
    return rcode;
}

int DATASET_UTIL_create(const tag_t rev_tag, const char *dataset_type_name, const char *dataset_name,
                        const char *relation_type_name, tag_t *dataset_tag)
{
    int rcode = ITK_ok;

    tag_t dataset_type = NULLTAG, relation_type = NULLTAG, relation_tag = NULLTAG;

    LOGGER_ITK_GOTO(AE_find_datasettype2(dataset_type_name, &dataset_type));
    LOGGER_ITK_GOTO(AE_create_dataset_with_id(dataset_type, dataset_name, "", NULL, NULL, dataset_tag));
    LOGGER_ITK_GOTO(AOM_save(*dataset_tag));
    LOGGER_ITK_GOTO(AOM_lock(rev_tag));
    LOGGER_ITK_GOTO(GRM_find_relation_type(relation_type_name, &relation_type));
    LOGGER_ITK_GOTO(GRM_create_relation(rev_tag, *dataset_tag, relation_type, NULLTAG, &relation_tag));
    LOGGER_ITK_GOTO(GRM_save_relation(relation_tag));
    AOM_unlock(relation_tag);
    AOM_unlock(rev_tag);

CLEANUP:
    return rcode;
}

int DATASET_UTIL_upload(const tag_t dataset_tag, const char *file_path, const int file_type, const char *reference_name)
{
    int rcode = ITK_ok;

    tag_t file_tag = NULLTAG;

    IMF_file_t file_descriptor;

    LOGGER_ITK_GOTO(IMF_import_file(file_path, NULL, file_type, &file_tag, &file_descriptor));
    LOGGER_ITK_GOTO(IMF_close_file(file_descriptor));
    LOGGER_ITK_GOTO(AOM_save(file_tag));
    AOM_unlock(file_tag);
    LOGGER_ITK_GOTO(AOM_lock(dataset_tag));
    LOGGER_ITK_GOTO(AE_add_dataset_named_ref2(dataset_tag, reference_name, AE_PART_OF, file_tag));
    LOGGER_ITK_GOTO(AE_save_myself(dataset_tag));
    LOGGER_ITK_GOTO(AOM_refresh(dataset_tag, false));
    AOM_unlock(dataset_tag);

CLEANUP:
    return rcode;
}
