#include "AbsMaterial.h"
#include "..\Util\Util.h"

AbsMaterial::AbsMaterial(RT::Vec3f &color) :
	color(color)
{
}

AbsMaterial::AbsMaterial(const AbsMaterial &other) :
	color(other.color)
{}

RT::Vec3f AbsMaterial::Shade(Result &result)
{
	return BLACK;
}
