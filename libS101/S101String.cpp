#include "S101String.h"
#include <locale>
#include <codecvt>
#include <cstdio>
#include <memory>


namespace libS101{

String::String(const char *s){
    *this = str2wstr(s);
}

String::String(const std::string &s){
    *this = str2wstr(s);
}

String::String(const std::wstring& s) : std::wstring(s){

}

String& String::operator=(const wchar_t* ws) {
    *this = ws ? ws : L"";
    return *this;
}

String& String::operator=(const char* s){
    *this = str2wstr(s);
    return *this;
}

String& String::operator=(const std::wstring& ws) {
    *this = String(ws);
    return *this;
}

String& String::operator=(const std::string &s){
    *this = str2wstr(s);
    return *this;
}

String::operator const wchar_t*() const {
    return this->c_wstr();
}

String String::mid(size_t start, size_t length) const{
    if (start >= this->length()) {
        return String();
    }

    return String(this->substr(start, length));
}


std::string String::str() const{
    return wstr2str(*this);
}

const char *String::c_str() const{
    static std::string temp;
    temp = wstr2str(*this);
    return temp.c_str();
}

const wchar_t *String::c_wstr() const{
    return std::wstring::c_str();
}

std::wstring String::str2wstr(const std::string& s){
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(s);
}

std::string String::wstr2str(const std::wstring &ws){
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(ws);
}

std::ostream& operator<<(std::ostream& os, const libS101::String& s) {
    return os << s.str();
}

};