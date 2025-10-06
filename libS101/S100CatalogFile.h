#pragma once

#include "SpatialObject.h"

class S100CatalogFile :
	public SpatialObject
{
public:
	S100CatalogFile();
	virtual ~S100CatalogFile();

public:


public:
	bool Open(libS101::String _filepath);
};

