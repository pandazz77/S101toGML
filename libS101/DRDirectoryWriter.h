#pragma once

#include "DRDirectory.h"
#include "DRReader.h"

#ifdef _WIN32
#include <atlstr.h>
#else
#include "compat/compat_mfc.h"
#endif

struct DRDirectoryWriter : public DRDirectory
{
public:
	DRDirectoryWriter();
	DRDirectoryWriter(DRReader leader, DRDirectory& dir);
	virtual ~DRDirectoryWriter();

public:
	int lengthCipher;
	int posCipher;

	std::uint8_t b_length[9];
	std::uint8_t b_pos[9];
};
