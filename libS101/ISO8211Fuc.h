#pragma once
#include <string>

#include "S101String.h"

void buf2charArr(libS101::String& dest, std::uint8_t*& buf);
void buf2charArr(std::wstring& dest, std::uint8_t*& buf);
void buf2charArr(libS101::String& dest, std::uint8_t*& buf, int len);
void buf2charArr(std::wstring& dest, std::uint8_t*& buf, int len);
std::uint32_t buf2uint(std::uint8_t*& buf, int len);
double buf2double(std::uint8_t*& buf, int size);
std::uint32_t buf2int(std::uint8_t*& buf, int len);
std::uint32_t atoi(std::uint8_t*& buf, int len);


int asNumeric( wchar_t wch );
wchar_t const* const digitTables[] =
{
    L"0123456789",
    L"\u0660\u0661\u0662\u0663\u0664\u0665\u0666\u0667\u0668\u0669",
    // ...
};
