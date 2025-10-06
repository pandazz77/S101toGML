#pragma once
#include "Geometry.h"
#include "Point.h"
#include <unordered_map>

class SSurface;
class Symbol;
class R_FeatureRecord;
class SENC_SymbolFill;
//class Point;

class SGeometry : public Geometry
{
public:
	SGeometry();
	virtual ~SGeometry();

public:
	static int sizeOfPoint;

	// �޷θ� �Ҵ�� ȸ���� �ּ�ȭ �ϱ� ���� Point�迭�� ������ �ִ´�.
	static Point   *viewPoints;

	// 1 : Point 
	// 2 : Curve
	// 3 : Surface
	// 4 : Multi Point (Sounding)
	int type;

	R_FeatureRecord* m_pFeature = nullptr;

public:
	// 1 : Point 
	// 2 : Curve
	// 3 : Surface
	// 4 : Multi Point (Sounding)
	virtual int GetType() {	return 0; }

	bool IsPoint();
	bool IsCurve();
	bool IsSurface();
	bool IsMultiPoint();
};
