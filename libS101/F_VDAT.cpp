#include "pch.h"
#include "F_VDAT.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_VDAT::F_VDAT()
{
	m_dtnm = "";
	m_dtid = "";
	m_dtsr = 0;
	m_scri = "";
}

F_VDAT::~F_VDAT()
{
}

void F_VDAT::ReadField(BYTE *&buf)
{
	buf2charArr(m_dtnm, buf);
	buf2charArr(m_dtid, buf);
	m_dtsr = *(buf++);
	buf2charArr(m_scri, buf);
}

BOOL F_VDAT::Save(libS101::File *file)
{
	CT2CA outputString(m_dtnm, CP_UTF8);
	file->write(outputString, (UINT)::strlen(outputString));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	
	CT2CA outputString2(m_dtid, CP_UTF8);
	file->write(outputString2, (UINT)::strlen(outputString2));
	file->write(&NonPrintableCharacter::unitTerminator, 1);

	file->write(&m_dtsr, 1);
		
	CT2CA outputString3(m_scri, CP_UTF8);
	file->write(outputString3, (UINT)::strlen(outputString3));
	file->write(&NonPrintableCharacter::unitTerminator, 1);

	file->write(&NonPrintableCharacter::fieldTerminator, 1);
	return TRUE;
}

int F_VDAT::GetFieldLength()
{
	int len = 0;
	
	len += m_dtnm.GetLength()+1;
	len += m_dtid.GetLength()+1;
	len++;
	len += m_scri.GetLength()+1;
	
	return ++len;
}