
#include "F_CCOC.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_CCOC::F_CCOC()
{
}

F_CCOC::~F_CCOC()
{
}

int F_CCOC::GetSize()
{
	return 5;
}

void F_CCOC::ReadField(std::uint8_t *&buf)
{
	m_ccui = buf2uint(buf, 1);
	m_ccix = buf2uint(buf, 2);
	m_ncco = buf2uint(buf, 2);
}

bool F_CCOC::Save(libS101::File *file)
{
	file->write(&m_ccui, 1);
	file->write(&m_ccix, 2);
	file->write(&m_ncco, 2);

	file->write(&NonPrintableCharacter::fieldTerminator, 1);
	return true;
}

int F_CCOC::GetFieldLength()
{
	int len = 0;
	len += 1;
	len += 2;
	len += 2;
	return ++len;
}