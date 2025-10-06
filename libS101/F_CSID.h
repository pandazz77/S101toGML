#pragma once
#include "Field.h"
#include "RecordName.h"
class F_CSID : Field
{
public:
	F_CSID();
	virtual ~F_CSID();

public:
	RecordName m_name;
	int m_ncrc;

public:
	void ReadField(std::uint8_t *&buf);
	void ReadField(std::uint8_t *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();
};