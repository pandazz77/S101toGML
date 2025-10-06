#pragma once
#include "Namespace_GISLibrary.h"
#include "Enum_S100_FileType.h"
#include "MBR.h"

#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else

#endif
//#include "..\\GeoMetryLibrary\\MBR.h"

#include "String.h"

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
	virtual bool Open(libS101::String _filepath);
	void Save(libS101::String _filepath, libS101::String extend);

	libS101::String GetLayerName();
	libS101::String GetLayerPath();
	libS101::String GetLayerType();

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