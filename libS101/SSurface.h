#pragma once
#include "SGeometry.h"
#include "SCurveHasOrient.h"
#include "Point.h"

class Scaler;
class GeoPoint;
class MBR;

class SSurface : public SGeometry
{
public:
	SSurface();
	SSurface(MBR* mbr);
	SSurface(std::vector<Point>& points, std::vector<int> parts);
	virtual ~SSurface();
	
	// Area ��ǥ
	int m_numParts = 0;
	int	m_numPoints = 0;
	int* m_pParts = nullptr;
	GeoPoint* m_pPoints = nullptr;
	GeoPoint* m_centerPoint = nullptr;
	
	// Curve ��ǥ
	std::list<SCurveHasOrient> m_listCurveLink;
};