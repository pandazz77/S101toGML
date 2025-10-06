#pragma once

#include "Record.h"
#include "F_IRID.h"

#include <list>

class F_ATTR;
class F_INAS;
class ATTR;
class DRDirectoryInfo;
// Information Record
class R_InformationRecord : Record
{
public:
	R_InformationRecord();
	virtual ~R_InformationRecord();

public:
	// 000
	F_IRID m_irid;
	std::list<F_ATTR*> m_attr;
	std::list<F_INAS*> m_inas;

public:
	bool ReadRecord(DRDirectoryInfo *dir, BYTE*& buf);
	bool Save(libS101::File *file);

	int GetRCID();
	int GetAttributeIndex(ATTR* value);
	int GetAssociationCount();
	int GetInformationAssociationCount();
	int GetNumericCode();
};