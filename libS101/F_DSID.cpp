
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
	CT2CA outputString(m_ensp, CP_UTF8);
	file->write(outputString, (std::uint32_t)::strlen(outputString));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	CT2CA outputString2(m_ened, CP_UTF8);
	file->write(outputString2, (std::uint32_t)::strlen(outputString2));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	CT2CA outputString3(m_prsp, CP_UTF8);
	file->write(outputString3, (std::uint32_t)::strlen(outputString3));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	CT2CA outputString4(m_pred, CP_UTF8);
	file->write(outputString4, (std::uint32_t)::strlen(outputString4));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	CT2CA outputString5(m_prof, CP_UTF8);
	file->write(outputString5, (std::uint32_t)::strlen(outputString5));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	CT2CA outputString6(m_dsnm, CP_UTF8);
	file->write(outputString6, (std::uint32_t)::strlen(outputString6));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	CT2CA outputString7(m_dstl, CP_UTF8);
	file->write(outputString7, (std::uint32_t)::strlen(outputString7));
	file->write(&NonPrintableCharacter::unitTerminator, 1);

	CT2CA outputString8(m_dsrd, CP_UTF8);
	int size = (int)::strlen(outputString8);
	file->write(outputString8, (std::uint32_t)::strlen(outputString8));

	CT2CA outputString9(m_dslg, CP_UTF8);
	file->write(outputString9, (std::uint32_t)::strlen(outputString9));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	CT2CA outputString10(m_dsab, CP_UTF8);
	file->write(outputString10, (std::uint32_t)::strlen(outputString10));
	file->write(&NonPrintableCharacter::unitTerminator, 1);
	CT2CA outputString11(m_dsed, CP_UTF8);
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
	len += m_ensp.GetLength()+1;
	len += m_ened.GetLength()+1;
	len += m_prsp.GetLength()+1;
	len += m_pred.GetLength()+1;
	len += m_prof.GetLength()+1;
	len += m_dsnm.GetLength()+1;
	len += m_dstl.GetLength()+1;
	len += m_dsrd.GetLength();
	len += m_dslg.GetLength()+1;
	len += m_dsab.GetLength()+1;
	len += m_dsed.GetLength()+1;
	len += (int)m_dstc.size();

	return ++len;
}
