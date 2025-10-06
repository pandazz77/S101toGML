
#include "DRDirectoryInfoWriter.h"
#include "DRDirectoryWriter.h"


DRDirectoryInfoWriter::DRDirectoryInfoWriter(void) 
	: DRDirectoryInfo()
{
}

DRDirectoryInfoWriter::DRDirectoryInfoWriter(int directoryCount)
	: DRDirectoryInfo(directoryCount)
{
}


DRDirectoryInfoWriter::~DRDirectoryInfoWriter(void)
{
}

bool DRDirectoryInfoWriter::WriteDRDirectory(libS101::File* file, const DRReader dr)
{
	for(int i = 0; i < m_count; i++)
	{
		DRDirectoryWriter dirWriter(dr, directories[i]);
		
		file->write(&dirWriter.tag, 4);
		file->write(dirWriter.b_length, dr.m_fieldLength);
		file->write(dirWriter.b_pos, dr.m_fieldPosition);
	}

	file->write(&NonPrintableCharacter::fieldTerminator, 1);
	return true;
}

void DRDirectoryInfoWriter::CheckLength(DRReader *dr)
{	
	int len = 0;
	int pos = 0;
	for(int i = 0; i < m_count; i++)
	{
		int fLen = 1;
		int fPos = 1;
	
		len = directories[i].length;
		pos += directories[i].pos;
		
		while(len = len / 10)
		{
			fLen++;
		}
		while(pos = pos / 10)
		{
			fPos++;
		}

		dr->m_fieldLength = dr->m_fieldLength > fLen ? dr->m_fieldLength : fLen;
		dr->m_fieldPosition = dr->m_fieldPosition > fPos ? dr->m_fieldPosition : fPos;
	}
}
