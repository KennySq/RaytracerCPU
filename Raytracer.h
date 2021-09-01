#pragma once


#include"vec3.h"

#include"HittableList.h"
#include"Sphere.h"

#include"Camera.h"
#include<Windows.h>

class Raytracer
{
	
public:
	Raytracer(HWND handle, HINSTANCE instance, unsigned int width, unsigned int height);
	
	void Run();

	// Raytracer methods;
	void ClearGradiant();

	// Win32 DIB methods
	void ClearDIB();
	HDC GetMemoryDC() const { return mMemoryDC; }
	void Release();
private:

	Color rayColor(const Ray& r, const Hittable& world, int depth);

	bool makeDIB();

	void setColor(int u, int v, Color color, int SampleCount);

	double hitSphere(const Point3& center, double radius, const Ray& r);

	unsigned int mWidth;
	unsigned int mHeight;

	HWND mHandle;
	HBITMAP mBitmap;

	HDC mMemoryDC;
	LPDWORD mPixels;

	HINSTANCE mInstance;
};

