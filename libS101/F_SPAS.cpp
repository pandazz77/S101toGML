
#include "F_SPAS.h"
#include "SPAS.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_SPAS::F_SPAS(void)
{
}


F_SPAS::~F_SPAS(void)
{
	for (auto itor = m_arr.begin(); itor != m_arr.end(); itor++)
	{
		delete *itor;
	}
}
void F_SPAS::ReadField(BYTE *&buf)
{
	while(*buf != 0x1E)
	{
		SPAS* spas = new SPAS();
		spas->m_name.RCNM = *(buf++);
		spas->m_name.RCID = buf2uint(buf, 4);
		spas->m_ornt = *(buf++);
		spas->m_smin = buf2uint(buf, 4);
		spas->m_smax = buf2uint(buf, 4);
		spas->m_saui = *(buf++);

		m_arr.push_back(spas);
	}
}
void F_SPAS::ReadField(BYTE *&buf, int loopCnt)
{
	for(int i = 0; i < loopCnt; i++)
	{
		SPAS* spas = new SPAS();
		spas->m_name.RCNM = *(buf++);
		spas->m_name.RCID = buf2uint(buf, 4);
		spas->m_ornt = *(buf++);
		spas->m_smin = buf2uint(buf, 4);
		spas->m_smax = buf2uint(buf, 4);
		spas->m_saui = *(buf++);

		m_arr.push_back(spas);
	}
}
bool F_SPAS::Save(libS101::File *file)
{
	for (auto itor = m_arr.begin(); itor != m_arr.end(); itor++)
	{
		SPAS *spas = *itor;
		
		file->write(&spas->m_name.RCNM, 1);
		file->write(&spas->m_name.RCID, 4);
		file->write(&spas->m_ornt, 1);
		file->write(&spas->m_smin, 4);
		file->write(&spas->m_smax, 4);
		file->write(&spas->m_saui, 1);
	}
	file->write(&NonPrintableCharacter::fieldTerminator, 1);
	return true;
}

int F_SPAS::GetFieldLength()
{
	int len = 0;

	for (auto itor = m_arr.begin(); itor != m_arr.end(); itor++)
	{
		SPAS *spas = *itor;
		len += SPAS::GetSize();
	}
	return ++len;
}