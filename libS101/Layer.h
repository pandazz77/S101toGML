#pragma once
#include "Namespace_GISLibrary.h"
#include "Enum_S100_FileType.h"
#include "MBR.h"

#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else
#include "compat/compat_mfc.h"
#endif
//#include "..\\GeoMetryLibrary\\MBR.h"

class SpatialObject;
class Scaler;

//���̾� �������� ������ Class
class Layer
{

public:
	Layer();
	virtual ~Layer();

public:
	bool	      On;
	bool		Info;
	//���� ���̾ �׸��� �� �׸��� �����մϴ�.
	//bool		InfoOn;
	// ��������
	MBR			  m_mbr;
	SpatialObject *m_spatialObject = nullptr;

	int scaleMinimum = 0;
	int scaleMaximum = 0;

public:
	virtual bool Open(CString _filepath);
	void Save(CString _filepath, CString extend);

	CString GetLayerName();
	CString GetLayerPath();
	CString GetLayerType();

	void SetMBR(MBR& value);
	MBR GetMBR();
	void SetSpatialObject(SpatialObject* value);
	SpatialObject* GetSpatialObject();
	bool IsS100Layer();

	S100_FileType GetFileType();

	int GetScaleMinimum();
	void SetScaleMiminum(int value);

	int GetScaleMaximum();
	void SetScaleMaximum(int value);
}; 