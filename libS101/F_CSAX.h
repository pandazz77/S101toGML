#pragma once
#include "Field.h"

struct CSAX;
class F_CSAX : Field
{
public:
	F_CSAX();
	virtual ~F_CSAX();

public:
	std::vector<CSAX*> m_arr;

public:
	void ReadField(std::uint8_t *&buf);
	void ReadField(std::uint8_t *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();
};