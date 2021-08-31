#pragma once
#include<Windows.h>

class Raytracer
{
	
public:
	Raytracer(HWND handle, HINSTANCE instance, unsigned int width, unsigned int height);
	
	// Raytracer methods;
	void ClearGradiant();

	// Win32 DIB methods
	void ClearDIB();
	HDC GetMemoryDC() const { return mMemoryDC; }
	void Release();
private:
	bool makeDIB();




	unsigned int mWidth;
	unsigned int mHeight;

	HWND mHandle;
	HBITMAP mBitmap;

	HDC mMemoryDC;
	LPDWORD mPixels;

	HINSTANCE mInstance;

};

