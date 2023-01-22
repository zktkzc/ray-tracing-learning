#pragma once

#include <cmath>
#include <iostream>


// ������
class vec3
{
public:
	vec3() : e{ 0,0,0 } {};
	vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {};
	vec3(double e0) : e{ e0, e0, e0 } {};

	// ȡ����Ԫ��
	double x() { return e[0]; }
	double y() { return e[1]; }
	double z() { return e[2]; }

	// ����
	vec3 operator-() { return vec3(-e[0], -e[1], -e[2]); };
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }; // ����ͨ������ֱ�Ӹ�������Ԫ��

	vec3& operator+= (const vec3& v)
	{
		this->e[0] += v.e[0];
		this->e[1] += v.e[1];
		this->e[2] += v.e[2];
		return *this; // ֱ�ӷ����������
	}

	vec3& operator*=(const double& t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(const double& t)
	{
		return *this *= (1 / t);
	}

	double length_squard() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	double length() const // const �����˺������ú�����һ��ֻ����Ա�����������޸ĳ�Ա���� // ע�⣺���ܷ��غ����ڲ��ֲ�����������
	{
		return sqrt(length_squard()); // ���������ص�������ʱ������Ҫ���ؿ��޸ĵ���ֵ
	}

	void write_color(std::ostream& out)
	{
		out << static_cast<int>(255.99 * e[0]) << ' '
			<< static_cast<int>(255.99 * e[1]) << ' '
			<< static_cast<int>(255.99 * e[2]) << '\n';
	}

public:
	double e[3]; // xyz
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t)
{
	return t * v;
}

inline vec3 operator/(const vec3& v, double t)
{
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) // ����ֵ���ܷ������ã������Ǿ�̬����
{
	return vec3(
		u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]
	);
}

inline vec3 unit_vector(const vec3& v)
{
	return v / v.length();
}