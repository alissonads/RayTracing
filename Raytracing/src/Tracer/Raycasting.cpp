#include "Raycasting.h"
#include "..\abstract\AbsScene.h"
#include "..\raytracer\Ray.h"
#include "..\primitivas\Result.h"
#include "..\abstract\AbsMaterial.h"
#include "..\Util\Util.h"

RT::Vec3f Raycasting::Raytracer(AbsScene &scene,
								Ray &ray, int depth)
{
	if (depth > TRACEDEPTH)
	{
		return BLACK;
	}

	Result result(scene.Hit(ray));//Result result(scene.Hit(ray));

	if (result.hit || result.hit == EOF)
	{
		result.depth = depth;
		result.ray = &ray;
		return result.material->Shade(result);
	}

	return scene.GetBackground();
}
