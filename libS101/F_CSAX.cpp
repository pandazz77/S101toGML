
#include "F_CSAX.h"
#include "CSAX.h"
#include "NonPrintableCharacter.h"

F_CSAX::F_CSAX(void)
{
}


F_CSAX::~F_CSAX(void)
{
	for(CSAX *csax: m_arr)
		delete csax;
}
void F_CSAX::ReadField(std::uint8_t *&buf)
{
	while(*buf != 0x1E){
		CSAX *csax = new CSAX();

		csax->m_axty = *(buf++);
		csax->m_axum = *(buf++);
			
		m_arr.push_back(csax);
	}
}

void F_CSAX::ReadField(std::uint8_t *&buf, int loopCnt)
{
	for(int i = 0;i < loopCnt; i++)
	{
		CSAX *csax = new CSAX();

		csax->m_axty = *(buf++);
		csax->m_axum = *(buf++);
			
		m_arr.push_back(csax);
	}
}
bool F_CSAX::Save(libS101::File *file)
{
	int len = 0;

	for(CSAX *csax: m_arr){
		file->write(&csax->m_axty, 1);
		file->write(&csax->m_axum, 1);
	}

	file->write(&NonPrintableCharacter::fieldTerminator, 1);

	return true;
}

int F_CSAX::GetFieldLength()
{
	int len = 0;
	
	for(CSAX *csax: m_arr){
		len += 1;
		len += 1;
	}

	return ++len;
}