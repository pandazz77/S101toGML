
#include "F_FASC.h"
#include "FASC.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_FASC::F_FASC(void)
{
}


F_FASC::~F_FASC(void)
{
	for (auto itor = m_arr.begin(); itor != m_arr.end(); itor++)
		delete *itor;
}
void F_FASC::ReadField(std::uint8_t *&buf)
{
	m_name.RCNM = *(buf++);
	m_name.RCID = buf2uint(buf, 4);
	m_nfac = buf2uint(buf, 2);
	m_narc = buf2uint(buf, 2);
	m_faui = *(buf++);

	//while (*buf != 0x1E){
	//	FASC *cont = new FASC();
	//	
	//	cont->m_natc = buf2uint(buf, 2);
	//	cont->m_atix = buf2uint(buf, 2);
	//	cont->m_paix = buf2uint(buf, 2);
	//	cont->m_atin = *(buf++);
	//	buf2charArr(cont->m_atvl, buf);
	//	
	//	m_arr.push_back(cont);
	//}
}

void F_FASC::ReadField(std::uint8_t *&buf, int loopCnt)
{
	m_name.RCNM = *(buf++);
	m_name.RCID = buf2uint(buf, 4);
	m_nfac = buf2uint(buf, 2);
	m_narc = buf2uint(buf, 2);
	m_faui = *(buf++);

	//for (int i = 0; i < loopCnt; i++)
	//{
	//	FASC *cont = new FASC();

	//	cont->m_natc = buf2uint(buf, 2);
	//	cont->m_atix = buf2uint(buf, 2);
	//	cont->m_paix = buf2uint(buf, 2);
	//	cont->m_atin = *(buf++);
	//	buf2charArr(cont->m_atvl, buf);

	//	m_arr.push_back(cont);
	//}
}
bool F_FASC::Save(libS101::File *file)
{
	//POSITION pos = m_arr.GetHeadPosition();

	file->write(&m_name.RCNM, 1);
	file->write(&m_name.RCID, 4);
	file->write(&m_nfac, 2);
	file->write(&m_narc, 2);
	file->write(&m_faui, 1);
	for (auto itor = m_arr.begin(); itor != m_arr.end(); itor++)
	{
		FASC *cont = *itor;

		file->write(&cont->m_natc, 2);
		file->write(&cont->m_atix, 2);
		file->write(&cont->m_paix, 2);
		file->write(&cont->m_atin, 1);
		CT2CA outputString(cont->m_atvl, CP_UTF8);
		file->write(outputString, (std::uint32_t)::strlen(outputString));
		file->write(&NonPrintableCharacter::unitTerminator, 1);
	}
	file->write(&NonPrintableCharacter::fieldTerminator, 1);

	return true;
}

int F_FASC::GetFieldLength()
{
	int len = 0;

	len += 10;

	for (auto itor = m_arr.begin(); itor != m_arr.end(); itor++)
		//while(pos != NULL)
	{
		//ATTR *attr = m_arr.GetNext(pos);
		FASC *cont = *itor;
		len += FASC::GetSize();
		CT2CA outputString(cont->m_atvl, CP_UTF8);
		len += (int)::strlen(outputString) + 1;
	}
		
	return ++len;
}