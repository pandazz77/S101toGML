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
	std::unordered_map<long long, MASK*> m_arr;

public:
	void ReadField(std::uint8_t *&buf);
	void ReadField(std::uint8_t *&buf, int loopCnt);
	bool Save(libS101::File *file);
	int GetFieldLength();

};

