#pragma once
#include "Field.h"

#include <list>
struct CUCO;
class F_CUCO : Field
{
public:
	F_CUCO();
	virtual ~F_CUCO();
	
public:
	std::list<CUCO*> m_arr;

public:
	void ReadField(std::uint8_t *&buf);
	void ReadField(std::uint8_t *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();
};