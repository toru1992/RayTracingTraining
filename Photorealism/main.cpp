// Photorealism.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Vec3.h"
#include "Ray.h"
#include "Image.h"
#include "Sphere.h"
#include "Camera.h"

// Vec3のテスト
void TestVec3()
{
    std::cout << "---TestVec3---" << std::endl;

    Vec3 v1(1, 2, 3), v2(4, 5, 6);

    std::cout << v1 + v2 << std::endl;
    std::cout << v1 - v2 << std::endl;
    std::cout << v1 * v2 << std::endl;
    std::cout << v1 / v2 << std::endl;

    std::cout << v1 + 1 << std::endl;
    std::cout << v1 - 1 << std::endl;
    std::cout << v1 * 2 << std::endl;
    std::cout << v1 / 2 << std::endl;

    std::cout << Dot(v1, v2) << std::endl;
    std::cout << Cross(v1, v2) << std::endl;

    std::cout << v1.length() << std::endl;
    std::cout << v1.length2() << std::endl;

    std::cout << "------" << std::endl;
}
// Rayのテスト
void TestRay()
{
    std::cout << "---TestRay---" << std::endl;
    
    Ray r(Vec3(0, 0, 0), Vec3(0, 0, 1));

    std::cout << r << std::endl;
    std::cout << r(10) << std::endl;

    std::cout << "------" << std::endl;
}

// Imageのテスト
void TestImage()
{
    std::cout << "---TestImage---" << std::endl;

    Image image(512, 512);

    for (int w = 0; w < image.width; ++w)
    {
        for (int h = 0; h < image.height; ++h)
        {
            image.SetPixel(w, h, Vec3(w / double(image.width), h / double(image.height), 1.0));
        }
    }
    image.OutputPpm("image_test.ppm");

    std::cout << "------" << std::endl;
}

// Sphereテスト
void TestSphere()
{
    std::cout << "---TestSphere---" << std::endl;

    Sphere s(Vec3(0, 0, 0), 1);
    Ray ray(Vec3(0, 0, -3), Vec3(0, 0, 1));

    Hit res;
    if (s.intersect(ray, res))
    {
        std::cout << res.hitPos << std::endl;
    }

    std::cout << "------" << std::endl;
}

// PinholeCameraテスト
void TestPinholeCamera()
{
    std::cout << "---TestPinholeCamera---" << std::endl;
    
    Image image(512, 512);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

    for (int w = 0 ; w < image.width ; ++w)
    {
        for (int h = 0; h < image.height; ++h)
        {
            double u = (2.0 * w - image.width) / image.height;
            double v = (2.0 * h - image.height) / image.height;
        
            Ray ray = cam.GetRay(-u, -v);

            Vec3 col = (ray.direction + 1.0) / 2.0;

            image.SetPixel(w, h, col);
        }
    }

    image.OutputPpm("image_test.ppm");

    std::cout << "------" << std::endl;
}

// メインシーン
void MainScene()
{
    Image image(256, 256);

    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1.0);

    Sphere sphere(Vec3(0, 0, -3), 1);

    for (int w = 0; w < image.width; ++w)
    {
        for (int h = 0; h < image.height; ++h)
        {
            double u = (2.0 * w - image.width) / image.height;
            double v = (2.0 * h - image.height) / image.height;

            Ray ray = cam.GetRay(-u, -v);

            Vec3 col;
            Hit res;
            if (sphere.intersect(ray, res))
            {
                image.SetPixel(w, h, (res.hitNormal + 1.0) / 2.0);
            }
            else
            {
                image.SetPixel(w, h, Vec3(0, 0, 0));
            }
        }
    }

    image.OutputPpm("image_test.ppm");
}

int main()
{
    // Vec3のテスト
    //TestVec3();
    // Rayのテスト
    //TestRay();
    // Imageのテスト
    //TestImage();
    // Sphereのテスト
    //TestSphere();
    // PinholeCameraテスト
    //TestPinholeCamera();
    // メインシーン
    MainScene();

    return 0;
}

