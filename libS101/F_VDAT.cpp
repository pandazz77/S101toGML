
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

void F_VDAT::ReadField(std::uint8_t *&buf)
{
	buf2charArr(m_dtnm, buf);
	buf2charArr(m_dtid, buf);
	m_dtsr = *(buf++);
	buf2charArr(m_scri, buf);
}

bool F_VDAT::Save(libS101::File *file)
{
	const char* outputString = m_dtnm.c_str();
	file->write(outputString, (std::uint32_t)::strlen(outputString));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	
	const char* outputString2 = m_dtid.c_str();
	file->write(outputString2, (std::uint32_t)::strlen(outputString2));
	file->write(&NonPrintableCharacter::unitTerminator, 1);

	file->write(&m_dtsr, 1);
		
	const char* outputString3 = m_scri.c_str();
	file->write(outputString3, (std::uint32_t)::strlen(outputString3));
	file->write(&NonPrintableCharacter::unitTerminator, 1);

	file->write(&NonPrintableCharacter::fieldTerminator, 1);
	return true;
}

int F_VDAT::GetFieldLength()
{
	int len = 0;
	
	len += m_dtnm.length()+1;
	len += m_dtid.length()+1;
	len++;
	len += m_scri.length()+1;
	
	return ++len;
}