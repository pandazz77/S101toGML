
#include "F_DSID.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_DSID::F_DSID(void)
{
	m_name.RCNM = 0;
	m_name.RCID = 0;
	m_ensp = "";
	m_ened = "";
	m_prsp = "";
	m_pred = "";
	m_prof = "";
	m_dsnm = "";		
	m_dstl = "";
	m_dsrd = "";
	m_dslg = "";
	m_dsab = "";
	m_dsed = "";
}


F_DSID::~F_DSID(void)
{
}
void F_DSID::ReadField(std::uint8_t *&buf)
{
	m_name.RCNM = *(buf++);
	m_name.RCID = buf2uint(buf, 4);
	buf2charArr(m_ensp, buf);
	buf2charArr(m_ened, buf);
	buf2charArr(m_prsp, buf);
	buf2charArr(m_pred, buf);
	buf2charArr(m_prof, buf);
	buf2charArr(m_dsnm, buf);			
	buf2charArr(m_dstl, buf);
	buf2charArr(m_dsrd, buf, 8);
	buf2charArr(m_dslg, buf);
	buf2charArr(m_dsab, buf);
	buf2charArr(m_dsed, buf);

	while(*buf != 0x1E)
	{
		m_dstc.push_back(*(buf++));
	}

}
bool F_DSID::Save(libS101::File *file)
{
	file->write(&m_name.RCNM, 1);
	file->write(&m_name.RCID, 4);
	const char *outputString = m_ensp.c_str();
	file->write(outputString, (std::uint32_t)::strlen(outputString));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	const char *outputString2 = m_ened.c_str();
	file->write(outputString2, (std::uint32_t)::strlen(outputString2));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	const char* outputString3 = m_prsp.c_str();
	file->write(outputString3, (std::uint32_t)::strlen(outputString3));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	const char* outputString4 = m_pred.c_str();
	file->write(outputString4, (std::uint32_t)::strlen(outputString4));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	const char* outputString5 = m_prof.c_str();
	file->write(outputString5, (std::uint32_t)::strlen(outputString5));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	const char* outputString6 = m_dsnm.c_str();
	file->write(outputString6, (std::uint32_t)::strlen(outputString6));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	const char* outputString7 = m_dstl.c_str();
	file->write(outputString7, (std::uint32_t)::strlen(outputString7));
	file->write(&NonPrintableCharacter::unitTerminator, 1);

	const char* outputString8 = m_dsrd.c_str();
	int size = (int)::strlen(outputString8);
	file->write(outputString8, (std::uint32_t)::strlen(outputString8));

	const char* outputString9 = m_dslg.c_str();
	file->write(outputString9, (std::uint32_t)::strlen(outputString9));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	const char* outputString10 = m_dsab.c_str();
	file->write(outputString10, (std::uint32_t)::strlen(outputString10));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	const char* outputString11 = m_dsed.c_str();
	file->write(outputString11, (std::uint32_t)::strlen(outputString11));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	
	for(int i=0;i < m_dstc.size();i++)
	{
		file->write(&m_dstc[i], 1);
	}
	//while(*buf != 0x1E)
	//{
	//	m_dstc.Add(*(buf++));
	//}
	file->write(&NonPrintableCharacter::fieldTerminator, 1);
	return true;
}

int F_DSID::GetFieldLength()
{
	int len = 0;
	len += m_name.GetLength();
	len += m_ensp.length()+1;
	len += m_ened.length()+1;
	len += m_prsp.length()+1;
	len += m_pred.length()+1;
	len += m_prof.length()+1;
	len += m_dsnm.length()+1;
	len += m_dstl.length()+1;
	len += m_dsrd.length();
	len += m_dslg.length()+1;
	len += m_dsab.length()+1;
	len += m_dsed.length()+1;
	len += (int)m_dstc.size();

	return ++len;
}
