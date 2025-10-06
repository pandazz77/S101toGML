#include "compat_mfc.h"
#include "RecordName.h"

#include <string>
RecordName::RecordName(void)
{
}


RecordName::~RecordName(void)
{
}

std::int64_t RecordName::GetName()
{
	return ((std::int64_t)RCNM) << 32 | RCID;
}

int RecordName::GetLength()
{
	return 5;
}

std::wstring RecordName::GetRCIDasWstring() 
{
	return std::to_wstring(RCID);
}