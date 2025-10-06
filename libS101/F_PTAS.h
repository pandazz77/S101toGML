#pragma once

#include "Field.h"
#include "RecordName.h"

#include <vector>

struct PTAS;
class F_PTAS : Field
{
public:
	F_PTAS();
	virtual ~F_PTAS();

public:
	std::vector<PTAS*> m_arr;

public:
	void ReadField(std::uint8_t *&buf);
	void ReadField(std::uint8_t *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();
};