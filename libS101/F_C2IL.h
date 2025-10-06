#pragma once
#include "Field.h"
#include <list>

struct IC2D;
class F_C2IL : Field
{
public:
	F_C2IL();
	virtual ~F_C2IL();

public:
	/*
	* Attribute Array
	*/
	std::list<IC2D*> m_arr;

public:
	void ReadField(std::uint8_t *&buf);
	void ReadField(std::uint8_t *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();
};

