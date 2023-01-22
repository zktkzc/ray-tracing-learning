#include <iostream>
#include "vec3.h"
#include "ray.h"

color ray_color(ray& r)
{
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
	vec3 x_vec = vec3(Image_Width, 0, 0);
	vec3 y_vec = vec3(0, Image_Height, 0);
	point3 low_left_corner = point3(origin - x_vec / 2 - y_vec / 2 - vec3(0, 0, 1));

	std::cout << "P3\n" << Image_Width << ' ' << Image_Height << "\n255\n";

	for (int j = Image_Height - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
		for (int i = 0; i < Image_Width; i++)
		{
			auto u = double(i) / (Image_Width - 1);
			auto v = double(j) / (Image_Height - 1);
			ray r(origin, low_left_corner + u * x_vec + v * y_vec - origin);
			color pixel = ray_color(r);
			pixel.write_color(std::cout);
		}
	}

	std::cerr << "\nDone!\n";

	return 0;
}