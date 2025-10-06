
#include "SpatialObject.h"

SpatialObject::SpatialObject(void)
{
}

SpatialObject::~SpatialObject(void)
{
}

bool SpatialObject::Open(libS101::String _filepath)
{
	return true;
}

void SpatialObject::Save(libS101::String filename, libS101::String extend)
{
	
}

void SpatialObject::SetLayer(Layer* value)
{
	m_pLayer = value;
}

Layer* SpatialObject::GetLayer()
{
	return m_pLayer;
}

void SpatialObject::SetFilePath(libS101::String& value)
{
	m_FilePath = value;
	int index= value.rfind('\\');
	auto name= value.mid(index + 1);

	//���� �̸�, Ȯ���� ����
	SetFileName(name);
}

libS101::String SpatialObject::GetFilePath()
{
	return m_FilePath;
	
}

void SpatialObject::SetFileName(libS101::String& value)
{
	m_FileName = value;
}


libS101::String SpatialObject::GetFileName()
{
	return m_FileName;
}

void SpatialObject::SetFileType(S100_FileType value)
{
	m_FileType = value;
}

S100_FileType SpatialObject::GetFileType()
{
	return m_FileType;
}