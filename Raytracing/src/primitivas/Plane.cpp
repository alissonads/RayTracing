#include "Plane.h"
#include "..\raytracer\Ray.h"
#include "..\primitivas\Result.h"

Plane::Plane(RT::Vec3f &normal, float distance, AbsMaterial *material) :
	Primitive(material), 
	normal(normal), 
	distance(distance)
{}

RT::Vec3f Plane::GetNormalAt(RT::Vec3f &pos)
{
	return normal;
}

bool Plane::Intersect(Ray &ray, float &_distance, Result &result)
{
	float d = normal.Dot(ray.GetDirection());
	bool hit = false;
	float dst = _distance;

	if (d != 0)
	{
		dst = -(normal.Dot(ray.GetOrigin()) + distance) / d;
		
		if (dst > 0 && dst < _distance)
		{
			hit = true;
			_distance = dst;

			result.hit = hit;
		}
	}

	return hit;
}
