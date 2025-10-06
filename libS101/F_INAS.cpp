
#include "F_INAS.h"
#include "ATTR.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_INAS::F_INAS()
{
	m_name.RCNM = 0;
	m_name.RCID = 0;
	m_niac = 0;
	m_narc = 0;
	m_iuin = 0;	
}

F_INAS::~F_INAS()
{
	for(ATTR *attr: m_arr)
		delete attr;
}

int F_INAS::GetSize()
{
	return 10;
}

void F_INAS::ReadField(std::uint8_t *&buf)
{
	m_name.RCNM = *(buf++);
	m_name.RCID = buf2uint(buf, 4);
	m_niac = buf2uint(buf, 2);
	m_narc = buf2uint(buf, 2);
	m_iuin = *(buf++);

	while (*buf != 0x1E)
	{
		ATTR *attr = new ATTR();
		attr->m_natc = buf2uint(buf, 2);
		attr->m_atix = buf2uint(buf, 2);
		attr->m_paix = buf2uint(buf, 2);
		attr->m_atin = *(buf++);
		buf2charArr(attr->m_atvl, buf);

		m_arr.push_back(attr);
	}
}

void F_INAS::ReadField(std::uint8_t *&buf, int loopCnt)
{
	m_name.RCNM = *(buf++);
	m_name.RCID = buf2uint(buf, 4);
	m_niac = buf2uint(buf, 2);
	m_narc = buf2uint(buf, 2);
	m_iuin = *(buf++);

	for (int i = 0; i < loopCnt; i++)
	{
		ATTR *attr = new ATTR();
		attr->m_natc = buf2uint(buf, 2);
		attr->m_atix = buf2uint(buf, 2);
		attr->m_paix = buf2uint(buf, 2);
		attr->m_atin = *(buf++);
		buf2charArr(attr->m_atvl, buf);

		m_arr.push_back(attr);
	}
}
bool F_INAS::Save(libS101::File *file)
{
	file->write(&m_name.RCNM, 1);
	file->write(&m_name.RCID, 4);
	file->write(&m_niac, 2);
	file->write(&m_narc, 2);
	file->write(&m_iuin, 1);

	for(ATTR *attr: m_arr){
		file->write(&attr->m_natc, 2);
		file->write(&attr->m_atix, 2);
		file->write(&attr->m_paix, 2);
		file->write(&attr->m_atin, 1);
		const char *outputString = attr->m_atvl.c_str();
		file->write(outputString, (std::uint32_t)::strlen(outputString));
		file->write(&NonPrintableCharacter::unitTerminator, 1);
	}
	
	file->write(&NonPrintableCharacter::fieldTerminator, 1);

	return true;
}
int F_INAS::GetFieldLength()
{
	int len = 0;
	len += F_INAS::GetSize();

	for(ATTR *attr: m_arr){
		len += ATTR::GetOffsetToATVL();
		const char* outputString = attr->m_atvl.c_str();
		len += (int)::strlen(outputString) + 1;
	}
	
	return ++len;
}
