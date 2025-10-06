
#include "F_C3IT.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_C3IT::F_C3IT()
{
}

F_C3IT::~F_C3IT()
{
}

int F_C3IT::GetSize()
{
	return 13;
}

void F_C3IT::ReadField(std::uint8_t *&buf)
{
	m_vcid = *(buf++);
	m_ycoo = buf2int(buf, 4);
	m_xcoo = buf2int(buf, 4);
	m_zcoo = buf2int(buf, 4);
}

bool F_C3IT::Save(libS101::File *file)
{
	file->write(&m_vcid, 1);
	file->write(&m_ycoo, 4);
	file->write(&m_xcoo, 4);
	file->write(&m_zcoo, 4);

	file->write(&NonPrintableCharacter::fieldTerminator, 1);
	
	return true;
}
int F_C3IT::GetFieldLength()
{
	int len = 0;
	len += F_C3IT::GetSize();
	return ++len;
}
