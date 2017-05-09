#include "AbsLight.h"

AbsLight::AbsLight(bool shadows) :
	shadows(shadows)
{
}

AbsLight::AbsLight(const AbsLight &other) :
	shadows(other.shadows)
{}

RT::Vec3f AbsLight::L(Result & result)
{
	return RT::Vec3f();
}
