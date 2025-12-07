// ReSharper disable CppEntityAssignedButNoRead
// ReSharper disable CppTooWideScope
#include <base_utils/IFail.hxx>
#include <base_utils/ScopedSmPtr.hxx>
#include <base_utils/TcResultStatus.hxx>
#include <mld/logging/Logger.hxx>

#include <pom/pom/pom.h>
#include <ps/ps.h>
#include <qry/qry.h>
#include <tc/preferences.h>
#include <tccore/aom_prop.h>
#include <tccore/grm.h>
#include <tccore/releasestatus.h>
#include <tccore/tctype.h>

#include "TcUtil.hxx"

extern Teamcenter::Logging::Logger* logger;

void TcUtil::addReleaseStatus(const std::vector<tag_t>& workspaceObjects, const std::string& statusType,
                              const logical retainReleasedDate)
{
    ResultStatus ok;
    std::vector<tag_t> valid;

    for (const tag_t& workspaceObject : workspaceObjects)
    {
        // Append or not
        logical isExist = false;
        std::vector<tag_t> statuses = askReleasedStatus(workspaceObject);
        for (const tag_t& status : statuses)
        {
            std::string tempStatusType = askValueString(status, "name");
            if (statusType == tempStatusType)
            {
                isExist = true;
                break;
            }
        }
        if (isExist)
        {
            std::string objectName = askValueString(workspaceObject, "object_name");
            LOGGER_DEBUG("Workspace object %s already has %s, skip", objectName.c_str(), statusType.c_str());
            continue;
        }
        valid.push_back(workspaceObject);
    }

    if (!valid.empty())
    {
        tag_t releaseStatus = NULLTAG;
        LOGGER_ITK(RELSTAT_create_release_status(statusType.c_str(), &releaseStatus));
        LOGGER_ITK(RELSTAT_add_release_status(releaseStatus, valid.size(), valid.data(), retainReleasedDate));
    }
}

std::map<std::string, std::string> TcUtil::askArgumentNamedValue(TC_argument_list_t* arguments)
{
    ResultStatus ok;
    std::map<std::string, std::string> result;

    const int argCount = TC_number_of_arguments(arguments);
    TC_init_argument_list(arguments);
    for (int i = 0; i < argCount; i++)
    {
        const char* argument = TC_next_argument(arguments);
        Teamcenter::scoped_smptr<char> argNamePtr;
        Teamcenter::scoped_smptr<char> argValuePtr;

        LOGGER_ITK(ITK_ask_argument_named_value(argument, &argNamePtr, &argValuePtr));
        result[argNamePtr.getString()] = argValuePtr.getString();
    }

    return result;
}

std::vector<std::string> TcUtil::askPrefValues(const std::string& prefName)
{
    ResultStatus ok;
    int prefCount = 0;
    Teamcenter::scoped_smptr<char*> prefValuesPtr;
    std::vector<std::string> result;

    LOGGER_ITK(PREF_ask_char_values(prefName.c_str(), &prefCount, &prefValuesPtr));

    result.reserve(prefCount);
    for (int i = 0; i < prefCount; ++i)
    {
        result.emplace_back(prefValuesPtr.getString()[i]);
    }

    return result;
}

std::vector<tag_t> TcUtil::askReleasedStatus(const tag_t workspaceObject)
{
    ResultStatus ok;
    int num = 0;
    Teamcenter::scoped_smptr<tag_t> statuses;

    LOGGER_ITK(WSOM_ask_release_status_list(workspaceObject, &num, &statuses));

    std::vector<tag_t> result;
    result.assign(statuses.get(), statuses.get() + num);

    return result;
}

date_t TcUtil::askValueDate(tag_t object, const std::string& propName)
{
    ResultStatus ok;
    date_t propValue;

    LOGGER_ITK(AOM_ask_value_date(object, propName.c_str(), &propValue));

    return propValue;
}

std::string TcUtil::askValueString(const tag_t object, const std::string& propName)
{
    ResultStatus ok;
    Teamcenter::scoped_smptr<char> propValue;

    LOGGER_ITK(AOM_ask_value_string(object, propName.c_str(), &propValue));

    return propValue.get();
}

std::vector<std::string> TcUtil::askValueStrings(const tag_t object, const std::string& propName)
{
    ResultStatus ok;
    int num = 0;
    Teamcenter::scoped_smptr<char*> values;

    LOGGER_ITK(AOM_ask_value_strings(object, propName.c_str(), &num, &values));
    std::vector<std::string> result;
    result.reserve(num);
    for (int i = 0; i < num; ++i)
    {
        result.emplace_back(values[i]);
    }

    return result;
}

std::vector<tag_t> TcUtil::askValueTags(const tag_t object, const std::string& propName)
{
    ResultStatus ok;
    int num = 0;
    Teamcenter::scoped_smptr<tag_t> values;
    std::vector<tag_t> result;

    LOGGER_ITK(AOM_ask_value_tags(object, propName.c_str(), &num, &values));
    result.reserve(num);
    for (int i = 0; i < num; ++i)
    {
        result.emplace_back(values[i]);
    }

    return result;
}

bool TcUtil::checkType(const tag_t object, const std::string& typeName)
{
    ResultStatus ok;
    Teamcenter::scoped_smptr<char> objectType;

    LOGGER_ITK(AOM_ask_value_string(object, "object_type", &objectType));

    return typeName == objectType.get();
}

void TcUtil::deleteReleaseStatus(const std::vector<tag_t>& workspaceObjects, const std::string& statusType)
{
    ResultStatus ok;

    tag_t attr = NULLTAG;
    LOGGER_ITK(POM_attr_id_of_attr("release_status_list", "WorkspaceObject", &attr));

    for (const tag_t& workspaceObject : workspaceObjects)
    {
        std::vector<tag_t> statuses = askReleasedStatus(workspaceObject);
        for (int i = 0; i < statuses.size(); i++)
        {
            std::string tempStatusType = askValueString(statuses[i], "name");
            if (statusType != tempStatusType)
            {
                continue;
            }
            LOGGER_ITK(POM_refresh_instances_any_class(1, &workspaceObject, POM_modify_lock));
            LOGGER_ITK(POM_remove_from_attr(1, &workspaceObject, attr, i, 1));
            LOGGER_ITK(POM_save_instances(1, &workspaceObject, true));
        }
    }
}

std::vector<tag_t> TcUtil::findRelatedTagsByType(const tag_t primaryObject, const std::string& relationTypeName)
{
    ResultStatus ok;
    int count = 0;
    tag_t relationType = NULL_TAG;
    Teamcenter::scoped_smptr<tag_t> secondaryObjects;

    LOGGER_ITK(GRM_find_relation_type(relationTypeName.c_str(), &relationType));
    LOGGER_ITK(GRM_list_secondary_objects_only(primaryObject, relationType, &count, &secondaryObjects));

    std::vector<tag_t> result;
    result.reserve(count);
    for (int i = 0; i < count; i++)
    {
        result.emplace_back(secondaryObjects.get()[i]);
    }

    return result;
}

logical TcUtil::isTypeOf(const tag_t object, const std::string& parentTypeName)
{
    ResultStatus ok;
    logical result = false;
    tag_t typeTag = NULLTAG;

    LOGGER_ITK(TCTYPE_ask_object_type(object, &typeTag));
    LOGGER_ITK(TCTYPE_is_type_of_as_str(typeTag, parentTypeName.c_str(), &result));

    return result;
}

tag_t TcUtil::queryOne(const std::string& queryName, const std::vector<std::string>& entries,
                       const std::vector<std::string>& values)
{
    ResultStatus ok;
    int resultNum = 0;
    tag_t queryTag = NULLTAG;
    Teamcenter::scoped_smptr<tag_t> resultTags;

    LOGGER_ITK(QRY_find2(queryName.c_str(), &queryTag));
    if (queryTag == NULLTAG)
    {
        throw IFail(0, "Not found query name");
    }

    std::vector<char*> entriesCstrs;
    entriesCstrs.reserve(entries.size());
    for (auto& s : entries)
    {
        entriesCstrs.push_back(const_cast<char*>(s.c_str()));
    }

    std::vector<char*> valuesCstrs;
    valuesCstrs.reserve(values.size());
    for (auto& s : values)
    {
        valuesCstrs.push_back(const_cast<char*>(s.c_str()));
    }
    LOGGER_ITK(QRY_execute(queryTag, entries.size(), entriesCstrs.data(), valuesCstrs.data(), &resultNum, &resultTags));

    if (resultNum == 0)
    {
        return NULLTAG;
    }

    return resultTags.get()[0];
}

std::vector<tag_t> TcUtil::where_used_top(const tag_t target, const std::string& typeName)
{
    ResultStatus ok;

    int parentNum = 0;
    Teamcenter::scoped_smptr<int> levelNum;
    Teamcenter::scoped_smptr<tag_t> parents;
    std::vector<tag_t> result;

    LOGGER_ITK(PS_where_used_all(target, PS_where_used_all_levels, &parentNum, &levelNum, &parents));
    for (int i = 0; i < parentNum; i++)
    {
        // Top level
        if (i == parentNum - 1 || levelNum[i] >= levelNum[i + 1])
        {
            if (typeName.empty())
            {
                result.emplace_back(parents[i]);
            }
            else
            {
                if (checkType(parents[i], typeName))
                {
                    result.emplace_back(parents[i]);
                }
            }
        }
    }

    return result;
}
