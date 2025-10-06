#pragma once
#include "Field.h"
#include "RecordName.h"

#include <list>
struct SPAS;
class F_SPAS : Field
{
public:
	F_SPAS();
	virtual ~F_SPAS();

public:
	std::list<SPAS*> m_arr;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();
};