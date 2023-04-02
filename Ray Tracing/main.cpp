#include <iostream>
#include "vec3.h"
#include "ray.h"

bool hit_sphere(const point3& center, double radius, ray& r)
{
	vec3 oc = r.GetOrigin() - center;
	auto a = dot(r.GetDirection(), r.GetDirection());
	auto b = 2.0 * dot(oc, r.GetDirection());
	auto c = dot(oc, oc) - radius * radius;
	auto discrimination = b * b - 4 * a * c; // 有几个解
	if (discrimination < 0) // 无解
	{
		return -1;
	}
	else
	{
		return ((-b - sqrt(discrimination)) / 2 * a); // 返回较小的t值
	}
}

color ray_color(ray& r)
{
	auto t = hit_sphere(point3(0, 0, -1), 0.6, r);
	if (t > 0.0) // 返回值>0
	{
		vec3 _N = unit_vector(r.at(t) - point3(0, 0, -1));
		return 0.5 * color(_N.x() + 1, _N.y() + 1, _N.z() + 1); // 将值从 -1~1 映射为 0~1
	}

	vec3 unit_dir = unit_vector(r.GetDirection());
	auto t = 0.5 * (unit_dir.y() + 1.0);
	return (1 - t) * color(1.0f) + t * color(0.3, 0.2, 1.0f);
}

int main()
{
	const int Image_Width = 400;
	const auto aspect_ratio = 16.0 / 9.0; // 宽高比
	const int Image_Height = static_cast<int>(Image_Width / aspect_ratio);

	// 找到左下角
	vec3 origin = vec3(0.0f);
	auto viewHeight = 2.0f; // 视口高度
	auto viewWidth = viewHeight * aspect_ratio; // 视口宽度
	auto focal_length = 1.0f; // 焦距

	vec3 horizontal = vec3(viewWidth, 0, 0);
	vec3 vertical = vec3(0, viewHeight, 0);
	point3 low_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	std::cout << "P3\n" << Image_Width << ' ' << Image_Height << "\n255\n";

	for (int j = Image_Height - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
		for (int i = 0; i < Image_Width; i++)
		{
			auto u = double(i) / (Image_Width - 1);
			auto v = double(j) / (Image_Height - 1);
			ray r(origin, low_left_corner + u * horizontal + v * vertical - origin);
			color pixel = ray_color(r);
			pixel.write_color(std::cout);
		}
	}

	std::cerr << "\nDone!\n";

	return 0;
}