#pragma once

#include <string>

namespace S100Utilities
{
	int GetScaleByLevel(int level);
	void TRACE(const char* format, ...);
	
	inline void OutputDebugString(const wchar_t* s) {
		if (s) std::fwprintf(stderr, L"%ls", s);
	}
};
