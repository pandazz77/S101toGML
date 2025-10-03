#pragma once
#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else
#include "compat/compat_mfc.h"
#endif
#include <string>

class CodeWithNumericCode
{
public:
	/*
	* Code
	* Format		: A
	* Description	: The code as defined in the feature catalogue
	*/
	CString m_code;

	/*
	* Code
	* Format		: b12
	* Description	: The code used within the subfield which using numeric code value
	*/
	int m_nmcd;

public:
	static int GetSize();

	int GetNumericCode();
	std::wstring GetCode();
};