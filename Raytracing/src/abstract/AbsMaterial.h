#ifndef	 __ABS_MATERIAL_H__
#define	 __ABS_MATERIAL_H__

#include "..\interface\Material.h"

class AbsMaterial : public Material
{
protected:
	RT::Vec3f color;

public:
	AbsMaterial(RT::Vec3f &color);
	AbsMaterial(const AbsMaterial &other);

	inline const RT::Vec3f &GetColor() const { return color; }

	virtual Material *Clone() const = 0;
	virtual RT::Vec3f Shade(Result &resultt);
	virtual RT::Vec3f AreaLightShade() = 0;
	virtual RT::Vec3f PathShade() = 0;
};

#endif //__ABS_MATERIAL_H__