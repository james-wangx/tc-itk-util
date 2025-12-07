#include <stdexcept>

#include "StringUtil.hxx"

std::wstring StringUtil::char2wstring(const char* str, const UINT codePage)
{
    if (!str)
        return L"";

    const int len = MultiByteToWideChar(codePage, 0, str, -1, nullptr, 0);
    if (len == 0)
    {
        throw std::runtime_error("MultiByteToWideChar failed");
    }

    std::wstring ws(len - 1, L'\0');
    MultiByteToWideChar(codePage, 0, str, -1, &ws[0], len);

    return ws;
}

std::wstring StringUtil::string2wstring(const std::string& str, const UINT codePage)
{
    return char2wstring(str.c_str(), codePage);
}

logical StringUtil::isStartWith(const std::string& str, const std::string& prefix)
{
    if (str.size() < prefix.size())
    {
        return false;
    }

    return str.compare(0, prefix.size(), prefix) == 0;
}

std::string StringUtil::utf82gbk(const std::string& utf8)
{
    // UTF-8 -> UTF-16
    const int wLen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
    std::wstring wStr(wLen, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &wStr[0], wLen);

    // UTF-16 -> GBK
    const int len = WideCharToMultiByte(CP_ACP, 0, wStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string str(len, '\0');
    WideCharToMultiByte(CP_ACP, 0, wStr.c_str(), -1, &str[0], len, nullptr, nullptr);

    return str;
}

std::string StringUtil::gbk2utf8(const std::string& gbk)
{
    // GBK -> UTF-16
    const int wLen = MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, nullptr, 0);
    std::wstring wStr(wLen, L'\0');
    MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, &wStr[0], wLen);

    // UTF-16 -> UTF-8
    const int len = WideCharToMultiByte(CP_UTF8, 0, wStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string str(len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wStr.c_str(), -1, &str[0], len, nullptr, nullptr);

    return str;
}
