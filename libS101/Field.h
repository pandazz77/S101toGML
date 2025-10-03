#pragma once
#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else
#include "compat/compat_mfc.h"
#endif

class Field
{
public:
	Field();
	virtual ~Field();

public:
	virtual void ReadField(BYTE *&buf) {};
	virtual BOOL Save(CFile *file) { return TRUE; };
	virtual int GetFieldLength() { return 0; };
};