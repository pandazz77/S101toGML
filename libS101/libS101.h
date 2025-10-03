#pragma once

#ifdef _WIN32
#  ifdef LIBS101_EXPORTS
#    define LIBS101_API __declspec(dllexport) 
#  else
#    define LIBS101_API __declspec(dllimport) 
#  endif
#else
#  define LIBS101_API
#endif