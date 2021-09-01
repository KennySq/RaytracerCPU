#pragma once
#include"Hittable.h"

#include<memory>
#include<vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable 
{
public:
	HittableList() {}
	HittableList(shared_ptr<Hittable> object) {  }

	void Clear() { mObjects.clear(); }
	void Add(shared_ptr<Hittable> object) { mObjects.push_back(object); }

	virtual bool Hit(const Ray& r, double tMin, double tMax, Hitrecord& rec) const override;



public:
	std::vector<std::shared_ptr<Hittable>> mObjects;


	// Hittable을(를) 통해 상속됨

};

