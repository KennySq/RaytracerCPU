#pragma once
#include<cstdlib>
#include<cmath>
#include<limits>
#include<memory>
#include<random>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double DegreesToRadians(double degrees)
{
	return degrees * PI / 180.0;
}

inline double RandDouble()
{
	return rand() / (RAND_MAX + 1.0);
}

inline double RandDouble(double min, double max)
{
	return min + (max - min) * RandDouble();
}

inline double Clamp(double x, double min, double max)
{
	if (x < min)
	{
		return min;
	}
	if (x > max)
	{
		return max;
	}

	return x;

}

#include"Ray.h"
#include"vec3.h"