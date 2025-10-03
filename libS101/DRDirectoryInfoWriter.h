#pragma once

#include "DRDirectoryInfo.h"
#include "NonPrintableCharacter.h"
#include "DRReader.h"

#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else
#include "compat/compat_mfc.h"
#endif
class DRDirectoryInfoWriter : public DRDirectoryInfo
{
public:
	DRDirectoryInfoWriter();
	DRDirectoryInfoWriter(int directoryCount);
	virtual ~DRDirectoryInfoWriter();

public:
	BOOL WriteDRDirectory(CFile* file, const DRReader dr);
	void CheckLength(DRReader *dr);
};