#include "Primitive.h"
#include "..\raytracer\_Material.h"
#include "..\raytracer\Ray.h"

Primitive::Primitive(AbsMaterial *material) :
	material(material)
{}

Primitive::~Primitive()
{
	if (material)
	{
		delete material;
		material = nullptr;
	}
}

