#pragma once

#include "Record.h"
#include "F_DSID.h"
#include "F_DSSI.h"
#include "F_CodeWithNumericCode.h"

#include <string>

class F_ATTR;
class DRDirectoryInfo;

// Dataset General Information Record
class R_DSGIR : Record
{
public:
	R_DSGIR();
	virtual ~R_DSGIR();

public:
	F_DSID m_dsid;
	F_DSSI m_dssi;
	F_CodeWithNumericCode *m_atcs = nullptr;
	F_CodeWithNumericCode *m_itcs = nullptr;
	F_CodeWithNumericCode *m_ftcs = nullptr;
	F_CodeWithNumericCode *m_iacs = nullptr;
	F_CodeWithNumericCode *m_facs = nullptr;
	F_CodeWithNumericCode *m_arcs = nullptr;

public:
	bool ReadRecord(DRDirectoryInfo *dir, std::uint8_t*& buf);
	bool Save(libS101::File *file);

	// ���޸� �ڵ�� �ڵ带 �������� �Լ�
	CString GetFeatureCode(int numericCode);
	CString GetInformationCode(int numericCode);
	CString GetAttributeCode(int numericCode);
	CString GetInformationAssociationCode(int numericCode);
	CString GetFeatureAssociationCode(int numericCode);
	CString GetAssociationRoleCode(int numericCode);

	//void Update(R_DSGIR* record);
};