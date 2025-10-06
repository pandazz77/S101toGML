#pragma once
#include "Field.h"
#include <vector>

#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else

#endif
struct ATTR;

class F_ATTR : Field
{
public:
	F_ATTR();
	virtual ~F_ATTR();

public:
	std::vector<ATTR*> m_arr;

public:
	void ReadField(std::uint8_t *&buf);
	void ReadField(std::uint8_t *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();
};