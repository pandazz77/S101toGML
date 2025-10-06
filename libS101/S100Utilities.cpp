
#include "S100Utilities.h"

#include <string>
#include <cstring>
#include <filesystem>
#include <cctype>
#include <cstdio>
#include <cstdarg>

int S100Utilities::GetScaleByLevel(int level)
{
	return 0;
}

void S100Utilities::TRACE(const char* format, ...){
	va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    fputc('\n', stderr);
    va_end(args);
}

void S100Utilities::OutputDebugString(const wchar_t* s) {
	if (s) std::fwprintf(stderr, L"%ls", s);
}

std::wstring S100Utilities::compat_utf8_to_wstring(const char* s) {
	if (!s) return std::wstring();
	std::wstring out; out.reserve(std::strlen(s));
	for (const unsigned char* p = (const unsigned char*)s; *p; ++p) out.push_back((wchar_t)*p);
	return out;
}