
#include "F_FRID.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_FRID::F_FRID(void)
{
	m_name.RCNM = 0;
	m_name.RCID = 0;
	m_nftc = 0;
	m_rver = 0;
	m_ruin = 0;
}


F_FRID::~F_FRID(void)
{
}
void F_FRID::ReadField(std::uint8_t *&buf)
{
	m_name.RCNM = *(buf++);
	m_name.RCID = buf2uint(buf, 4);
	m_nftc = buf2uint(buf, 2);
	m_rver = buf2uint(buf, 2);
	m_ruin = *(buf++);
}
bool F_FRID::Save(libS101::File *file)
{
	file->write(&m_name.RCNM, 1);
	file->write(&m_name.RCID, 4);
	file->write(&m_nftc, 2);
	file->write(&m_rver, 2);
	file->write(&m_ruin, 1);

	file->write(&NonPrintableCharacter::fieldTerminator, 1);
	return true;
}
int F_FRID::GetFieldLength()
{
	int len = 0;
	len += m_name.GetLength();
	len += 2;
	len += 2;
	len += 1;
	return ++len;
}