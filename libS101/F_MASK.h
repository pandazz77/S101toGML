#pragma once
#include "Field.h"
#include "RecordName.h"
#include <unordered_map>

struct MASK;
class F_MASK : Field
{
public:
	F_MASK();
	virtual ~F_MASK();

public:
        #ifdef _WIN32
        std::unordered_map<__int64, MASK*> m_arr;
        #else
        std::unordered_map<long long, MASK*> m_arr;
        #endif

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();

};

