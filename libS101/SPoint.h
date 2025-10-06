#pragma once

#include "SGeometry.h"
#include "GeoPoint.h"
#include "Point.h"

class SPoint : public SGeometry
{
public:
	SPoint();
	SPoint(double _x, double _y);
	virtual ~SPoint();

public:
	GeoPoint m_point;	
	
	// �޷θ� �Ҵ�� ȸ���� Pointϱ� ���� CPoint�迭�� ������ �ִ´�.
	Point   m_vPoint;

public:
	void SetPoint(double _x, double _y);
};