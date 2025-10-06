
#include "DDR.h"
#include "ISO8211Fuc.h"

DDR::DDR()
{

}

DDR::~DDR()
{
	SetSize(0);
	Delete();
}

void DDR::Set(std::uint8_t* buffer)
{
	size = atoi(buffer, 5);
	buffer -= 5;
	
	if (size > 0)
	{
		content = new std::uint8_t[size];
		memcpy(content, buffer, size);
	}

	buffer += size;
}

void DDR::Delete()
{
	delete[] content;
	content = nullptr;
}

std::uint8_t* DDR::GetContent()
{
	return content;
}

void DDR::Allocate()
{
	if (GetSize() > 0)
	{
		Allocate(GetSize());
	}
}

void DDR::Allocate(int size)
{
	SetSize(size);
	content = new std::uint8_t[GetSize()];
}

void DDR::SetByte(int index, std::uint8_t value)
{
	if (nullptr != content &&
		index >= 0 &&
		index < GetSize())
	{
		content[index] = value;
	}
}

void DDR::SetBytes(int size, std::uint8_t* value)
{
	Delete();

	if (size > 0 && nullptr != value)
	{
		Allocate(size);
		std::memcpy(content,value,size);
	}
}

int DDR::GetSize()
{
	return size;
}

void DDR::SetSize(int value)
{
	size = value;
}