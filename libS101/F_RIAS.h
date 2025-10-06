#pragma once
#include "Field.h"
#include "RecordName.h"

#include <list>

struct RIAS;
class F_RIAS : Field
{
public:
	F_RIAS();
	virtual ~F_RIAS();

	std::list<RIAS*> m_arr;

public:
	void ReadField(std::uint8_t *&buf);
	void ReadField(std::uint8_t *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();
};