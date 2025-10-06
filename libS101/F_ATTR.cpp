
#include "F_ATTR.h"
#include "ATTR.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_ATTR::F_ATTR()
{
}


F_ATTR::~F_ATTR()
{
	for (auto itor = m_arr.begin(); itor != m_arr.end(); itor++)
	{
		delete* itor;
	}
}

void F_ATTR::ReadField(std::uint8_t *&buf)
{
	while (*buf != 0x1E)
	{
		ATTR *attr = new ATTR();
		attr->m_natc = buf2uint(buf, 2);
		attr->m_atix = buf2uint(buf, 2);
		attr->m_paix = buf2uint(buf, 2);
		attr->m_atin = *(buf++);
		buf2charArr(attr->m_atvl, buf);

//		m_arr.AddTail(attr);
		m_arr.push_back(attr);
	}
}

void F_ATTR::ReadField(std::uint8_t *&buf, int loopCnt)
{
	for(int i = 0; i < loopCnt; i++)
	{
		ATTR *attr = new ATTR();
		attr->m_natc = buf2uint(buf, 2);
		attr->m_atix = buf2uint(buf, 2);
		attr->m_paix = buf2uint(buf, 2);
		attr->m_atin = *(buf++);
		buf2charArr(attr->m_atvl, buf);

		//m_arr.AddTail(attr);
		m_arr.push_back(attr);
	}
}

bool F_ATTR::Save(libS101::File *file)
{
	//POSITION pos = m_arr.GetHeadPosition();

	for (auto itor = m_arr.begin(); itor != m_arr.end(); itor++)
	//while(pos != NULL)
	{
		//ATTR *attr = m_arr.GetNext(pos);
		ATTR *attr = *itor;

		file->write(&attr->m_natc, 2);
		file->write(&attr->m_atix, 2);
		file->write(&attr->m_paix, 2);
		file->write(&attr->m_atin, 1);
		const char* outputString = attr->m_atvl.c_str();
		file->write(outputString, (std::uint32_t)::strlen(outputString));
		file->write(&NonPrintableCharacter::unitTerminator, 1);
	}
	file->write(&NonPrintableCharacter::fieldTerminator, 1);

	return true;
}

int F_ATTR::GetFieldLength()
{
	unsigned len = 0;

	for (auto i = m_arr.begin(); i != m_arr.end(); i++)
	{
		auto attr = *i;

		len += ATTR::GetOffsetToATVL();

		const char *outputString = attr->m_atvl.c_str();

		len += (unsigned int)::strlen(outputString) + 1;
	}
	return ++len;
}