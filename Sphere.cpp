#include "Sphere.h"

bool Sphere::Hit(const Ray& r, double tMin, double tMax, Hitrecord& rec) const
{
	Vec3 oc = r.mOrigin - mCenter;
	auto a = r.mDirection.LengthSqaured();
	auto bHalf = Dot(oc, r.mDirection);
	auto c = oc.LengthSqaured() - mRadius * mRadius;

	auto discriminant = bHalf * bHalf - a * c;

	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	auto root = (-bHalf - sqrtd) / a;
	if (root < tMin || tMax < root)
	{
		root = (-bHalf + sqrtd) / a;
		if (root < tMin || tMax < root)
		{
			return false;
		}
	}

	rec.t = root;
	rec.p = r.At(rec.t);

	Vec3 outward = (rec.p - mCenter) / mRadius;
	rec.SetFaceNormal(r, outward);

	return true;
}
