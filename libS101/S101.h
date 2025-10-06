#pragma once

#include "libS101.h"
#include "R_DSGIR.h"
#include "R_DSCRS.h"
#include "S100SpatialObject.h"
#include "DDR.h"
#include "MBR.h"
#include "OrientedCurveRecord.h"
#include "SCurveHasOrient.h"
#include "Point.h"


#include <string>
#include <vector>
#include <list>

class R_InformationRecord;
class R_PointRecord;
class R_MultiPointRecord;
class R_CurveRecord;
class R_CompositeRecord;
class R_SurfaceRecord;
class R_FeatureRecord;


class SPoint;
class SCurve;
class SSurface;
class SMultiPoint;
class SCompositeCurve;
class GeoPointZ;
class GeoPoint;

namespace libS101
{
	// aka GISLibrary::S101Cell
    class S101 : public S100SpatialObject
	{
	public:
		S101();
		virtual ~S101();

	public:
		MBR mbr;
		DDR m_S101DDR;
		// Dataset General Information Record 
		R_DSGIR m_dsgir;

		// Dataset Coordinate Reference System Record 
		// Base : O
		// Update : X
		// Comment : ������Ʈ ������ �� ���� ���ڵ� �̹Ƿ� ������ ������ ���� �ʿ�
		R_DSCRS m_dscrs;

		std::vector<R_InformationRecord*> vecInformation;
		std::vector<R_PointRecord*> vecPoint;
		std::vector<R_MultiPointRecord*> vecMultiPoint;
		std::vector<R_CurveRecord*> vecCurve;
		std::vector<R_CompositeRecord*> vecComposite;
		std::vector<R_SurfaceRecord*> vecSurface;
		std::vector<R_FeatureRecord*> vecFeature;

	private:
		std::unordered_map<std::int64_t, SCurve*> m_curveMap;

	public:
		bool Open(libS101::String _filepath);
		void Save(libS101::String _filepath, libS101::String extend);

		std::string GetEncodingSpecificationToString();
		libS101::String GetEncodingSpecification();

		std::string GetDatasetTitleToString();
		libS101::String GetDatasetTitle();

		std::string GetDatasetEditionToString();
		libS101::String GetEncodingSpecificationEdition();
		libS101::String GetDatasetEdition();

		libS101::String GetDatasetReferenceDate();
		std::string GetEncodingSpecificationEditionToString();

		libS101::String GetProductIdentifier();
		std::string GetProductIdentifierToString();
		std::string GetDatasetReferenceDataToString();

		libS101::String GetApplicationProfile();
		std::string GetApplicationProfileToString();

		libS101::String GetDatasetFileIdentifier();
		std::string GetDatasetFileIdentifierToString();

		libS101::String GetProductEdition();
		std::string GetProductEditionToString();

		libS101::String GetDatasetLanguage();
		std::string GetDatasetLanguageToString();

		libS101::String GetDatasetAbstract();
		std::string GetDatasetAbstractToString();

	private:
		void InsertInformationRecord(std::int64_t key, R_InformationRecord* record);
		void InsertPointRecord(std::int64_t key, R_PointRecord* record);
		void InsertMultiPointRecord(std::int64_t key, R_MultiPointRecord* record);
		void InsertCurveRecord(std::int64_t key, R_CurveRecord* record);
		void InsertCompositeCurveRecord(std::int64_t key, R_CompositeRecord* record);
		void InsertSurfaceRecord(std::int64_t key, R_SurfaceRecord* record);
		void InsertFeatureRecord(std::int64_t key, R_FeatureRecord* record);

		bool ReadDDR(std::uint8_t*& buf);

		bool MakeFullSpatialData();
		bool MakePointData(R_FeatureRecord* fe);
		bool MakeSoundingData(R_FeatureRecord* fe);
		bool MakeLineData(R_FeatureRecord* fe);
		bool MakeAreaData(R_FeatureRecord* fe);

		SCurve* GetCurveGeometry(R_CurveRecord* r/*, std::vector<GeoPoint> &geoArr, unsigned ORNT = 1*/);
		bool SetSCurveList(std::list<OrientedCurveRecord>* inCurveRecordList, std::list<SCurveHasOrient>* outSCurveList);

		bool GetFullCurveData(R_FeatureRecord* fe, R_PointRecord* r, int ornt = 1);
		bool GetFullCurveData(R_FeatureRecord* fe, R_MultiPointRecord* r, int ornt = 1);
		bool GetFullCurveData(R_FeatureRecord* fe, R_CurveRecord* r, int ornt = 1);
		bool GetFullCurveData(R_FeatureRecord* fe, R_CompositeRecord* r, int ornt = 1);
		bool GetFullCurveData(R_FeatureRecord* fe, R_SurfaceRecord* r, int ornt = 1);

		bool GetFullSpatialData(R_PointRecord* r, GeoPoint& geo);
		bool GetFullSpatialData(R_PointRecord* r, GeoPointZ& geo);
		bool GetFullSpatialData(R_MultiPointRecord* r, std::vector<GeoPointZ>& geoArr);
		bool GetFullSpatialData(R_CurveRecord* r, std::vector<GeoPoint>& geoArr, int ORNT = 1);
		bool GetFullSpatialData(R_CurveRecord* r, std::vector<Point>& geoArr, int ORNT = 1);
		bool GetFullSpatialData(R_CompositeRecord* r, std::vector<GeoPoint>& geoArr, int ORNT = 1);
		bool GetFullSpatialData(R_CompositeRecord* r, std::vector<Point>& geoArr, int ORNT = 1);
		bool GetFullSpatialData(R_SurfaceRecord* r, std::vector<GeoPoint>& geoArr);

		R_MultiPointRecord* findMultiPointRecord(long long value);
		R_PointRecord* findPointRecord(long long value);
		R_CurveRecord* findCurveRecord(long long value);
		R_CompositeRecord* findCompositeRecord(long long value);
		R_SurfaceRecord* findSurfaceRecord(long long value);

		void CalcMBR();
		void ClearCurveMap();

		std::string CStringToString(libS101::String str);
		std::string WStringToString(std::wstring str);
	};
}