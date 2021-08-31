#pragma once
#include"vec3.h"

class Ray
{
public:
	Ray() {}
	Ray(const Point3& origin, const Vec3& direction)
		: mOrigin(origin), mDirection(direction)
	{}

	Point3 GetOrigin() const { return mOrigin; }
	Vec3 GetDirection() const { return mDirection; }

	Point3 At(double t) const 
	{
		return mOrigin + t * mDirection;
	}

public:
	Point3 mOrigin;
	Vec3 mDirection;
};

