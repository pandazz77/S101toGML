#pragma once

#ifdef _WIN32
#include <afxext.h>
#include <windows.h>
#else

#include <cstdint>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <list>

#define _T(x) L##x
#define TEXT(x) L##x

#define CP_UTF8 65001


#endif // _WIN32


