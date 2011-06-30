/*
=================================================
vec4.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	13/05/2009
=================================================
*/

#ifndef __VEC4_H
#define __VEC4_H

#include <iostream>
#include <cmath>
#include "vec3.h"

namespace RX
{

class vec4
{
public:
	// Create/destroy
	vec4();
	vec4(float x1, float y1, float z1, float w1);
	vec4(const vec3 &v, float w); 
	vec4(const vec3 &v);

	// Norm & Squared norm
	const inline float norm() const { return sqrt(x*x + y*y + z*z + w*w); }
	const inline float sqrNorm() const { return x*x + y*y + z*z + w*w; }

	// Normalize vector
	inline void normalize() {
		float norm1 = norm();
		if(norm1) {
			x /= norm1; y /= norm1; z /= norm1; w /= norm1;
		}
	}
	inline vec4 normalized() const {
	   vec4 aux = *this;
	   aux.normalize();
	   return aux;
	}

	float operator[](int id) const;

	// Operators

	// Dot product
	float operator*(const vec4 &v) const;

	// Addition/Subtraction
	vec4 operator+(const vec4 &v) const;
	vec4 operator+=(const vec4 &v);
	vec4 operator-(const vec4 &v) const;
	vec4 operator-=(const vec4 &v);

	// Transform by scalar
	vec4 operator*=(const float &f);
	vec4 operator/=(const float &f);
	vec4 operator*(const float &f);
	vec4 operator/(const float &f);

	bool operator==(const vec4 &v);

	// Get floats
	float const *floats() const { return &x; }

public:
	float x, y, z, w;
};

};

#endif // __vec4_H

