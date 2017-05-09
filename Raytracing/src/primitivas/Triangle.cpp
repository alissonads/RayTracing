#include "Triangle.h"
#include "..\primitivas\Result.h"
#include "..\raytracer\Ray.h"
#include "..\Util\Util.h"

Triangle::Triangle(RT::Vec3f &v1, 
				   RT::Vec3f &v2, 
				   RT::Vec3f &v3, 
				   AbsMaterial *material) :
		   Primitive(material),
		   v1(v1),
		   v2(v2),
		   v3(v3)
{
	normal = RT::vc3::Cross(v2 - v1, v3 - v1).Normalize();
}

Triangle::Triangle(RT::Vec3f v1,
		           RT::Vec3f v2,
		           RT::Vec3f v3,
				   RT::Vec3f normal,
				   AbsMaterial *material) :
		  Primitive(material),
		  v1(v1),
		  v2(v2),
		  v3(v3),
	      normal(normal)
{}

Triangle::Triangle(Triangle &other) :
	v1(other.v1),
	v2(other.v2),
	v3(other.v3),
	Primitive(other.material)
{}

RT::Vec3f Triangle::GetNormalAt(RT::Vec3f & pos)
{
	return normal;
}

bool Triangle::Intersect(Ray &ray, float &distance, Result &result)
{
	bool hit = true;
	RT::Vec3f a = v1 - v2;
	RT::Vec3f b = v1 - v3;
	RT::Vec3f c = ray.GetDirection();
	RT::Vec3f d = v1 - ray.GetOrigin();

	float m = b.y * c.z - c.y * b.z;
	float n = d.y * c.z - c.y * d.z;
	float p = b.y * d.z - d.y * b.z;
	float q = c.y * a.z - a.y * c.z;
	float s = a.y * b.z - b.y * a.z;

	float inv = 1.0f / (a.x * m + b.x * q + c.x * s);

	float e1 = d.x * m - b.x * n - c.x * p;
	float beta = e1 * inv;

	if (beta < 0.0f)
		hit = false;

	float r = a.y * d.z - d.y * a.z;
	float e2 = a.x * n + d.x * q + c.x * r;
	double gama = e2 * inv;

	if (gama < 0.0f)
		hit = false;

	if (beta + gama > 1.0f)
		hit = false;

	float e3 = a.x * p - b.x * r + d.x * s;
	float t = e3 * inv;

	if (t < 0.0f)
	{
		hit = false;
		distance = t;
	}

	if (hit)
	{
		result.hit = hit;
	}

	return hit;
}
