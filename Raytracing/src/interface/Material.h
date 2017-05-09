#ifndef	 __MATERIAL_H__
#define	 __MATERIAL_H__

#include <RTmath.h>

class Result;
class Ray;

class Material
{
public:
	virtual ~Material() {}

	virtual Material *Clone() const = 0;
	virtual RT::Vec3f Shade(Result &result) = 0;
	virtual RT::Vec3f AreaLightShade() = 0;
	virtual RT::Vec3f PathShade() = 0;
};

#endif //__MATERIAL_H__