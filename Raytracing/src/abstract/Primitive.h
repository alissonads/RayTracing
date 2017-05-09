#ifndef	 __PRIMITIVE_H__
#define	 __PRIMITIVE_H__

#include <RTmath.h>
#include "..\abstract\AbsMaterial.h"

class Result;
class Ray;

class Primitive
{
protected:
	AbsMaterial *material;

public:
	Primitive(AbsMaterial *material);
	~Primitive();

	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos) = 0;
	virtual bool Intersect(Ray &ray, float &distance, Result &result) = 0;

	inline RT::Vec3f GetColor() { return material->GetColor(); }
	inline AbsMaterial *GetMaterial() const { return material; }
};

#endif //__PRIMITIVE_H__
