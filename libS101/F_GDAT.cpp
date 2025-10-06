
#include "F_GDAT.h"
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"

F_GDAT::F_GDAT()
{	/*
	* Datum Name
	* A
	* Name of the geodetic datum
	*/
	m_dtnm = L"";
	/*
	* Ellipsoid Name
	* A
	* Name of the ellipsoid
	*/
	m_elnm = L"";
	/*
	* Ellipsoid semi major axis
	* b48
	* Semi major axis of the ellipsoid in metre
	*/
	m_esma = 0;
	/*
	* Ellipsoid second parameter type
	* b11
	* {1} - Semi minor axis in metres
	* {2} - Inverse Flattening
	*/
	m_espt = 1;
	/*
	* Ellipsoid second parameter
	* b48
	* The second defining parameter of the ellipsoid
	*/
	m_espm = 0;
	/*
	* Central Meridian Name
	* A
	* Name of the central meridian
	*/
	m_cmnm = L"";
	/*
	* Central Meridian Greenwich Longitude
	* b48
	* Greenwich longitude of the central meridian in degrees
	*/
	m_cmgl = 0;
}


F_GDAT::~F_GDAT()
{
}

void F_GDAT::ReadField(std::uint8_t *&buf)
{
	buf2charArr(m_dtnm, buf);
	buf2charArr(m_elnm, buf);
	m_esma = buf2double(buf, 8);
	m_espt = buf2uint(buf, 1);
	m_espm = buf2double(buf, 8);
	buf2charArr(m_cmnm, buf);
	m_cmgl = buf2double(buf, 8);
}

bool F_GDAT::Save(libS101::File *file)
{
	const char *outputString = m_dtnm.c_str();
	file->write(outputString, (std::uint32_t)::strlen(outputString));
	file->write(&NonPrintableCharacter::unitTerminator, 1);

	const char * outputString2 = m_elnm.c_str();
	file->write(outputString2, (std::uint32_t)::strlen(outputString2));
	file->write(&NonPrintableCharacter::unitTerminator, 1);

	file->write(&m_esma, 8);
	file->write(&m_espt, 1);
	file->write(&m_espm, 8);

	const char * outputString3 = m_cmnm.c_str();
	file->write(outputString3, (std::uint32_t)::strlen(outputString3));
	file->write(&NonPrintableCharacter::unitTerminator, 1);

	file->write(&m_cmgl, 8);

	file->write(&NonPrintableCharacter::fieldTerminator, 1);
	return true;
}

int F_GDAT::GetFieldLength()
{
	int len = 0;

	len += m_dtnm.length() + 1;
	len += m_elnm.length() + 1;
	len += 8;
	len += 1;
	len += 8;
	len += m_cmnm.length() + 1;
	len += 8;

	return ++len;
}