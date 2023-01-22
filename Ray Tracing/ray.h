#pragma once
#include "vec3.h"

class ray
{
public:
	ray() {};
	ray(const point3& _orig, const vec3& _dir) : orig(_orig), dir(_dir) {};

	point3 GetOrigin()
	{
		return orig;
	}

	vec3 GetDirection()
	{
		return dir;
	}

	point3 at(double t) const
	{
		return orig + t * dir; // 获取到线上的一个点
	}

private:
	point3 orig;
	vec3 dir;
};