#pragma once
#include "DRReader.h"

#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else

#endif

#include "File.h"

class DRReaderWriter : public DRReader
{
public:
	DRReaderWriter(void);
	virtual ~DRReaderWriter(void);

public:
	std::uint8_t b_recordLength[5];
	std::uint8_t b_interchangeLevel;
	std::uint8_t b_leaderIdentifier;
	std::uint8_t b_inLineCodeExtensionIndicator;
	std::uint8_t b_versionNumber;
	std::uint8_t b_applicationIndicator;
	std::uint8_t b_fieldControlLength[2];
	std::uint8_t b_baseAddressOfFieldArea[5];
	std::uint8_t b_extendedCharacterSetIndicator[3];

	std::uint8_t b_fieldAreaLoc;
	std::uint8_t b_fieldLength;
	std::uint8_t b_Reserved;
	std::uint8_t b_fieldPosition;

public:
	bool WriteDRReader(libS101::File* file);
	void SetByteInfo();
};