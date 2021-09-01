#pragma once
#include"Common.h"

class Camera
{
public:
	Camera() {
		auto aspectRatio = 4.0 / 3.0;
		auto viewportHeight = 2.0;
		auto viewportWidth = aspectRatio * viewportHeight;
		auto focalLength = 1.0;

		mOrigin = Point3(0, 0, 0);
		mHorizontal = Vec3(viewportWidth, 0, 0);
		mVertical = Vec3(0, viewportHeight, 0);
		mLowerLeft = mOrigin - mHorizontal / 2 - mVertical / 2 - Vec3(0, 0, focalLength);
	}

	Ray GetRay(double u, double v) const
	{
		return Ray(mOrigin, mLowerLeft + u * mHorizontal + v * mVertical - mOrigin);
	}

private:
	Point3 mOrigin;
	Point3 mLowerLeft;
	Vec3 mHorizontal;
	Vec3 mVertical;

};

