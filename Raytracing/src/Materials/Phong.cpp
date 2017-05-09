#include "Phong.h"
#include "..\raytracer\Ray.h"
#include "..\Util\Util.h"
#include "..\primitivas\Result.h"
#include "..\brdf\Lambertian.h"
#include "..\brdf\GlossySpecular.h"
#include "..\abstract\AbsScene.h"
#include "..\Lights\AmbientLight.h"

Phong::Phong(RT::Vec3f &color,
			 float ambient,
			 float diffuse,
			 float specular,
			 float intensity) :
	AbsMaterial(color),
	ambient(new Lambertian(color, ambient)),
	diffuse(new Lambertian(color, diffuse)),
	specular(new GlossySpecular(color, specular)),
	intensity(intensity)
{
}

Phong::Phong(const Phong &other) :
	AbsMaterial(other),
	ambient((Lambertian*)other.ambient->Clone()),
	diffuse((Lambertian*)other.ambient->Clone()),
	specular((GlossySpecular*)other.ambient->Clone()),
	intensity(other.intensity)
{}

Phong::~Phong()
{
	delete ambient;
	delete diffuse;
	delete specular;
}

Material *Phong::Clone() const
{
	return new Phong(*this);
}

RT::Vec3f Phong::Shade(Result &result)
{
	RT::Vec3f wo = result.ray->GetDirection();
	RT::Vec3f L = ambient->RHO(result, wo) *
		result.scene->GetAmbientLight()->L(result);

	const std::vector<AbsLight*> &lights = result.scene->GetLights();

	for (AbsLight *l : lights)
	{
		RT::Vec3f wi = l->GetDirection(result);

		float dot = result.normal.Dot(wi);
		if (dot > 0.0f)
		{
			if(!l->InShadow(Ray(result.wHitPoint, wi),
								result))
				L += (diffuse->F(result, wi, wo) +
					specular->F(result, wi, wo)) *
					l->L(result) * dot;
		}
	}

	return L;
}

RT::Vec3f Phong::AreaLightShade()
{
	return RT::Vec3f();
}

RT::Vec3f Phong::PathShade()
{
	return RT::Vec3f();
}
