

#include "S101.h"
#include "R_CompositeRecord.h"
#include "R_SurfaceRecord.h"
#include "R_InformationRecord.h"
#include "R_MultiPointRecord.h"
#include "R_CurveRecord.h"
#include "R_FeatureRecord.h"
#include "R_PointRecord.h"
#include "DRDirectory.h"
#include "DRDirectoryInfo.h"
#include "ISO8211Fuc.h"
#include "ATTR.h"
#include "F_INAS.h"
#include "F_FASC.h"
#include "CodeWithNumericCode.h"
#include "F_CodeWithNumericCode.h"
#include "SCompositeCurve.h"
#include "SPoint.h"
#include "SSurface.h"
#include "SCurve.h"
#include "SMultiPoint.h"
#include "S100_CD_AttributeValueType.h"
#include "GeoCommonFuc.h"
#include "SCurveHasOrient.h"
#include "F_SPAS.h"
#include "SPAS.h"
#include "GeoPointZ.h"
#include "GeoPoint.h"
#include "RIAS.h"
#include "F_RIAS.h"
#include "F_CUCO.h"
#include "CUCO.h"
#include "F_C3IT.h"
#include "F_C2IT.h"
#include "F_C3IL.h"
#include "C3IL.h"
#include "F_C2IL.h"
#include "PTAS.h"
#include "F_PTAS.h"
#include "IC2D.h"
#include "S100Utilities.h"


#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s,__NORMAL_BLOCK,__FILE__,__LINE__)
#endif

namespace libS101
{
	S101::S101() {
		//_CrtSetBreakAlloc(266);
		//_CrtDumpMemoryLeaks();
	}

	S101::~S101()
	{

		for (auto itor = vecInformation.begin(); itor != vecInformation.end(); itor++)
		{
			R_InformationRecord* ir = *(itor);
			delete ir;
			ir = nullptr;
		}
		vecInformation.clear();

		for (auto itor = vecPoint.begin(); itor != vecPoint.end(); itor++)
		{
			R_PointRecord* ir = *(itor);
			delete ir;
			ir = nullptr;
		}
		vecPoint.clear();

		for (auto itor = vecMultiPoint.begin(); itor != vecMultiPoint.end(); itor++)
		{
			R_MultiPointRecord* ir = *(itor);
			delete ir;
			ir = nullptr;
		}
		vecMultiPoint.clear();

		for (auto itor = vecCurve.begin(); itor != vecCurve.end(); itor++)
		{
			R_CurveRecord* ir = *(itor);
			delete ir;
			ir = nullptr;
		}
		vecCurve.clear();

		for (auto itor = vecComposite.begin(); itor != vecComposite.end(); itor++)
		{
			R_CompositeRecord* ir = *(itor);
			delete ir;
			ir = nullptr;
		}
		vecComposite.clear();

		for (auto itor = vecSurface.begin(); itor != vecSurface.end(); itor++)
		{
			R_SurfaceRecord* ir = *(itor);
			delete ir;
			ir = nullptr;
		}
		vecSurface.clear();

		for (auto itor = vecFeature.begin(); itor != vecFeature.end(); itor++)
		{
			R_FeatureRecord* ir = *(itor);

			delete ir->m_geometry;
			ir->m_geometry = nullptr;

			delete ir;
			ir = nullptr;
		}
		vecFeature.clear();

		for (auto iter = m_curveMap.begin(); iter != m_curveMap.end(); iter++)
		{
			SCurve* c = iter->second;
			delete c;
			c = nullptr;
		}
		m_curveMap.clear();

	}



#pragma warning(disable:4018)
	bool S101::Open(libS101::String _filepath) // Dataset ����, .000 ��������
	{

		SetFilePath(_filepath);

		File file;

		file.open(_filepath.str(),std::ios::in);
		if (file.is_open())
		{
			std::uint8_t* pBuf = nullptr;
			std::uint8_t* sBuf = nullptr;
			std::uint8_t* endOfBuf = nullptr;


			long long fileLength = file.length();

			pBuf = new std::uint8_t[(unsigned int)fileLength];
			sBuf = pBuf;

			file.read(pBuf, (unsigned)fileLength);


			m_FileType = FILE_S_100_VECTOR;
			S100Product = S100::S100_DataProduct::S_101;

			endOfBuf = pBuf + fileLength - 1;

			file.close();

			ReadDDR(pBuf);

			DRDirectoryInfo drDir;

			int tcnt = 0;
			while (pBuf < endOfBuf)
			{
				auto curRecordAddress = pBuf;

				tcnt++;
				DRReader drReader;
				int subFieldCount = 0;
				drReader.ReadReader(pBuf);
				subFieldCount = (drReader.m_fieldAreaLoc - DR_LENGTH - 1) / (4 + drReader.m_fieldLength + drReader.m_fieldPosition);

				if (subFieldCount < 1)
				{
					continue;
				}

				drDir.ReAllocateDirectory(subFieldCount);

				drDir.ReadDir(drReader, pBuf);

				if (*(pBuf++) != 0x1E)
				{

				}

				if (drDir.GetDirectory(0)->tag == *((unsigned int*)"DSID"))
				{
					m_dsgir.ReadRecord(&drDir, pBuf);
				}
				else if (drDir.GetDirectory(0)->tag == *((unsigned int*)"CSID"))
				{
					m_dscrs.ReadRecord(&drDir, pBuf);
				}

				else if (drDir.GetDirectory(0)->tag == *((unsigned int*)"IRID"))
				{
					R_InformationRecord* r = new R_InformationRecord();
					r->ReadRecord(&drDir, pBuf);
					InsertInformationRecord(r->m_irid.m_name.GetName(), r);
				}

				else if (drDir.GetDirectory(0)->tag == *((unsigned int*)"PRID"))
				{
					R_PointRecord* r = new R_PointRecord();
					r->ReadRecord(&drDir, pBuf);
					auto names = r->m_prid.m_name.GetName();

					InsertPointRecord(r->m_prid.m_name.GetName(), r);
				}
				else if (drDir.GetDirectory(0)->tag == *((unsigned int*)"MRID"))
				{
					R_MultiPointRecord* r = new R_MultiPointRecord();
					r->ReadRecord(&drDir, pBuf);

					InsertMultiPointRecord(r->m_mrid.m_name.GetName(), r);
				}
				else if (drDir.GetDirectory(0)->tag == *((unsigned int*)"CRID"))
				{
					R_CurveRecord* r = new R_CurveRecord();
					r->ReadRecord(&drDir, pBuf);

					InsertCurveRecord(r->m_crid.m_name.GetName(), r);
				}
				else if (drDir.GetDirectory(0)->tag == *((unsigned int*)"CCID"))
				{
					R_CompositeRecord* r = new R_CompositeRecord();
					r->ReadRecord(&drDir, pBuf);

					InsertCompositeCurveRecord(r->m_ccid.m_name.GetName(), r);
				}
				else if (drDir.GetDirectory(0)->tag == *((unsigned int*)"SRID"))
				{
					R_SurfaceRecord* r = new R_SurfaceRecord();
					r->ReadRecord(&drDir, pBuf);

					InsertSurfaceRecord(r->m_srid.m_name.GetName(), r);
				}
				else if (drDir.GetDirectory(0)->tag == *((unsigned int*)"FRID"))
				{
					R_FeatureRecord* r = new R_FeatureRecord();
					r->ReadRecord(&drDir, pBuf);

					InsertFeatureRecord(r->m_frid.m_name.GetName(), r);
				}

				pBuf = curRecordAddress + drReader.m_recordLength;
			}

			delete[] sBuf;

			MakeFullSpatialData();

			CalcMBR();


			return true;
		}
		else {
			return false;
		}
		return true;
	}

	void S101::Save(libS101::String _filepath, libS101::String extend)
	{
		S100Utilities::OutputDebugString(L"S101::Save DOESNT IMPLEMENTED\n");
	}

	std::string S101::GetEncodingSpecificationToString()
	{
		return GetEncodingSpecification().str();
	}

	libS101::String S101::GetEncodingSpecification()
	{
		return m_dsgir.m_dsid.m_ensp;
	}

	void  S101::InsertInformationRecord(std::int64_t key, R_InformationRecord* record)
	{
		vecInformation.push_back(record);
	}

	void  S101::InsertPointRecord(std::int64_t key, R_PointRecord* record)
	{
		vecPoint.push_back(record);
	}

	void  S101::InsertMultiPointRecord(std::int64_t key, R_MultiPointRecord* record)
	{
		vecMultiPoint.push_back(record);
	}

	void  S101::InsertCurveRecord(std::int64_t key, R_CurveRecord* record)
	{
		vecCurve.push_back(record);
	}

	void  S101::InsertCompositeCurveRecord(std::int64_t key, R_CompositeRecord* record)
	{
		vecComposite.push_back(record);
	}

	void  S101::InsertSurfaceRecord(std::int64_t key, R_SurfaceRecord* record)
	{
		vecSurface.push_back(record);
	}

	void  S101::InsertFeatureRecord(std::int64_t key, R_FeatureRecord* record)
	{
		vecFeature.push_back(record);
	}

	bool S101::ReadDDR(std::uint8_t*& buf)
	{
		int size = atoi(buf, 5);
		buf -= 5;

		m_S101DDR.SetBytes(size, buf);

		buf += m_S101DDR.GetSize();

		return true;
	}

	std::string S101::GetEncodingSpecificationEditionToString()
	{
		return GetEncodingSpecificationEdition().str();
	}

	libS101::String S101::GetProductIdentifier()
	{
		return m_dsgir.m_dsid.m_prsp;
	}

	std::string S101::GetProductIdentifierToString()
	{
		return GetProductIdentifier().str();
	}

	libS101::String S101::GetProductEdition()
	{
		return m_dsgir.m_dsid.m_pred;
	}

	std::string S101::GetProductEditionToString()
	{
		return GetProductEdition().str();
	}

	std::string S101::GetDatasetReferenceDataToString()
	{
		return GetDatasetReferenceDate().str();
	}

	libS101::String S101::GetApplicationProfile()
	{
		return m_dsgir.m_dsid.m_prof;
	}

	std::string S101::GetApplicationProfileToString()
	{
		return GetApplicationProfile().str();
	}

	std::string S101::GetDatasetEditionToString()
	{
		return GetDatasetEdition().str();
	}

	std::string S101::GetDatasetFileIdentifierToString()
	{
		return GetDatasetFileIdentifier().str();
	}


	libS101::String S101::GetDatasetFileIdentifier()
	{
		return m_dsgir.m_dsid.m_dsnm;
	}

	libS101::String S101::GetDatasetReferenceDate()
	{
		return m_dsgir.m_dsid.m_dsrd;
	}

	libS101::String S101::GetDatasetEdition()
	{
		return m_dsgir.m_dsid.m_dsed;
	}


	libS101::String S101::GetEncodingSpecificationEdition()
	{
		return m_dsgir.m_dsid.m_ened;
	}

	libS101::String S101::GetDatasetTitle()
	{
		return m_dsgir.m_dsid.m_dstl;
	}
	std::string S101::GetDatasetTitleToString()
	{
		return GetDatasetTitle().str();
	}

	std::string S101::GetDatasetLanguageToString()
	{
		return GetDatasetLanguage().str();
	}

	libS101::String S101::GetDatasetLanguage()
	{
		return m_dsgir.m_dsid.m_dslg;
	}


	libS101::String S101::GetDatasetAbstract()
	{
		return m_dsgir.m_dsid.m_dsab;
	}

	std::string S101::GetDatasetAbstractToString()
	{
		return GetDatasetAbstract().str();
	}

	bool S101::MakeFullSpatialData()
	{
		ClearCurveMap();

		R_FeatureRecord* fr;

		for (auto itor = vecFeature.begin(); itor != vecFeature.end(); itor++)
		{
			fr = *(itor);
			if (fr->m_spas.size() == 0)
			{
				continue;
			}

			for (auto itorParent = fr->m_spas.begin(); itorParent != fr->m_spas.end(); itorParent++)
			{
				F_SPAS* spasParent = *itorParent;

				for (auto itor = spasParent->m_arr.begin(); itor != spasParent->m_arr.end(); itor++)
				{
					SPAS* spas = *itor;

					if (spas->m_name.RCNM == 110)
					{
						MakePointData(fr);
					}
					else if (spas->m_name.RCNM == 115)
					{
						MakeSoundingData(fr);
					}
					else if (spas->m_name.RCNM == 120 || spas->m_name.RCNM == 125)
					{
						MakeLineData(fr);
					}
					else if (spas->m_name.RCNM == 130)
					{
						MakeAreaData(fr);
					}
				}
			}
		}
		return true;
	}
	bool S101::MakePointData(R_FeatureRecord* fe)
	{
		fe->m_curveList.clear();
		SPAS* spas = NULL;
		R_PointRecord* r;
		std::int64_t iKey;

		GeoPoint geoArr;

		for (auto itorParent = fe->m_spas.begin(); itorParent != fe->m_spas.end(); itorParent++)
		{
			F_SPAS* spasParent = *itorParent;

			for (auto itor = spasParent->m_arr.begin(); itor != spasParent->m_arr.end(); itor++)
			{
				SPAS* spas = *itor;

				iKey = ((std::int64_t)spas->m_name.RCNM) << 32 | spas->m_name.RCID;

				r = findPointRecord(iKey);

				if (r != nullptr) {
					if (r->m_c2it)
					{
						GeoPoint geoArr;
						GetFullCurveData(fe, r);
						GetFullSpatialData(r, geoArr);

						if (fe->m_geometry)
							delete fe->m_geometry;

						fe->m_geometry = new SPoint();
						SPoint* geo = (SPoint*)fe->m_geometry;

						geo->SetPoint(geoArr.x, geoArr.y);

						geo->m_mbr.CalcMBR(geoArr.x, geoArr.y);
					}
					else if (r->m_c3it)
					{
						GeoPointZ geoArr;

						GetFullCurveData(fe, r);
						GetFullSpatialData(r, geoArr);

						int cnt = 1;

						if (fe->m_geometry)
							delete fe->m_geometry;

						fe->m_geometry = new SMultiPoint();
						SMultiPoint* geo = (SMultiPoint*)fe->m_geometry;

						geo->m_numPoints = cnt;
						if (!geo->m_pPoints)
						{
							geo->m_pPoints = new std::vector<GeoPointZ>(geo->m_numPoints);//new GeoPointZ[geo->m_numPoints];
						}
						else
						{
							geo->m_pPoints->clear();
							if ((int)(*geo->m_pPoints).size() < geo->m_numPoints)
								(*geo->m_pPoints).resize(geo->m_numPoints + 1);
						}

						for (int i = 0; i < cnt; i++)
						{
							(*geo->m_pPoints)[i].SetPoint(geoArr.x, geoArr.y, geoArr.z);
						}
					}
				}
			}
		}
		return true;
	}
	bool S101::MakeSoundingData(R_FeatureRecord* fe)
	{
		fe->m_curveList.clear();
		R_MultiPointRecord* r;
		std::int64_t iKey;

		std::vector<GeoPointZ> geoArr;


		for (auto itorParent = fe->m_spas.begin(); itorParent != fe->m_spas.end(); itorParent++)
		{
			F_SPAS* spasParent = *itorParent;

			for (auto itor = spasParent->m_arr.begin(); itor != spasParent->m_arr.end(); itor++)
			{
				SPAS* spas = *itor;

				iKey = ((std::int64_t)spas->m_name.RCNM) << 32 | spas->m_name.RCID;

				r = findMultiPointRecord(iKey);
				if (r != nullptr) {
					GetFullSpatialData(r, geoArr);
				}
			}
		}

		int cnt = 0;
		cnt = (int)geoArr.size();

		if (fe->m_geometry)
			delete fe->m_geometry;

		fe->m_geometry = new SMultiPoint();
		SMultiPoint* geo = (SMultiPoint*)fe->m_geometry;

		//���⼭ �޸� ����
		geo->m_numPoints = cnt;
		if (!geo->m_pPoints) geo->m_pPoints = new std::vector<GeoPointZ>(geo->m_numPoints);//new GeoPointZ[geo->m_numPoints];
		else
		{
			geo->m_pPoints->clear();
			if ((int)(*geo->m_pPoints).size() < geo->m_numPoints)
				(*geo->m_pPoints).resize(geo->m_numPoints + 1);
		}

		if (geo->m_numPoints > SGeometry::sizeOfPoint)
		{
			SGeometry::sizeOfPoint = geo->m_numPoints;
			delete SGeometry::viewPoints;
			SGeometry::viewPoints = new Point[int(SGeometry::sizeOfPoint * 1.5)];
		}

		for (int i = 0; i < cnt; i++)
		{
			(*geo->m_pPoints)[i].SetPoint(geoArr[i].x, geoArr[i].y, geoArr[i].z);
			geo->m_mbr.CalcMBR(geoArr[i].x, geoArr[i].y);
		}

		geoArr.clear();
		return true;
	}

	bool S101::MakeLineData(R_FeatureRecord* fe)
	{
		fe->m_curveList.clear();

		R_CurveRecord* cr = nullptr;

		R_CompositeRecord* ccr = nullptr;

		std::int64_t iKey = 0;

		if (fe->m_geometry)
		{
			delete fe->m_geometry;
			fe->m_geometry = nullptr;
		}

		for (auto i = fe->m_spas.begin(); i != fe->m_spas.end(); i++)
		{
			F_SPAS* spasParent = *i;

			for (auto j = spasParent->m_arr.begin(); j != spasParent->m_arr.end(); j++)
			{
				SPAS* spas = *j;
				iKey = ((std::int64_t)spas->m_name.RCNM) << 32 | spas->m_name.RCID;

				ccr = findCompositeRecord(iKey);
				if (ccr != nullptr)
				{
					GetFullCurveData(fe, ccr, spas->m_ornt);
				}

				cr = findCurveRecord(iKey);
				if (cr != nullptr)
				{
					GetFullCurveData(fe, cr, spas->m_ornt);
				}
			}
		}

		SCompositeCurve* scc = new SCompositeCurve();
		fe->m_geometry = scc;

		SetSCurveList(&fe->m_curveList, &scc->m_listCurveLink);

		scc->SetMBR();

		return true;
	}

	bool S101::SetSCurveList(std::list<OrientedCurveRecord>* inCurveRecordList, std::list<SCurveHasOrient>* outSCurveList)
	{
		for (auto c = inCurveRecordList->begin(); c != inCurveRecordList->end(); c++)
		{
			OrientedCurveRecord* ocr = &(*c);

			std::int64_t iKey = ((std::int64_t)ocr->m_pCurveRecord->m_crid.m_name.RCNM) << 32 | ocr->m_pCurveRecord->m_crid.m_name.RCID;
			auto curveIter = m_curveMap.find(iKey);

			bool bOrnt = ocr->m_orient == 1 ? true : false;

			if (curveIter != m_curveMap.end())
			{
				SCurveHasOrient curveHasOrient(bOrnt, curveIter->second);
				outSCurveList->push_back(curveHasOrient);
			}
			else
			{
				SCurve* pCurve = GetCurveGeometry(ocr->m_pCurveRecord/*, geoArr, ocr->m_orient*/);
				pCurve->m_id = iKey;
				SCurveHasOrient curveHasOrient(bOrnt, pCurve);
				outSCurveList->push_back(curveHasOrient);

				m_curveMap.insert({ iKey, pCurve });
			}
		}
		return true;
	}

	SCurve* S101::GetCurveGeometry(R_CurveRecord* r/*, std::vector<GeoPoint> &geoArr, unsigned ORNT*/)
	{
		PTAS* ptas = NULL;
		IC2D* c2di = NULL;
		R_PointRecord* spr = nullptr, * epr = nullptr;
		GeoPoint gp;
		std::int64_t iKey;
		int coordinateIndex = 0;

		for (auto i = r->m_ptas->m_arr.begin(); i != r->m_ptas->m_arr.end(); i++)
		{
			auto ptas = *i;

			iKey = ((std::int64_t)ptas->m_name.RCNM) << 32 | ptas->m_name.RCID;
			if (ptas->m_topi == 1 /*&& ORNT == 1 ||*/	// Beginning node , forward
				/*ptas->m_topi == 2 && ORNT == 2*/		// End node, reverse
				)
			{
				spr = findPointRecord(iKey);
			}
			else if (/*ptas->m_topi == 1 && ORNT == 2 ||*/	// Beginning node , reverse
				ptas->m_topi == 2 /*&& ORNT == 1*/		// End node, forward
				)
			{
				epr = findPointRecord(iKey);
			}
			else if (ptas->m_topi == 3)
			{
				spr = findPointRecord(iKey);
				epr = spr;
			}
		}

		SCurve* retCurve = new SCurve();

		int totalCoordinateCount = 2;
		for (auto itorParent = r->m_c2il.begin(); itorParent != r->m_c2il.end(); itorParent++)
		{
			totalCoordinateCount += (int)(*itorParent)->m_arr.size();
		}

		if (totalCoordinateCount > SGeometry::sizeOfPoint)
		{
			SGeometry::sizeOfPoint = totalCoordinateCount;
			delete SGeometry::viewPoints;
			SGeometry::viewPoints = new Point[int(SGeometry::sizeOfPoint * 1.5)];
		}

		retCurve->m_numPoints = totalCoordinateCount;
		retCurve->m_pPoints = new GeoPoint[totalCoordinateCount];

		double x = spr->m_c2it->m_xcoo;// > double(180. * m_dsgir.m_dssi.m_cmfx) ? double(180. * m_dsgir.m_dssi.m_cmfx) - spr->m_c2it->m_xcoo : spr->m_c2it->m_xcoo;
		double y = spr->m_c2it->m_ycoo;// > double(180. * m_dsgir.m_dssi.m_cmfy) ? double(180. * m_dsgir.m_dssi.m_cmfy) - spr->m_c2it->m_ycoo : spr->m_c2it->m_ycoo;

		gp.SetPoint(x / (double)m_dsgir.m_dssi.m_cmfx,
			y / (double)m_dsgir.m_dssi.m_cmfy);
		projection(gp.x, gp.y);

		retCurve->m_pPoints[coordinateIndex++].SetPoint(gp.x, gp.y);
		retCurve->m_mbr.CalcMBR(gp.x, gp.y);


		for (auto itorParent = r->m_c2il.begin(); itorParent != r->m_c2il.end(); itorParent++)
		{
			for (auto itor = (*itorParent)->m_arr.begin(); itor != (*itorParent)->m_arr.end(); itor++)
			{
				IC2D* pIC2D = *itor;

				x = pIC2D->m_xcoo;// > double(180. * m_dsgir.m_dssi.m_cmfx) ? double(180. * m_dsgir.m_dssi.m_cmfx) - pIC2D->m_xcoo : pIC2D->m_xcoo;
				y = pIC2D->m_ycoo;// > double(180. * m_dsgir.m_dssi.m_cmfy) ? double(180. * m_dsgir.m_dssi.m_cmfy) - pIC2D->m_ycoo : pIC2D->m_ycoo;

				gp.SetPoint(x / (double)m_dsgir.m_dssi.m_cmfx,
					y / (double)m_dsgir.m_dssi.m_cmfy);

				projection(gp.x, gp.y);

				retCurve->m_pPoints[coordinateIndex++].SetPoint(gp.x, gp.y);
				retCurve->m_mbr.CalcMBR(gp.x, gp.y);
			}
		}


		x = epr->m_c2it->m_xcoo;// > double(180. * m_dsgir.m_dssi.m_cmfx) ? double(180. * m_dsgir.m_dssi.m_cmfx) - spr->m_c2it->m_xcoo : spr->m_c2it->m_xcoo;
		y = epr->m_c2it->m_ycoo;// > double(180. * m_dsgir.m_dssi.m_cmfy) ? double(180. * m_dsgir.m_dssi.m_cmfy) - spr->m_c2it->m_ycoo : spr->m_c2it->m_ycoo;

		gp.SetPoint(x / (double)m_dsgir.m_dssi.m_cmfx,
			y / (double)m_dsgir.m_dssi.m_cmfy);
		projection(gp.x, gp.y);

		retCurve->m_pPoints[coordinateIndex].SetPoint(gp.x, gp.y);
		retCurve->m_mbr.CalcMBR(gp.x, gp.y);

		return retCurve;
	}


	bool S101::MakeAreaData(R_FeatureRecord* fe)
	{
		fe->m_curveList.clear();

		R_SurfaceRecord* sr;
		std::int64_t iKey;
		std::vector<Point> vecPoint;
		std::vector<int> boundaryList;

		for (auto i = fe->m_spas.begin(); i != fe->m_spas.end(); i++)
		{
			F_SPAS* spasParent = *i;

			for (auto j = spasParent->m_arr.begin(); j != spasParent->m_arr.end(); j++)
			{
				SPAS* spas = *j;

				iKey = spas->m_name.GetName();

				sr = findSurfaceRecord(iKey);
				if (sr != nullptr)
				{
					for (auto k = sr->m_rias.begin(); k != sr->m_rias.end(); k++)
					{
						F_RIAS* riasParent = *k;

						for (auto l = riasParent->m_arr.begin(); l != riasParent->m_arr.end(); l++)
						{
							RIAS* rias = *l;

							auto iKey = rias->m_name.GetName();
							if (rias->m_name.RCNM == 120)
							{
								R_CurveRecord* cr = nullptr;
								cr = findCurveRecord(iKey);
								if (cr != nullptr)
								{
									GetFullCurveData(fe, cr);
									GetFullSpatialData(cr, vecPoint, rias->m_ornt);
								}
							}
							else if (rias->m_name.RCNM == 125)
							{
								R_CompositeRecord* ccr = nullptr;
								ccr = findCompositeRecord(iKey);
								if (ccr != nullptr)
								{
									GetFullCurveData(fe, ccr);
									GetFullSpatialData(ccr, vecPoint, rias->m_ornt);
								}
							}

							int sizet = (int)vecPoint.size();
							if (sizet == 0)
							{
								continue;
							}

							if (rias->m_usag == 1)
							{
								boundaryList.push_back(sizet);
							}
							else
							{
								boundaryList.push_back(sizet);
							}
						}
					}
				}
			}
		}

		int i = 0;

		if (fe->m_geometry)
		{
			delete fe->m_geometry;
		}

		fe->m_geometry = new SSurface(vecPoint, boundaryList);

		SSurface* geo = ((SSurface*)fe->m_geometry);
		fe->m_curveList.clear();

		R_CurveRecord* cr;
		R_CompositeRecord* ccr;

		for (auto i = fe->m_spas.begin(); i != fe->m_spas.end(); i++)
		{
			F_SPAS* spasParent = *i;

			for (auto j = spasParent->m_arr.begin(); j != spasParent->m_arr.end(); j++)
			{
				SPAS* spas = *j;
				iKey = spas->m_name.GetName();

				sr = findSurfaceRecord(iKey);
				if (sr != nullptr)
				{
					GetFullCurveData(fe, sr);
				}
				ccr = findCompositeRecord(iKey);
				if (ccr != nullptr) {
					GetFullCurveData(fe, ccr);
				}
				cr = findCurveRecord(iKey);
				if (cr != nullptr)
				{
					GetFullCurveData(fe, cr);
				}
			}
		}
		return true;
	}

	void S101::CalcMBR()
	{
		for (auto itor = vecFeature.begin(); itor != vecFeature.end(); itor++)
		{
			R_FeatureRecord* fe = *(itor);
			if (fe->m_geometry)
			{
				if (fe->m_geometry->type == 3) {
					SSurface* pSr = (SSurface*)fe->m_geometry;
					mbr.ReMBR(pSr->m_mbr);
				}
				else if (fe->m_geometry->type == 2) {
					auto geo = (SCompositeCurve*)fe->m_geometry;
					mbr.ReMBR(geo->m_mbr);
				}
				else if (fe->m_geometry->type == 1) {
					SPoint* geo = (SPoint*)fe->m_geometry;
					mbr.ReMBR(geo->m_mbr);
				}
			}
		}
	}

	void S101::ClearCurveMap()
	{
		for (auto iter = m_curveMap.begin(); iter != m_curveMap.end(); iter++)
		{
			SCurve* c = iter->second;
			delete c;
		}
		m_curveMap.clear();
	}

	bool S101::GetFullCurveData(R_FeatureRecord* fe, R_PointRecord* r, int ornt)
	{
		fe->m_pointList.push_back(r);
		return true;
	}

	bool S101::GetFullCurveData(R_FeatureRecord* fe, R_MultiPointRecord* r, int ornt)
	{
		return true;
	}

	bool S101::GetFullCurveData(R_FeatureRecord* fe, R_CurveRecord* r, int ornt)
	{
		OrientedCurveRecord ocr;
		ocr.m_pCurveRecord = r;
		ocr.m_orient = ornt;
		fe->m_curveList.push_back(ocr);
		return true;
	}

	bool S101::GetFullCurveData(R_FeatureRecord* fe, R_CompositeRecord* r, int ornt)
	{
		R_CurveRecord* cr = NULL;
		R_CompositeRecord* ccr = NULL;
		std::int64_t iKey;

		// forward
		if (1 == ornt)
		{
			for (auto i = r->m_cuco.begin(); i != r->m_cuco.end(); i++)
			{
				F_CUCO* cucoParent = *i;

				for (auto itor = cucoParent->m_arr.begin(); itor != cucoParent->m_arr.end(); itor++)
				{
					auto cuco = *itor;

					if (cuco->m_ornt == 2)
						ornt = (ornt == 2) ? 1 : 2;

					if (cuco->m_name.RCNM == 120)
					{
						iKey = ((std::int64_t)cuco->m_name.RCNM) << 32 | cuco->m_name.RCID;
						cr = findCurveRecord(iKey);
						if (cr != nullptr)
						{
							GetFullCurveData(fe, cr, cuco->m_ornt);
						}
					}
					else if (cuco->m_name.RCNM == 125)
					{
						iKey = ((std::int64_t)cuco->m_name.RCNM) << 32 | cuco->m_name.RCID;
						ccr = findCompositeRecord(iKey);
						if (ccr != nullptr) {
							GetFullCurveData(fe, ccr, cuco->m_ornt);
						}
					}
				}
			}
		}
		else if (2 == ornt)
		{
			for (auto i = r->m_cuco.rbegin(); i != r->m_cuco.rend(); i++)
			{
				F_CUCO* cucoParent = *i;

				for (auto itor = cucoParent->m_arr.begin(); itor != cucoParent->m_arr.end(); itor++)
				{
					auto cuco = *itor;

					if (cuco->m_ornt == 2)
						ornt = (ornt == 2) ? 1 : 2;

					if (cuco->m_name.RCNM == 120)
					{
						iKey = ((std::int64_t)cuco->m_name.RCNM) << 32 | cuco->m_name.RCID;
						cr = findCurveRecord(iKey);
						if (cr != nullptr)
						{
							GetFullCurveData(fe, cr, cuco->m_ornt);
						}
					}
					else if (cuco->m_name.RCNM == 125)
					{
						iKey = ((std::int64_t)cuco->m_name.RCNM) << 32 | cuco->m_name.RCID;
						ccr = findCompositeRecord(iKey);
						if (ccr != nullptr) {
							GetFullCurveData(fe, ccr, cuco->m_ornt);
						}
					}
				}
			}
		}

		return true;
	}

	bool S101::GetFullCurveData(R_FeatureRecord* fe, R_SurfaceRecord* r, int ornt)
	{
		R_CurveRecord* cr = NULL;
		R_CompositeRecord* ccr = NULL;
		std::int64_t iKey;

		for (auto itorParent = r->m_rias.begin(); itorParent != r->m_rias.end(); itorParent++)
		{
			F_RIAS* riasParent = *itorParent;

			for (auto itor = riasParent->m_arr.begin(); itor != riasParent->m_arr.end(); itor++)
			{
				RIAS* rias = *itor;

				if (rias->m_ornt == 2)
					ornt = (ornt == 2) ? 1 : 2;

				iKey = ((std::int64_t)rias->m_name.RCNM) << 32 | rias->m_name.RCID;
				if (rias->m_name.RCNM == 120)
				{
					cr = findCurveRecord(iKey);
					if (cr != nullptr)
					{
						GetFullCurveData(fe, cr, ornt);
					}
				}
				else if (rias->m_name.RCNM == 125)
				{
					ccr = findCompositeRecord(iKey);
					if (ccr != nullptr) {
						GetFullCurveData(fe, ccr, ornt);
					}
				}
			}
		}
		return true;
	}

	bool S101::GetFullSpatialData(R_PointRecord* r, GeoPointZ& geo)
	{
		double x = r->m_c3it->m_xcoo;
		double y = r->m_c3it->m_ycoo;
		double z = r->m_c3it->m_zcoo;

		if (m_dsgir.m_dssi.m_cmfy && m_dsgir.m_dssi.m_cmfx)
		{
			geo.SetPoint(
				x,
				y,
				z);
		}
		else
		{
			geo.SetPoint(
				x / 10000000.0,
				y / 10000000.0,
				z / 100.);
		}

		return true;
	}

	bool S101::GetFullSpatialData(R_PointRecord* r, GeoPoint& geo)
	{
		double x = r->m_c2it->m_xcoo;
		double y = r->m_c2it->m_ycoo;

		if (m_dsgir.m_dssi.m_cmfy && m_dsgir.m_dssi.m_cmfx)
		{
			geo.SetPoint(
				x / (double)m_dsgir.m_dssi.m_cmfx,
				y / (double)m_dsgir.m_dssi.m_cmfy);
		}
		else
		{
			geo.SetPoint(
				x / 10000000.0,
				y / 10000000.0);
		}
		projection(geo.x, geo.y);
		return true;
	}

	bool S101::GetFullSpatialData(R_MultiPointRecord* r, std::vector<GeoPointZ>& geoArr)
	{

		for (auto itor = r->m_c3il.begin(); itor != r->m_c3il.end(); itor++)
		{
			F_C3IL* c3il = *itor;
			for (auto itor = c3il->m_arr.begin(); itor != c3il->m_arr.end(); itor++)
			{
				C3IL* unitC3IL = *itor;

				double x = unitC3IL->m_xcoo;
				double y = unitC3IL->m_ycoo;

				GeoPointZ gpz;
				gpz.SetPoint(
					x / (double)m_dsgir.m_dssi.m_cmfx,
					y / (double)m_dsgir.m_dssi.m_cmfy,
					(unitC3IL->m_zcoo > 0 ? unitC3IL->m_zcoo + 0.5 : unitC3IL->m_zcoo - 0.5) / (double)m_dsgir.m_dssi.m_cmfz);
				projection(gpz.x, gpz.y);

				geoArr.push_back(gpz);
			}
		}

		return true;
	}

	bool S101::GetFullSpatialData(R_CurveRecord* r, std::vector<GeoPoint>& geoArr, int ORNT)
	{
		PTAS* ptas = NULL;
		IC2D* c2di = NULL;
		R_PointRecord* spr = nullptr, * epr = nullptr;
		GeoPoint gp;
		std::int64_t iKey;

		for (auto i = r->m_ptas->m_arr.begin(); i != r->m_ptas->m_arr.end(); i++)
		{
			auto ptas = *i;

			iKey = ((std::int64_t)ptas->m_name.RCNM) << 32 | ptas->m_name.RCID;
			if (ptas->m_topi == 1 && ORNT == 1 ||	// Beginning node , forward
				ptas->m_topi == 2 && ORNT == 2		// End node, reverse
				)
			{
				spr = findPointRecord(iKey);
			}
			else if (ptas->m_topi == 1 && ORNT == 2 ||	// Beginning node , reverse
				ptas->m_topi == 2 && ORNT == 1		// End node, forward
				)
			{
				epr = findPointRecord(iKey);
			}
			else if (ptas->m_topi == 3)
			{
				spr = findPointRecord(iKey);
				epr = spr;
			}
		}

		double x = spr->m_c2it->m_xcoo;
		double y = spr->m_c2it->m_ycoo;

		gp.SetPoint(x / (double)m_dsgir.m_dssi.m_cmfx,
			y / (double)m_dsgir.m_dssi.m_cmfy);
		projection(gp.x, gp.y);
		geoArr.push_back(gp);

		if (ORNT == 1)
		{
			for (auto itorParent = r->m_c2il.begin(); itorParent != r->m_c2il.end(); itorParent++)
			{
				for (auto itor = (*itorParent)->m_arr.begin(); itor != (*itorParent)->m_arr.end(); itor++)
				{
					IC2D* pIC2D = *itor;

					x = pIC2D->m_xcoo;
					y = pIC2D->m_ycoo;

					gp.SetPoint(x / (double)m_dsgir.m_dssi.m_cmfx,
						y / (double)m_dsgir.m_dssi.m_cmfy);

					projection(gp.x, gp.y);
					geoArr.push_back(gp);
				}
			}
		}
		else if (ORNT == 2)
		{
			for (auto itorParent = r->m_c2il.begin(); itorParent != r->m_c2il.end(); itorParent++)
			{
				for (auto itor = (*itorParent)->m_arr.rbegin(); itor != (*itorParent)->m_arr.rend(); itor++)
				{
					IC2D* pIC2D = *itor;

					x = pIC2D->m_xcoo;
					y = pIC2D->m_ycoo;

					gp.SetPoint(x / (double)m_dsgir.m_dssi.m_cmfx,
						y / (double)m_dsgir.m_dssi.m_cmfy);

					projection(gp.x, gp.y);
					geoArr.push_back(gp);
				}
			}
		}
		x = epr->m_c2it->m_xcoo;
		y = epr->m_c2it->m_ycoo;

		gp.SetPoint(x / (double)m_dsgir.m_dssi.m_cmfx,
			y / (double)m_dsgir.m_dssi.m_cmfy);
		projection(gp.x, gp.y);
		geoArr.push_back(gp);

		return true;
	}

	bool S101::GetFullSpatialData(R_CurveRecord* r, std::vector<Point>& geoArr, int ORNT)
	{
		if (nullptr != r->m_ptas)
		{
			auto countPTAS = r->m_ptas->m_arr.size();

			if (countPTAS != 1 && countPTAS != 2)
			{
				S100Utilities::OutputDebugString(L"Invalid count of PTAS of Curve Record\n");
			}

			auto beginPointKey = r->m_ptas->m_arr.front()->m_name.GetName();
			auto endPointKey = r->m_ptas->m_arr.back()->m_name.GetName();

			auto beginPointRecord = findPointRecord(beginPointKey);
			if (nullptr == beginPointRecord || nullptr == beginPointRecord->m_c2it)
			{
				return false;
			}


			auto endPointRecord = findPointRecord(endPointKey);
			if (nullptr == endPointRecord || nullptr == endPointRecord->m_c2it)
			{
				return false;
			}

			// PTAS
			if (1 == ORNT)
			{
				geoArr.push_back({ beginPointRecord->m_c2it->m_xcoo, beginPointRecord->m_c2it->m_ycoo });
			}
			else if (2 == ORNT)
			{
				geoArr.push_back({ endPointRecord->m_c2it->m_xcoo, endPointRecord->m_c2it->m_ycoo });
			}
			else
			{
				S100Utilities::OutputDebugString(L"Invalied ORNT\n");
			}

			// C2IL
			if (r->m_c2il.size() == 1)
			{
				// Forward
				if (1 == ORNT)
				{
					for (auto i = r->m_c2il.front()->m_arr.begin(); i != r->m_c2il.front()->m_arr.end(); i++)
					{
						auto segC2IL = *i;
						geoArr.push_back({ segC2IL->m_xcoo, segC2IL->m_ycoo });
					}
				}
				// Reverse
				else if (2 == ORNT)
				{
					for (auto i = r->m_c2il.front()->m_arr.rbegin(); i != r->m_c2il.front()->m_arr.rend(); i++)
					{
						auto segC2IL = *i;
						geoArr.push_back({ segC2IL->m_xcoo, segC2IL->m_ycoo });
					}
				}
				else
				{
					S100Utilities::OutputDebugString(L"Invalied ORNT\n");
				}
			}
			else
			{
				S100Utilities::OutputDebugString(L"Invalied C2IL count\n");
			}

			// PTAS
			if (1 == ORNT)
			{
				geoArr.push_back({ endPointRecord->m_c2it->m_xcoo, endPointRecord->m_c2it->m_ycoo });
			}
			else if (2 == ORNT)
			{
				geoArr.push_back({ beginPointRecord->m_c2it->m_xcoo, beginPointRecord->m_c2it->m_ycoo });
			}
			else
			{
				S100Utilities::OutputDebugString(L"Invalied ORNT\n");
			}
		}

		return true;
	}

	bool S101::GetFullSpatialData(R_CompositeRecord* r, std::vector<GeoPoint>& geoArr, int ORNT)
	{
		CUCO* cuco = NULL;
		R_CurveRecord* cr = NULL;
		R_CompositeRecord* ccr = NULL;
		std::int64_t iKey;

		if (ORNT == 1)
		{
			for (auto itorParent = r->m_cuco.begin(); itorParent != r->m_cuco.end(); itorParent++)
			{
				F_CUCO* cucoParent = *itorParent;

				for (auto itor = cucoParent->m_arr.begin(); itor != cucoParent->m_arr.end(); itor++)
				{
					cuco = *itor;
					if (cuco->m_name.RCNM == 120)
					{
						iKey = ((std::int64_t)cuco->m_name.RCNM) << 32 | cuco->m_name.RCID;
						cr = findCurveRecord(iKey);
						if (cr != nullptr)
						{
							GetFullSpatialData(cr, geoArr, cuco->m_ornt);
						}
					}
					else if (cuco->m_name.RCNM == 125)
					{
						iKey = ((std::int64_t)cuco->m_name.RCNM) << 32 | cuco->m_name.RCID;
						ccr = findCompositeRecord(iKey);
						if (ccr != nullptr) {
							GetFullSpatialData(ccr, geoArr, cuco->m_ornt);
						}
					}
				}
			}
		}
		else if (ORNT == 2)
		{
			for (auto itorParent = r->m_cuco.begin(); itorParent != r->m_cuco.end(); itorParent++)
			{
				F_CUCO* cucoParent = *itorParent;

				for (auto itor = cucoParent->m_arr.rbegin(); itor != cucoParent->m_arr.rend(); itor++)
				{
					cuco = *itor;
					iKey = ((std::int64_t)cuco->m_name.RCNM) << 32 | cuco->m_name.RCID;

					unsigned ornt = 1;
					if (cuco->m_ornt == 2)
						ornt = 1;
					else
						ornt = 2;

					if (cuco->m_name.RCNM == 120)
					{
						cr = findCurveRecord(iKey);
						if (cr != nullptr)
						{
							GetFullSpatialData(cr, geoArr, ornt);
						}
					}
					else if (cuco->m_name.RCNM == 125)
					{
						ccr = findCompositeRecord(iKey);
						if (ccr != nullptr) {
							GetFullSpatialData(ccr, geoArr, ornt);
						}
					}
				}
			}
		}

		return true;
	}

	bool S101::GetFullSpatialData(R_CompositeRecord* r, std::vector<Point>& geoArr, int ORNT)
	{
		for (auto i = r->m_cuco.begin(); i != r->m_cuco.end(); i++)
		{
			auto CUCO = *i;
			for (auto j = CUCO->m_arr.begin(); j != CUCO->m_arr.end(); j++)
			{
				auto segCUCO = *j;

				if (segCUCO->m_name.RCNM == 120)
				{

					auto curveRecord = findCurveRecord(segCUCO->m_name.GetName());
					if (nullptr != curveRecord)
					{
						GetFullSpatialData(curveRecord, geoArr, segCUCO->m_ornt);
					}
				}
				else if (segCUCO->m_name.RCNM == 125)
				{

					auto compositeCurveRecord = findCompositeRecord(segCUCO->m_name.GetName());
					if (nullptr != compositeCurveRecord)
					{
						GetFullSpatialData(compositeCurveRecord, geoArr, segCUCO->m_ornt);
					}
				}
				else
				{
					S100Utilities::OutputDebugString(L"Invalid RCNM in CUCO\n");
					return false;
				}
			}
		}

		return true;
	}

	bool S101::GetFullSpatialData(R_SurfaceRecord* r, std::vector<GeoPoint>& geoArr)
	{
		RIAS* rias = NULL;
		R_CurveRecord* cr = NULL;
		R_CompositeRecord* ccr = NULL;
		std::int64_t iKey;

		///////////////////////////////
		// for blank interior area
		int sp = 0;
		std::vector<int> boundaryList;
		bool isExtrior = true;
		///////////////////////////////

		for (auto itorParent = r->m_rias.begin(); itorParent != r->m_rias.end(); itorParent++)
		{
			F_RIAS* riasParent = *itorParent;

			for (auto itor = riasParent->m_arr.begin(); itor != riasParent->m_arr.end(); itor++)
			{
				RIAS* rias = *itor;
				if (sp == -1)
				{
					sp = (int)geoArr.size();
				}

				iKey = ((std::int64_t)rias->m_name.RCNM) << 32 | rias->m_name.RCID;
				if (rias->m_name.RCNM == 120)
				{
					cr = findCurveRecord(iKey);
					if (cr != nullptr)
					{
						GetFullSpatialData(cr, geoArr, rias->m_ornt);
					}
				}
				else if (rias->m_name.RCNM == 125)
				{
					ccr = findCompositeRecord(iKey);
					if (ccr != nullptr) {
						GetFullSpatialData(ccr, geoArr, rias->m_ornt);
					}
				}
				// for blank interior area
				int sizet = (int)geoArr.size() - 1;
				if (geoArr[sp].x == geoArr[sizet].x &&
					geoArr[sp].y == geoArr[sizet].y)
				{
					if (isExtrior)
					{
						sp = -1;
						isExtrior = false;
					}
					else
					{
						sp = -1;
						boundaryList.push_back(sizet + 1);
					}
				}
			}
		}
		// for blank interior area
		int arrIndex = 0;
		int i = 0;
		int index;
		int count = 0;

		for(int bindex: boundaryList){
			index = bindex + count;
			GeoPoint p(geoArr[0].x, geoArr[0].y);
			geoArr.insert(geoArr.begin()+index,p);
			count++;
		}
		return true;
	}

	R_MultiPointRecord* S101::findMultiPointRecord(long long value) {

		for (auto itor = vecMultiPoint.begin(); itor != vecMultiPoint.end(); itor++) {
			R_MultiPointRecord* r = *(itor);
			if (r->m_mrid.m_name.GetName() == value)
			{
				return r;
			}

		}
		return nullptr;
	}

	R_PointRecord* S101::findPointRecord(long long value)
	{
		for (auto itor = vecPoint.begin(); itor != vecPoint.end(); itor++) {
			R_PointRecord* r = *(itor);
			if (r->m_prid.m_name.GetName() == value)
			{
				return r;
			}

		}
		return nullptr;

	}

	R_CurveRecord* S101::findCurveRecord(long long value)
	{
		for (auto itor = vecCurve.begin(); itor != vecCurve.end(); itor++) {
			R_CurveRecord* r = *(itor);
			if (r->m_crid.m_name.GetName() == value)
			{
				return r;
			}

		}
		return nullptr;
	}

	R_CompositeRecord* S101::findCompositeRecord(long long value)
	{
		for (auto itor = vecComposite.begin(); itor != vecComposite.end(); itor++) {
			R_CompositeRecord* r = *(itor);
			if (r->m_ccid.m_name.GetName() == value)
			{
				return r;
			}

		}
		return nullptr;

	}

	R_SurfaceRecord* S101::findSurfaceRecord(long long value) {

		for (auto itor = vecSurface.begin(); itor != vecSurface.end(); itor++) {
			R_SurfaceRecord* r = *(itor);
			if (r->m_srid.m_name.GetName() == value)
			{
				return r;
			}

		}
		return nullptr;
	}

        std::string S101::CStringToString(libS101::String str)
	{
		return str.str();
	}

	std::string S101::WStringToString(std::wstring str)
	{
		std::string Value;
		Value.assign(str.begin(), str.end());

		return Value;
	}
}