#pragma once
class ObjectName
{
public:
	ObjectName();
	virtual ~ObjectName();

public:
        std::int64_t m_objName;
	int m_agen;
	int m_fidn;
	int m_fids;

public:
        std::int64_t GetName();
	int GetLength();
};