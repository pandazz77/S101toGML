
#include "F_MRID.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else
#include "compat/compat_mfc.h"
#endif

F_MRID::F_MRID(void)
{
	m_name.RCNM = 0;
	m_name.RCID = 0;
	m_rver = 0;
	m_ruin = 0;
}


F_MRID::~F_MRID(void)
{
}
void F_MRID::ReadField(BYTE *&buf)
{
	m_name.RCNM = *(buf++);
	m_name.RCID = buf2uint(buf, 4);
	m_rver = buf2uint(buf, 2);
	m_ruin = *(buf++);
}
BOOL F_MRID::Save(libS101::File *file)
{
	file->write(&m_name.RCNM, 1);
	file->write(&m_name.RCID, 4);
	file->write(&m_rver, 2);
	file->write(&m_ruin, 1);

	file->write(&NonPrintableCharacter::fieldTerminator, 1);

	return TRUE;
}

int F_MRID::GetFieldLength()
{
	int len = 0;
	len += m_name.GetLength();
	len += 2;
	len += 1;
	return ++len;
}