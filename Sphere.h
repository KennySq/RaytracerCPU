#pragma once

#include"Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere() {}
	Sphere(Point3 center, double radius) : mCenter(center), mRadius(radius) {}

	virtual bool Hit(const Ray& r, double tMin, double tMax, Hitrecord& rec) const override;


public:
	Point3 mCenter;
	double mRadius;

};

