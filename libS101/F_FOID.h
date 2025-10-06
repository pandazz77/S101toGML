#pragma once
#include "Field.h"
#include "ObjectName.h"

class F_FOID : Field
{
public:
	F_FOID();
	virtual ~F_FOID();

public:
	ObjectName m_objName;

public:
	void ReadField(std::uint8_t *&buf);
	void ReadField(std::uint8_t *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();
};