#pragma once
#include"Ray.h"
struct Hitrecord
{
	Point3 p;
	Vec3 normal;
	double t;
	bool bFront;

	inline void SetFaceNormal(const Ray& r, const Vec3& outward)
	{
		bFront = Dot(r.mDirection, outward) < 0;
		normal = bFront ? outward : -outward;
	}
};

class Hittable
{
public:
	virtual bool Hit(const Ray& r, double tMin, double tMax, Hitrecord& rec) const = 0;
};