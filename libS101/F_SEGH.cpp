
#include "F_SEGH.h"
#include "NonPrintableCharacter.h"

F_SEGH::F_SEGH(void)
{
	m_intp = 0;
	m_circ = 0;
	m_ycoo = 0;
	m_xcoo = 0;
	m_dist = 0;
	m_disu = 0;
	m_sbrg = 0;
	m_angl = 0;
}

F_SEGH::~F_SEGH(void)
{
}
void F_SEGH::ReadField(std::uint8_t *&buf)
{
	m_intp = *(buf++);
	//m_circ = *(buf++);
	//m_ycoo = buf2double(buf, 8);
	//m_xcoo = buf2double(buf, 8);
	//m_dist = buf2double(buf, 8);
	//m_disu = *(buf++);
	//m_sbrg = buf2double(buf, 8);
	//m_angl = buf2double(buf, 8);
}
bool F_SEGH::Save(libS101::File *file)
{
	file->write(&m_intp, 1);
	//file->write(&m_circ, 1);
	//file->write(&m_ycoo, 8);
	//file->write(&m_xcoo, 8);
	//file->write(&m_dist, 8);
	//file->write(&m_disu, 1);
	//file->write(&m_sbrg, 8);
	//file->write(&m_angl, 8);
	file->write(&NonPrintableCharacter::fieldTerminator, 1);
	return true;
}
int F_SEGH::GetFieldLength()
{
	int len = 0;
	len += 1;
	return ++len;
}