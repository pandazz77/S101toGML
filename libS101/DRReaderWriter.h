#pragma once
#include "DRReader.h"

#undef _WINDOWS_
#ifdef _WIN32
#include <afxext.h>
#else
#include "compat/compat_mfc.h"
#endif

#include "File.h"

class DRReaderWriter : public DRReader
{
public:
	DRReaderWriter(void);
	virtual ~DRReaderWriter(void);

public:
	BYTE b_recordLength[5];
	BYTE b_interchangeLevel;
	BYTE b_leaderIdentifier;
	BYTE b_inLineCodeExtensionIndicator;
	BYTE b_versionNumber;
	BYTE b_applicationIndicator;
	BYTE b_fieldControlLength[2];
	BYTE b_baseAddressOfFieldArea[5];
	BYTE b_extendedCharacterSetIndicator[3];

	BYTE b_fieldAreaLoc;
	BYTE b_fieldLength;
	BYTE b_Reserved;
	BYTE b_fieldPosition;

public:
	bool WriteDRReader(libS101::File* file);
	void SetByteInfo();
};