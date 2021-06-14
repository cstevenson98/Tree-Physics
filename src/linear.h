#pragma once

#include <math.h>
#include <stdio.h>

struct vect2f
{
	float x, y;

	// vect2f() 
	// : x(0.), y(0.) 
	// { }
	
	vect2f() 
	: x(0.), y(0.) 
	{ }
	
	vect2f(float _x, float _y) 
	{
		x = _x; y = _y;
	}

	void print()
	{
		printf("(%f, %f)\n", x, y);
	}
};

struct mat2f
{
	float e11, e12, e21, e22;

	void setRotation(float theta)
	{
		float sTh = sin(theta);
		float cTh = cos(theta);

		e11 = cTh; e12 = -sTh;
		e21 = sTh; e22 = cTh;
	}

	vect2f dot(vect2f v)
	{
		return {e11 * v.x + e12 * v.y, e21 * v.x + e22 * v.y};
	}
};
