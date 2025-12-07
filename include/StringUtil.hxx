#ifndef TC_ITK_UTIL_STRINGUTIL_HXX
#define TC_ITK_UTIL_STRINGUTIL_HXX

#include <string>
#include <vector>

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

    /**
     * @brief convert utf-8 string to gbk string
     *
     * @param utf8 input utf-8 string
     * @return gbk string
     */
    static std::string utf82gbk(const std::string& utf8);

    /**
     * @brief convert gbk string to utf-8 string
     *
     * @param gbk input gbk string
     * @return utf-8 string
     */
    static std::string gbk2utf8(const std::string& gbk);

    /**
     * @brief split string by delimiter
     *
     * @param str input string
     * @param delimiter delimiter string
     * @return vector of split strings
     */
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter);
};

#endif // TC_ITK_UTIL_STRINGUTIL_HXX
