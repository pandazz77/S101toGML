#pragma once
#include "Field.h"
#include "RecordName.h"

class F_FRID : Field
{
public:
	F_FRID();
	virtual ~F_FRID();

public:
	RecordName m_name;
	/*
	* Numeric Feature Type Code
	* Format		: b12
	* Description	: A valid feature type code as defined in the FTCS field of the Dataset General Information Record
	*/
	int m_nftc;
	int m_rver;
	int m_ruin;

public:
	void ReadField(std::uint8_t *&buf);
	void ReadField(std::uint8_t *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();
};