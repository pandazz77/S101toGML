#pragma once

#include "R_VectorRecord.h"
#include "F_SRID.h"

#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else
#include "compat/compat_mfc.h"
#endif
#include <list>
class F_INAS;
class F_RIAS;

// Surface Record
class R_SurfaceRecord : public R_VectorRecord
{
public:
	R_SurfaceRecord();
	virtual ~R_SurfaceRecord();

public:
	F_SRID m_srid;
	std::list<F_INAS*> m_inas;
	std::list<F_RIAS*> m_rias; // Base �϶��� 1�� �̻� �ʼ�

public:
	bool ReadRecord(DRDirectoryInfo *dir, BYTE*& buf);
	bool Save(libS101::File *file);
	int GetRCID();
	std::wstring GetRCIDasWstring();
};