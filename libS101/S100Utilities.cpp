
#include "S100Utilities.h"

#include <string>
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