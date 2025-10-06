#pragma once
#include "Field.h"
#include "RecordName.h"

#include <vector>

// Dataset Identification Field

class F_DSID : Field
{
public:
	F_DSID();
	virtual ~F_DSID();

public:
	RecordName m_name;
	libS101::String m_ensp; //encodingSpecification(������ ����) //S-100 Part 10a
	libS101::String m_ened; //encodingSpecificationEdition(������ ����) //1.1
	libS101::String m_prsp;	//productIdentifier(������ ����) //INT.IHO.S-101.1.0
	libS101::String m_pred; //productEdition(������ ����) //1.0
	libS101::String m_prof; //applicationProfile(������ ����) //1
	libS101::String m_dsnm; //datasetFileIdentifier
	libS101::String m_dstl; //datasetTitle
	libS101::String m_dsrd; //datasetReferenceDate
	libS101::String m_dslg; //datasetLanguage(������ ����) //EN
	libS101::String m_dsab; //datasetAbstract
	libS101::String m_dsed; //dataset Edition
	std::vector<int> m_dstc;

public:
	void ReadField(std::uint8_t *&buf);
	bool Save(libS101::File *file);
	int GetFieldLength();
};