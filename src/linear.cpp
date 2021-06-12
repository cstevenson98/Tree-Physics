#include "linear.h"

vect2f operator+(const vect2f &v1, const vect2f &v2)
{
	return { v1.x + v2.x, v1.y + v2.y };
}

vect2f operator*(const float &a, const vect2f &v)
{
	return { a * v.x, a * v.y };
}
