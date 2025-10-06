#pragma once

#include "File.h"
#include "String.h"

class Field
{
public:
	Field();
	virtual ~Field();

public:
	virtual void ReadField(std::uint8_t *&buf) {};
	virtual bool Save(libS101::File *file) { return true; };
	virtual int GetFieldLength() { return 0; };
};