
#include "F_CUCO.h"
#include "CUCO.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_CUCO::F_CUCO(void)
{
}


F_CUCO::~F_CUCO(void)
{
	for (auto itor = m_arr.begin(); itor != m_arr.end(); itor++)
	{
		CUCO *cuco = *itor;
		delete cuco;
	}
}

void F_CUCO::ReadField(BYTE *&buf)
{
	while(*buf != 0x1E){
		CUCO *cuco = new CUCO();
		cuco->m_name.RCNM = *(buf++);
		cuco->m_name.RCID = buf2uint(buf, 4);
		cuco->m_ornt = *(buf++);

		m_arr.push_back(cuco);
	}
}

void F_CUCO::ReadField(BYTE *&buf, int loopCnt)
{
	for(int i = 0; i < loopCnt; i++){
		CUCO *cuco = new CUCO();
		cuco->m_name.RCNM = *(buf++);
		cuco->m_name.RCID = buf2uint(buf, 4);
		cuco->m_ornt = *(buf++);

		m_arr.push_back(cuco);
	}
}
bool F_CUCO::Save(libS101::File *file)
{
	for (auto itor = m_arr.begin(); itor != m_arr.end(); itor++)
	{
		CUCO *cuco = *itor;
		
		file->write(&cuco->m_name.RCNM, 1);
		file->write(&cuco->m_name.RCID, 4);
		file->write(&cuco->m_ornt, 1);
	}
	file->write(&NonPrintableCharacter::fieldTerminator, 1);

	return true;
}

int F_CUCO::GetFieldLength()
{
	int len = 0;
	
	for (auto itor = m_arr.begin(); itor != m_arr.end(); itor++)
	{
		CUCO *cuco = *itor;
		len += cuco->m_name.GetLength();
		len += 1;
	}
	return ++len;
}