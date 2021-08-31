#include "Raytracer.h"

Raytracer::Raytracer(HWND handle, HINSTANCE instance, unsigned int width, unsigned int height)
    : mHandle(handle), mInstance(instance), mWidth(width), mHeight(height)
{
    makeDIB();

}

void Raytracer::ClearGradiant()
{
    for (int y = mHeight - 1; y >= 0; y--)
    {
        for (int x = 0; x < mWidth; x++)
        {
            int color = 0;
            auto r = double(x) / (mWidth - 1);
            auto g = double(y) / (mHeight - 1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            color |= (ir << 16);
            color |= (ig << 8);
            color |= ib;

            mPixels[(y * mWidth) + x] = color;
        }
    }
}

bool Raytracer::makeDIB()
{
    BITMAPINFO bitInfo{};

    bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitInfo.bmiHeader.biBitCount = 32;
    bitInfo.bmiHeader.biWidth = mWidth;
    bitInfo.bmiHeader.biHeight = mHeight;
    bitInfo.bmiHeader.biPlanes = 1;
    bitInfo.bmiHeader.biCompression = BI_RGB;
    
    HDC dc = GetDC(mHandle);
    mBitmap = CreateDIBSection(dc, &bitInfo, DIB_RGB_COLORS, reinterpret_cast<void**>(&mPixels), nullptr, 0);

    mMemoryDC = CreateCompatibleDC(dc);

    SelectObject(mMemoryDC, mBitmap);
    ReleaseDC(mHandle, dc);

    return true;
}

void Raytracer::ClearDIB()
{
    for (int y = mHeight-1; y > 0; y--)
    {
        for (int x = 0; x < mWidth; x++)
        {
            mPixels[(y * mWidth) + x] = 0x00ff0000;
        }
    }
}

void Raytracer::Release()
{
    DeleteDC(mMemoryDC);
    DeleteObject(mBitmap);
}
