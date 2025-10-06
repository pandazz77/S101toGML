#include <cstdint>
#include "ObjectName.h"


ObjectName::ObjectName(void)
{
	m_agen = 0;
	m_fidn = 0;
	m_fids = 0;
}


ObjectName::~ObjectName(void)
{
}

std::int64_t ObjectName::GetName()
{
	return ((std::int64_t)m_agen) << 48 | ((std::int64_t)m_fidn) << 16 | m_fids;
}

int ObjectName::GetLength()
{
	return 8;
}