#include <iostream>
#include "Scenes\Raytracer.h"
#include "Scenes\PresentationScene.h"
#include "Scenes\RefractionScene.h"
#include "interface\Scene.h"
#include "Util\Util.h"
#include <time.h>

#include <SDL.h>

int main(int argc, char **argv)
{
	//Raytracer raytracer;
	
	PresentationScene(1.5f, MEDIUM).Render();

	//setRandSeed(time(NULL));
	//std::cout << randFloat() << std::endl;

	system("pause");
	return 0;
}