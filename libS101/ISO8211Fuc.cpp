
#include "ISO8211Fuc.h"
#include "NonPrintableCharacter.h"
#include "S100Utilities.h"

#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else
#include "compat/compat_mfc.h"
#endif
#include <cmath>
#ifdef _WIN32
#include <atlbase.h>
#include <atlconv.h>
#endif
#include <algorithm>
#include <bitset> // Convert the 32-bit binary encoding into hexadecimal



std::uint8_t tBYTEArr[1024];
void buf2charArr(CString &dest, std::uint8_t*& buf)
{
	;
	int i = 0;
	int endLoc = 0;
	
	while (buf[endLoc] != NonPrintableCharacter::unitTerminator)
	{
		endLoc++;
	}
	for(i = 0; i < endLoc; i++)
	{
		tBYTEArr[i] = *(buf++);
	}
	tBYTEArr[i] = NULL;
	dest = S100Utilities::compat_utf8_to_wstring((char*)tBYTEArr);
	buf++;
}

void buf2charArr(std::wstring &dest, std::uint8_t*& buf)
{
	//;
	int i = 0;
	int endLoc = 0;
	
	while(buf[endLoc] != 0x1F)
	{
		endLoc++;
	}
	for(i = 0; i < endLoc; i++)
	{
		tBYTEArr[i] = *(buf++);
		//dest.AppendChar(*(buf++));
	}
	tBYTEArr[i] = NULL;
	dest = S100Utilities::compat_utf8_to_wstring((char*)tBYTEArr);
	buf++;
}

void buf2charArr(CString &dest, std::uint8_t*& buf, int len)
{
	for(int i = 0; i < len; i++)
	{
		dest.AppendChar(*(buf++));
	}
}


void buf2charArr(std::wstring &dest, std::uint8_t*& buf, int len)
{
//	;
	int i = 0;
	for(i = 0; i < len; i++)
	{
		tBYTEArr[i] = *(buf++);
		//dest.AppendChar(*(buf++));
	}
	tBYTEArr[i] = NULL;
	dest = S100Utilities::compat_utf8_to_wstring((char*)tBYTEArr);
}

std::uint32_t buf2uint(std::uint8_t*& buf, int size)
{
	std::uint32_t ret = 0;
	//for(int i = 0; i < size; i++)
	//{
	//	ret |= ((*(buf++))<<(8*i))&(0xff<<(8*i));
	//	//ret = ret << 8 | *buf;
	//	//buf++;
	//}
	std::memcpy(&ret,buf,size);

	buf += size;
	return ret;
}

std::uint32_t buf2int(std::uint8_t*& buf, int size)
{
	std::uint32_t ret = 0;
	//for(int i = 0; i < size; i++)
	//{
	//	ret |= ((*(buf++))<<(8*i))&(0xff<<(8*i));
	//	//ret = ret << 8 | *buf;
	//	//buf++;
	//}
	std::memcpy(&ret,buf,size);

	buf += size;
	return ret;
}

char TEMP_BUF256[1024];
std::uint32_t atoi(std::uint8_t*& buf, int len)
{
	std::uint32_t ret = 0;
	for(int i=0; i< len;i++)
	{
		ret = ret * 10 + *(buf++) - '0';
	}
	return ret;
}

double buf2double(std::uint8_t*& buf, int size)
{
	double ret = 0;
	std::memcpy(&ret,buf,8);
	buf += 8;
	return ret;
	//std::string Binary;

	//for (int i = 0; i < size; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		char c = buf[0] & (0x01 < (7 - j));
	//		if (c & 0xFF)
	//		{
	//			Binary.append("1");
	//		}
	//		else
	//		{
	//			Binary.append("0");
	//		}
	//	}
	//	buf++;
	//}

	//std::bitset<32> set(Binary);
	//int HexNumber = set.to_ulong();
	//bool negative = !!(HexNumber & 0x80000000);
	//int  exponent = (HexNumber & 0x7f800000) >> 23;
	//int sign = negative ? -1 : 1;
	//// Subtract 127 from the exponent     
	//exponent -= 127;
	//// Convert the mantissa into decimal using the     
	//// last 23 bits     
	//int power = -1;
	//float total = 0.0;
	//for (int i = 0; i < 23; i++)     {
	//	int c = Binary[i + 9] - '0';
	//	total += (float)c * (float)pow(2.0, power);
	//	power--;
	//}
	//total += 1.0;
	//float value = sign * (float)pow(2.0, exponent) * total;
	////float value = 0;

	//return value;

	//std::string s(reinterpret_cast<char const*>(buf), 8);

	//ret = GetFloat32(s);
	//str.append(buf, 8);

	////ret =  *((double*)buf);
	////ret = *reinterpret_cast<double*>(buf);
	////buf+=8;
	//DOUBLE a = 0;
	//for(int i = 0; i< size; i++)
	//{
	//	a = *(buf++) << 8*i;
	//	ret += a;
	//}

	//int sign = b & 0x80? 1 : 0;
	//int quotient = b & 0x7F << 4;
	//
	//b = *(buf++);
	//quotient |= b&0xF0 >> 4;

	//int mantissa = b&0x0F << 48;

	//for(int i = 0; i < size; i++)
	//{
	//	mantissa |= ((*(buf++))<<(8*i))&(0xff<<(8*i));
	//	//ret = ret << 8 | *buf;
	//	//buf++;
	//}

	//return ret;
}

int asNumeric( wchar_t wch )
{
	int result = -1;
	for ( wchar_t const* const* p = std::begin( digitTables );
		p != std::end( digitTables ) && result == -1;
		++ p ) {
			wchar_t const* q = std::find( *p, *p + 10, wch );
			if ( q != *p + 10 ) {
				result = (int)(q - *p);
			}
	}
	return result;
}
