#pragma once

#include <string>

namespace S100Utilities
{
	int GetScaleByLevel(int level);
	void TRACE(const char* format, ...);
	void OutputDebugString(const wchar_t* s);
	std::wstring compat_utf8_to_wstring(const char* s);
};
