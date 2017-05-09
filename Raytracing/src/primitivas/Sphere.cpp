#include "Sphere.h"
#include "..\primitivas\Result.h"
#include "..\raytracer\Ray.h"

Sphere::Sphere(RT::Vec3f &pos, 
			   float r, 
			   AbsMaterial *material) :
	Primitive(material), 
	center(pos), 
	radius(r)
{}

RT::Vec3f Sphere::GetNormalAt(RT::Vec3f &pos)
{
	return (pos - center).Normalize();
}

bool Sphere::Intersect(Ray &ray, float &distance, Result &result)
{
	RT::Vec3f v = ray.GetOrigin() - center;

	float b = -v.Dot(ray.GetDirection());
	float det = (b * b) - v.Dot(v) + radius;
	int hit = false;

	if (det > 0)
	{
		det = sqrtf(det);

		float i1 = b - det;
		float i2 = b + det;

		if (i2 > 0)
		{
			if (i1 < 0)
			{
				if (i2 < distance)
				{
					hit = EOF;
					distance = i2;

					result.hit = hit;
					result.wHitPoint = ray.IntersectionPoint(distance);
					result.lHitPoint = result.wHitPoint;
					result.normal = GetNormalAt(result.wHitPoint);
				}
			}
			else
			{
				if (i1 < distance)
				{
					hit = true;
					distance = i1;

					result.hit = hit;
				}
			}
		}
	}

	return (hit == true || hit == EOF);
}
