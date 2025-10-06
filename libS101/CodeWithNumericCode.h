#pragma once

#include <string>

#include "String.h"

class CodeWithNumericCode
{
public:
	/*
	* Code
	* Format		: A
	* Description	: The code as defined in the feature catalogue
	*/
	libS101::String m_code;

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