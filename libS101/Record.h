#pragma once

#include <cstdint>

class DRDirectoryInfo;
class Record
{
public:
	Record();
	virtual ~Record();

public:
	virtual bool ReadRecord(DRDirectoryInfo* dir, std::uint8_t*& buf) {	return true; };
};