#pragma once

#include "SGeometry.h"

#include <cstdint>

class GeoPoint;
class ID2D1PathGeometry;
class ID2D1Factory1;
class Scaler;

class SCurve : public SGeometry
{
public:
	SCurve();
	virtual ~SCurve();
	
public:
	// CurveRecord ID (RCNM + RCID)
	std::int64_t m_id = 0;

	int m_numPoints = 0;

	GeoPoint *m_pPoints = nullptr;

	ID2D1PathGeometry* pGeometry = nullptr;

public:
	int GetRCID();

	int GetNumPoints();
	double GetX(int i);
	double GetY(int i);
	
//public:
//	void CreateD2Geometry(ID2D1Factory1* factory);
//
//	ID2D1PathGeometry* GetD2Geometry();
//	ID2D1PathGeometry* GetNewD2Geometry(ID2D1Factory1* factory, Scaler* scaler);
};
