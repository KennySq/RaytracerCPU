#include "Raytracer.h"


Raytracer::Raytracer(HWND handle, HINSTANCE instance, unsigned int width, unsigned int height)
    : mHandle(handle), mInstance(instance), mWidth(width), mHeight(height)
{
    makeDIB();

}

void Raytracer::Run()
{
    HittableList world;

    world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));
    world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));

    const auto aspectRatio = 4.0 / 3.0;
    const int imageWidth = mWidth;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int sampleCount = 1;
    const int maxDepth = 50;

    Camera cam;

    for (int y = mHeight - 1; y >= 0; --y)
    {
        for (int x = 0; x < mWidth; ++x)
        {
            Color pixelColor(0, 0, 0);

            for (int s = 0; s < sampleCount; s++)
            {
                auto u = (x + RandDouble()) / (imageWidth - 1);
                auto v = (y + RandDouble()) / (imageHeight - 1);
                Ray r = cam.GetRay(u, v);

                pixelColor += rayColor(r, world, maxDepth);
            }

            setColor(x, y, pixelColor, sampleCount);
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

Color Raytracer::rayColor(const Ray& r, const Hittable& world, int depth)
{
    Hitrecord rec;

    if (depth <= 0)
    {
        return Color(0, 0, 0);
    }
    
    if (world.Hit(r, 0, INF, rec))
    {
        Point3 target = rec.p + rec.normal + RandomUnitSphere();
        return 0.5 * rayColor(Ray(rec.p, target - rec.p), world, depth - 1);
    }

    Vec3 unitDirection = UnitVector(r.GetDirection());
    auto t = 0.5 * (unitDirection.y() + 1.0);
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

void Raytracer::setColor(int u, int v, Color color, int SampleCount)
{
    int writeColor = 0;

    auto r = color.e[0];
    auto g = color.e[1];
    auto b = color.e[2];

    auto scale = 1.0 / SampleCount;

    r *= scale;
    g *= scale;
    b *= scale;

    int ir = static_cast<int>(255.999 * Clamp(r, 0.0, 0.999));
    int ig = static_cast<int>(255.999 * Clamp(g, 0.0, 0.999));
    int ib = static_cast<int>(255.999 * Clamp(b, 0.0, 0.999));

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
