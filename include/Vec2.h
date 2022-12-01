#ifndef VEC2_H
#define VEC2_H
#define PI 3.1415
#include <cmath>
#if defined (_WIN64) || defined (_WIN32)
#include "SDL2/SDL.h"
#else
#include <SDL2/SDL.h>
#endif
#include <string>
#include <iostream>
class Vec2{
public:
	float x;
	float y;
	float Magnitude();
	Vec2 Rotate(float angulo);
	Vec2 operator +(Vec2 const& vect);
	Vec2 operator -(Vec2 const& vect);
	Vec2 operator *(Vec2 const& vect);
	Vec2 operator* (float const& esc);
	Vec2 operator/ (float d) const;
	void operator+=(Vec2 b);
	Vec2(float x,float y);
	Vec2 Normalizado();
	float Inclinacao();
	Vec2();

};
#endif

