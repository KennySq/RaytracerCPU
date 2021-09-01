#include "HittableList.h"



bool HittableList::Hit(const Ray& r, double tMin, double tMax, Hitrecord& rec) const
{
    Hitrecord tempRec;
    bool bHitSomething = false;
    auto ClosestSoFar = tMax;

    for (const auto& object : mObjects)
    {
        if (object->Hit(r, tMin, tMax, tempRec))
        {
            bHitSomething = true;
            ClosestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return bHitSomething;
}
