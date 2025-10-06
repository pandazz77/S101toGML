#pragma once
#include "Field.h"

class F_VDAT : Field
{
public:
	F_VDAT();
	virtual ~F_VDAT();

public:
	libS101::String m_dtnm;
	libS101::String m_dtid;
	int m_dtsr;
	libS101::String m_scri;

public:
	void ReadField(std::uint8_t *&buf);
	void ReadField(std::uint8_t *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();
};