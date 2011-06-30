/*
=================================================
vec2.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	06/03/2009
=================================================
*/

#ifndef __VEC2_H
#define __VEC2_H

#include <iostream>
#include "Mathematics.h"

namespace RX
{

class vec2
{
public:
	// Constructors
	vec2(float x1, float y1);
	vec2();

	// Norm & Squared norm
	const inline float norm() const { return sqrt(x*x + y*y); }
	const inline float sqrNorm() const { return x*x + y*y; }

	// Normalize vector
	inline void normalize() {
		float n = norm();
		if(n) {
			x /= n; 
			y /= n;
		}
	}

	// Addition/Subtraction
	vec2 operator+(const vec2 &v) const;
	vec2 operator+=(const vec2 &v);
	vec2 operator-(const vec2 &v) const;
	vec2 operator-=(const vec2 &v);


	float *floats() {
		f[0] = x; f[1] = y;
		return f;
	}

	float x, y;

private:
	float f[2];

};

};

#endif // __vec2_H