#include "PresentationScene.h"
#include "..\raytracer\Canvas.h"
#include "..\raytracer\Ray.h"
#include "..\abstract\Primitive.h"
#include "..\primitivas\Result.h"
#include "..\Lights\PointLight.h"
#include "..\primitivas\Plane.h"
#include "..\primitivas\Sphere.h"
#include "..\primitivas\Box.h"
#include "..\primitivas\Triangle.h"
#include "..\Camera\PinholeCamera.h"
#include "..\Camera\ThinLensCamera.h"
#include "..\Samples\Regular.h"
#include "..\Samples\Jittered.h"
#include "..\Samples\NRooks.h"
#include "..\Samples\Hammersley.h"
#include "..\Samples\Random.h"
#include "..\Samples\MultiJittered.h"
#include "..\Materials\Phong.h"
#include "..\Materials\ReflectMaterial.h"
#include "..\Lights\AmbientLight.h"
#include "..\Tracer\Raycasting.h"
#include "..\Materials\Reflect.h"

PresentationScene::PresentationScene(float zoom, int samples) :
	AbsScene(BLACK, 
		new AmbientLight(0.5f, 
			RT::Vec3f(1.0f, 1.0f, 1.0f)), 
		new Raycasting()),
	/*camera(new PinholeCamera(RT::Vec3f(-6.5f, -1.0f, -2.5f),
							 RT::Vec3f(-5.0f, -1.0f, 0.0f),
							 RT::Vec3f(0, 1, 0),
							 8,
							 zoom)),*/
	camera(new ThinLensCamera(RT::Vec3f(-6.5f, -1.0f, -2.5f),
							  RT::Vec3f(-5.0f, -1.0f, 0.0f),
							  RT::Vec3f(0, 1, 0),
							  12, 6.5f, 0.25f, zoom,
							  new MultiJittered(samples))),
	canvas(new Canvas(1920, 1080))
{
	canvas->SetSampler(
		new MultiJittered(samples)
		);
	Init();
}

PresentationScene::~PresentationScene()
{
	delete canvas;
	delete camera;
}

void PresentationScene::Init()
{
	//chão
	objects.push_back(new Plane(RT::Vec3f(0, 1, 0), 3.0f,
		new Phong(RT::Vec3f(0.4f, 0.3f, 0.3f), 0.2f, 0.7f, 0.5f, 20.0f)));

	//parede fundo
	objects.push_back(new Plane(RT::Vec3f(0, 0, -1), 22.4f,
		new Phong(RT::Vec3f(0.6f, 0.5f, 0.5f), 0.2f, 1.0f, 0.8f, 20.0f)));

	//parede esquerda
	objects.push_back(new Plane(RT::Vec3f(1, 0, 0), 12.0f,
		new Phong(RT::Vec3f(0.5f, 0.5f, 0.6f), 0.2f, 1.0f, 0.8f, 20.0f)));
	
	//parede direita
	objects.push_back(new Plane(RT::Vec3f(-1, 0, 0), 12.0f,
		new Phong(RT::Vec3f(0.5f, 0.5f, 0.6f), 0.2f, 1.0f, 0.8f, 20.0f)));

	//teto
	objects.push_back(new Plane(RT::Vec3f(0, -1, 0), 5.2f,
		new Phong(RT::Vec3f(0.7f, 0.7f, 0.7f), 0.2f, 1.0f, 0.8f, 20.0f)));
    
	//esfera de cima da caixa
	objects.push_back(new Sphere(RT::Vec3f(1.5f, 0.5f, 4.0f), 4.0f,
		new ReflectMaterial(RT::Vec3f(0.6f, 0.6f, 0.6f), 0.2f, 0.7f, 0.8f, 20.f, 0.1f)));

	//esfera grande
	objects.push_back(new Sphere(RT::Vec3f(-5.0f, -0.8f, 4.0f), 5.0f,
		new ReflectMaterial(RT::Vec3f(0.7f, 0.7f, 1.0f), 0.2f, 0.7f, 0.8f, 20.0f, 0.1f)));

	objects.push_back(new Box(RT::Vec3f(0.0f, -3.0f, 2.5f), RT::Vec3f(3.0f, 1.5f, 3.0f),
		new Phong(RT::Vec3f(0.7f, 0.7f, 1.0f), 0.2f, 0.7f, 0.2f, 20.0f)));

	//luzes
	//RT::Vec3f yellow = RT::Vec3f(1.0f, 1.0f, 1.0f);
	lights.push_back(new PointLight(RT::Vec3f(4, 4, -4), RT::Vec3f(0.6f, 0.6f, 0.7f)));
	lights.push_back(new PointLight(RT::Vec3f(2, 5, -2), RT::Vec3f(0.5f, 0.8f, 0.8f)));
}

void PresentationScene::Render()
{
	camera->Render(*this);
	canvas->Save();
}

Result PresentationScene::Hit(Ray &ray)
{
	Result result(this);

	float dist = INFINITE;

	Primitive *prim = nullptr;

	for (Primitive *obj : objects)
	{
		if (obj->Intersect(ray, dist, result))
		{
			//result.hit = true;
			result.material = obj->GetMaterial();
			prim = obj;
		}
	}

	//ponto de intersecção
	RT::Vec3f pi = ray.IntersectionPoint(dist);

	result.lHitPoint = pi;
	result.wHitPoint = pi;
	result.normal = prim->GetNormalAt(pi);

	return result;
}

bool PresentationScene::ShadowHit(Ray &ray, float dist)
{
	Result result(this);

	for (Primitive *obj : objects)
	{
		if (obj->Intersect(ray, dist, result))
			return true;
	}

	return false;
}