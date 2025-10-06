#pragma once
#include "Field.h"
#include "RecordName.h"

class F_MRID : Field
{
public:
	F_MRID();
	virtual ~F_MRID();

public:
	RecordName m_name;
	int m_rver;
	int m_ruin;

public:
	void ReadField(std::uint8_t *&buf);
	bool Save(libS101::File *file);
	int GetFieldLength();
};

