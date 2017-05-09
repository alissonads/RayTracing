#pragma once
#include <stdlib.h>
#define INFINITE 1000000.0f
#define TRACEDEPTH 6

#define EPSILON 0.001f

#define FILE_NAME "raytrace.png"

#define RMASK 0x000000FF
#define GMASK 0x0000FF00
#define BMASK 0x00FF0000
#define AMASK 0xFF000000

#define RSHIFT 0
#define GSHIFT 8
#define BSHIFT 16
#define ASHIFT 24

#include <RTmath.h>

#define BLACK RT::Vec3f(0, 0, 0)
#define WHITE RT::Vec3f(1, 1, 1)
#define RED   RT::Vec3f(1, 0, 0)
#define GREEN RT::Vec3f(0, 1, 0)
#define BLUE  RT::Vec3f(0, 0, 1)

#define VERY_LOW  4
#define LOW       16
#define MEDIUM    64
#define HIGH      100
#define VERY_HIGH 144
#define ULTRA     256

#define INVPI 1.0 / RT_PI

inline int randInt() { return rand(); }

inline void setRandSeed(const int seed) { srand(seed); }

inline float randFloat() { return (float)randInt() / RAND_MAX; }

inline float randFloat(int l, float h) { return randFloat() * (h - l) + l; }

inline int randInt(int l, int h) { return (int)(randFloat(0, h - l + 1) + l); }
