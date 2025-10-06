#pragma once

#include <cstring>
#include <string>
#include <stdexcept>
#include <memory>

namespace libS101{

class String: public std::wstring{
    public:
        using std::wstring::wstring;
        String(const std::wstring& s);
        String(const char *s);
        String(const std::string &s);

        String& operator=(const wchar_t* ws);
        String& operator=(const char* s);
        String& operator=(const std::wstring& ws);
        String& operator=(const std::string &s);

        operator const wchar_t*() const;

        String mid(size_t start, size_t length = std::wstring::npos) const;

        std::string str() const;
        const char *c_str() const;
        const wchar_t *c_wstr() const;

        template<typename... Args>
        static std::wstring fmt(const std::wstring& format, Args... args) {
            int size_s = std::swprintf(nullptr, 0, format.c_str(), args...) + 1;
            if (size_s <= 0) {
                throw std::runtime_error("Error during formatting.");
            }
            auto size = static_cast<size_t>(size_s);
            std::unique_ptr<wchar_t[]> buf(new wchar_t[size]);

            std::swprintf(buf.get(), size, format.c_str(), args...);

            return std::wstring(buf.get(), buf.get() + size - 1);
        }

        static std::wstring str2wstr(const std::string &s);
        static std::string wstr2str(const std::wstring &s);
};

std::ostream& operator<<(std::ostream& os, const libS101::String& s);

};