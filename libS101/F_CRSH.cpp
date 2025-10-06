
#include "F_CRSH.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_CRSH::F_CRSH(void)
{
	m_crix = 0;
	m_crst = 0;
	m_csty = 0;
	m_crnm = "";
	m_crsi = "";
	m_crss = 0;
	m_scri = "";
}


F_CRSH::~F_CRSH(void)
{
}
void F_CRSH::ReadField(std::uint8_t *&buf)
{
	m_crix = *(buf++);
	m_crst = *(buf++);
	m_csty = *(buf++);
	buf2charArr(m_crnm, buf);
	buf2charArr(m_crsi, buf);
	m_crss = *(buf++);
	buf2charArr(m_scri, buf);

}

bool F_CRSH::Save(libS101::File *file)
{
	file->write(&m_crix, 1);
	file->write(&m_crst, 1);
	file->write(&m_csty, 1);
	
	const char* outputString = m_crnm.c_str();
	file->write(outputString, (std::uint32_t)::strlen(outputString));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	
	const char* outputString2 = m_crsi.c_str();
	file->write(outputString2, (std::uint32_t)::strlen(outputString2));
	file->write(&NonPrintableCharacter::unitTerminator, 1);

	file->write(&m_crss, 1);

	const char* outputString3 = m_scri.c_str();
	file->write(outputString3, (std::uint32_t)::strlen(outputString3));
	file->write(&NonPrintableCharacter::unitTerminator, 1);

	file->write(&NonPrintableCharacter::fieldTerminator, 1);

	return true;
}

int F_CRSH::GetFieldLength()
{
	int len = 0;

	len += 1;
	len += 1;
	len += 1;
	len += m_crnm.length() + 1;
	len += m_crsi.length() + 1;
	len += 1;
	len += m_scri.length() + 1;
	return ++len;
}