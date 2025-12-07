#ifndef TC_ITK_UTIL_STRINGUTIL_HXX
#define TC_ITK_UTIL_STRINGUTIL_HXX

#include <string>

#include <Windows.h>
#include <unidefs.h>

class StringUtil
{
public:
    /**
     * @brief char* to std::wstring
     *
     * @param str input char*
     * @param codePage code page, default UTF-8
     * @return std::wstring result std::wstring
     */
    static std::wstring char2wstring(const char* str, UINT codePage = CP_UTF8);

    /**
     * @brief std::string to std::wstring
     *
     * @param str input std::string
     * @param codePage code page, default UTF-8
     * @return std::wstring result std::wstring
     */
    static std::wstring string2wstring(const std::string& str, UINT codePage = CP_UTF8);

    /**
     * @brief check if str starts with prefix
     *
     * @param str input std::string
     * @param prefix prefix std::string
     * @return logical true if str starts with prefix, false otherwise
     */
    static logical isStartWith(const std::string& str, const std::string& prefix);
};

#endif // TC_ITK_UTIL_STRINGUTIL_HXX
