#ifndef	 __RAYCASTING_H__
#define	 __RAYCASTING_H__

#include "..\interface\Tracer.h"

class Raycasting : public Tracer
{
public:
	virtual RT::Vec3f Raytracer(AbsScene &scene,
								Ray &ray, int depth);
};

#endif //__RAYCASTING_H__