#include "Raytracer.h"

Raytracer::Raytracer(HWND handle, HINSTANCE instance, unsigned int width, unsigned int height)
    : mHandle(handle), mInstance(instance), mWidth(width), mHeight(height)
{
    makeDIB();

}

void Raytracer::Run()
{
    const auto aspectRatio = 4.0 / 3.0;
    const int imageWidth = mWidth;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    auto viewportHeight = 2.0;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewportWidth, 0, 0);
    auto vertical = Vec3(0, viewportHeight, 0);
    auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

    for (int y = mHeight - 1; y >= 0; y--)
    {
        for (int x = 0; x < mWidth; x++)
        {
            auto u = double(x) / (imageWidth - 1);
            auto v = double(y) / (imageHeight - 1);

            Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            Color pixelColor = rayColor(r);
            setColor(x, y, pixelColor);
        }
    }
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

Color Raytracer::rayColor(const Ray& r)
{

    auto t = hitSphere(Point3(0, 0, -1), 0.5, r);

    if (t > 0.0)
    {
        Vec3 N = UnitVector(r.At(t) - Vec3(0, 0, -1));

        return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    Vec3 unitDirection = UnitVector(r.GetDirection());
    t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
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

void Raytracer::setColor(int u, int v, Color color)
{
    int writeColor = 0;

    auto r = color.e[0];
    auto g = color.e[1];
    auto b = color.e[2];

    int ir = static_cast<int>(255.999 * r);
    int ig = static_cast<int>(255.999 * g);
    int ib = static_cast<int>(255.999 * b);

    writeColor |= (ir << 16);
    writeColor |= (ig << 8);
    writeColor |= ib;

    mPixels[(v * mWidth) + u] = writeColor;

}

double Raytracer::hitSphere(const Point3& center, double radius, const Ray& r)
{
    Vec3 oc = r.mOrigin - center;

    auto a = r.mDirection.LengthSqaured();
    auto bHalf = Dot(oc, r.mDirection);
    auto c = oc.LengthSqaured() - radius * radius;
    auto discriminant = bHalf * bHalf - a * c;
    
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-bHalf - sqrt(discriminant)) / a;
    }
   
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
