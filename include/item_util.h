#ifndef ITEM_UTIL_H
#define ITEM_UTIL_H

#include <unidefs.h>

/**
 * @brief Get the latest released revision of an item with a specific status name.
 *
 * This function retrieves the latest released revision of an item that has a specific
 * status name. It searches through all revisions of the item and checks their release
 * status list for a match with the provided status name.
 *
 * @param item_tag The tag of the item to search for revisions.
 * @param status_name The name of the status to match against.
 * @param revision_tag A pointer to store the tag of the found revision.
 * @return int Returns ITK_ok on success, or an error code on failure.
 */
int ITEM_UTIL_get_latest_released_revision(tag_t item_tag, const char *status_name, tag_t *revision_tag);

int ITEM_UTIL_get_prev_no_base_rev(tag_t rev_tag, tag_t *prev_no_base_rev_tag);

#endif // !ITEM_UTIL_H
