#include <stdexcept>

#include "StringUtil.hxx"

std::wstring StringUtil::char2wstring(const char* str, UINT codePage)
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

std::wstring StringUtil::string2wstring(const std::string& str, UINT codePage)
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
