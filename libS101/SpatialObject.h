#pragma once
#include "Enum_S100_FileType.h"
#include "Namespace_GISLibrary.h"

#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else

#endif
#include <string>
#include "String.h"

class Layer;
class Scaler;

class SpatialObject
{
public:
	SpatialObject();
	virtual ~SpatialObject();

public:
	Layer* m_pLayer = nullptr;
	S100_FileType m_FileType; // ���� Ÿ�� : SHP, S-57, S-101, GML ����

private:
	libS101::String m_FilePath; // ���� ��ü ��� (�̸� ����)
	libS101::String m_FileName; // ���� �̸� (Ȯ���� ����)

public:
	virtual bool Open(libS101::String _filepath);
	/*virtual void Draw(CDC *pDC, Scaler *scaler, double offset = 0) {};
	virtual void Draw(HDC &hDC, Scaler *scaler, double offset = 0) {};
	virtual void Draw(HDC &hDC, Scaler *scaler, int priority, int geoType, double offset = 0) {};
	virtual void Draw(GISLibrary::D2D1Resources* D2, Scaler* scaler) {};
	virtual void Draw(CDCRenderTarget* pRenderTarget, Scaler *scaler, double offsetX = 0, double offsetY = 0) {};
	virtual void Draw(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory *pDXFactory, Scaler *scaler, double offsetX = 0, double offsetY = 0) {};*/
	virtual void Save(libS101::String filename, libS101::String extend);

	void SetLayer(Layer* value);
	Layer* GetLayer();


	void SetFilePath(libS101::String& value);
	libS101::String GetFilePath();

	void SetFileName(libS101::String& value);
	libS101::String GetFileName();

	void SetFileType(S100_FileType value);
	S100_FileType GetFileType();

};