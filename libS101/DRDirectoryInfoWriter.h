#pragma once

#include "DRDirectoryInfo.h"
#include "NonPrintableCharacter.h"
#include "DRReader.h"

#include "File.h"

class DRDirectoryInfoWriter : public DRDirectoryInfo
{
public:
	DRDirectoryInfoWriter();
	DRDirectoryInfoWriter(int directoryCount);
	virtual ~DRDirectoryInfoWriter();

public:
	bool WriteDRDirectory(libS101::File* file, const DRReader dr);
	void CheckLength(DRReader *dr);
};