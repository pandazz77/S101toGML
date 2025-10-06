#pragma once

#include <unordered_map>
#include <string>

#include "compat_mfc.h"

namespace GeoMetryLibrary
{

	enum ColorTable
	{
		Day = 0,
		Dusk,
		Night,
	};

	enum DisplayModeTable
	{
		base = 0,
		standard = 1,
		all = 2
	};

	enum UserMode
	{
		User_Mode,
		Developer_Mode,
		User_Developer_Mode
	};

	enum ReportingData
	{
		None, 
		PC,
		FC,
		DataSet
	};

	enum UnitDistance
	{
		unitDistance_km = 0,
		unitDistance_nautical_mile = 1,
	};

}

class ENCCommon
{
public:
	// true = 1  
	// false = 0 (default, �ӽ�)
	static bool SymbolizedAreaBoundary;

	// true = 1  
	// false = 0 (default, �ӽ�)
	static bool SeabedAreaType;

	static bool TWO_SHADES;
	static bool USE_SPATIAL_QUERY;
	static bool SHALLOW_PATTERN;

	//  true�� ���� ǥ��
	// false�� ���� ǥ�� ����
	static bool SOUNDING;

	//  true�� ��� �Һ� ǥ��
	// false�� ��� �Һ� ǥ�� ����
	static bool LIGHTS;

	//  ture�� Depth contour ǥ��
	// false�� Depth contour ǥ�� ����
	static bool CONTOUR_LABELS;

	static bool	TEXTOUT;

	static bool	SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER;

	static bool	FULL_SECTORS;

	// true�� scale min ����
	// false�� scale min ���� ����
	static bool APPLY_SCALE_MIN;

	// true = National Object Name ǥ��
	static bool SHOW_NOBJNM;

	static bool AVOID_CLUTTER;

	static bool SHOW_LIST_ABBREVIATION;

	static bool WGS84_TEXT_TYPE;
	static bool	SHOW_USER_COAST_AREA;
	static bool	SHOW_USER_COAST_AREA_DETAIL;

	static double SAFETY_DEPTH;				// unit : meter [IMP PS [3]]

	static double SAFETY_CONTOUR;			// unit : meter (optional)
	static double SHALLOW_CONTOUR;			// unit : meter [IMP PS [3]]
	static double DEEP_CONTOUR;				// unit : meter (optional)

	static int DISTANCE_TAGS;
	static int DISPLAY_FONT_SIZE;

	static unsigned DrawingType;		    // paper  = 1
										// simple = 0
        #ifdef _WIN32
        static std::int64_t OVER_GROUP;
        #else
        static long long OVER_GROUP;
        #endif

	static std::wstring DISPLAY_FONT_NAME;

	static int DISPLAY_MODE;
	static int m_eColorTable;
	static int UNIT_DISTANCE;
	static int m_ReportingData;
	static int m_UserMode;

	static std::unordered_map<int, bool> objectDisplaySettings;
	static std::unordered_map<std::wstring, bool> featureDisplaySettings;

	static bool DISPLAY_PLANE;

	// CUSTOM SETTINGS
	static bool SHOW_USER_WRECK;
	static bool SHOW_USER_MEMORIES;
	static bool SHOW_USER_FISHERY_ZONE;
	static bool SHOW_USER_IMAGE_LAYER;

	static double S111_SREF;
	static double S111_LREF;
	static double S111_SHIGH;
	static double S111_Alpha;

	static bool APPLY_DATA_COVERAGE_SCALE;

	static float DISPLAY_SYMBOL_SCALE;

	// true: ���� ȭ���� �߽��� (����)
	// false: AREA ��ü ������ �߽��� (����)
	static bool AREA_SYMBOL_DYNAMIC_POSITION_MODE;

	static int INTEROPERABILITY_LEVEL; //DISTANCE_TAGS;

	// Show Text Placement
	static bool	SHOW_TEXT_PLACEMENT;

	// Show wreck/obstruction/rock's uncertainty
	static bool SHOW_UNCERTAINTY;

	// Under/Over scale �� �ɺ� ũ�� ���� Test
	static int T_APPLY_OVER_N_UNDER_SCALE;
	static int T_CURRENT_SCALE;

	// DETECTION ��� ����
	static bool DETECTION_MODE;


	static bool SIMPLIFIED_POINT_SYMBOL;
	static bool AUTOSELECTION_CATALOGUE;
	static bool S111_SHOW_NODATA;
	static bool Show_INFORM01; //inform01 ������ ǥ���ϰų� ����ϴ�
	
	static bool S111_THINNING;

	static bool USING_MTP;

public:
	//static std::int64_t GetOverGroup(int viewGroup);
	//static bool Save(std::wstring filePath);
	//static bool Open(std::wstring filePath);
};