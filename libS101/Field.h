#pragma once
#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else
#include "compat/compat_mfc.h"
#endif

#include "File.h"

class Field
{
public:
	Field();
	virtual ~Field();

public:
	virtual void ReadField(BYTE *&buf) {};
	virtual bool Save(libS101::File *file) { return true; };
	virtual int GetFieldLength() { return 0; };
};