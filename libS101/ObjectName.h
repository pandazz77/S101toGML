#pragma once
class ObjectName
{
public:
	ObjectName();
	virtual ~ObjectName();

public:
        #ifdef _WIN32
        __int64 m_objName;
        #else
        long long m_objName;
        #endif
	int m_agen;
	int m_fidn;
	int m_fids;

public:
        #ifdef _WIN32
        __int64 GetName();
        #else
        long long GetName();
        #endif
	int GetLength();
};