#pragma once

#include "compat_mfc.h"

class DRDirectoryInfo;
class Record
{
public:
	Record();
	virtual ~Record();

public:
	virtual BOOL ReadRecord(DRDirectoryInfo* dir, BYTE*& buf) {	return TRUE; };
};