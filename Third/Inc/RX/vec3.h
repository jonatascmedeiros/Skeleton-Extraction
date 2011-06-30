/*
=================================================
vec3.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	06/03/2009
=================================================
*/

#ifndef __VEC3_H
#define __VEC3_H

#include <iostream>
#include <fstream>
#include <cmath>

namespace RX
{
class color;
class vec4;

class vec3
{
	friend std::ostream &operator<<(std::ostream &out, vec3 v);
	friend std::istream &operator>>(std::istream &in, vec3 &v);

public:
	// Static members
	static const vec3 unitX, unitY, unitZ;
	static const vec3 zero, one;

	// Create/destroy
	vec3(float x1, float y1, float z1);
	vec3(const float *v);
	vec3(const vec3 &v);
	vec3(const vec4 &v);
	vec3(const color &c);
	vec3();

	float operator[](int id) const;

	// Norm & Squared norm
	const inline float norm() const { return sqrt(x*x + y*y + z*z); }
	const inline float sqrNorm() const { return x*x + y*y + z*z; }

	// Normalize vector
	inline void normalize() {
		float norm1 = norm();
		if(norm1) x /= norm1; y /= norm1; z /= norm1;
	}

	inline vec3 normalized() const {
	   vec3 aux = *this;
	   aux.normalize();
	   return aux;
	}

	// Dot product
	float operator*(const vec3 &v) const;
	// Cross product
	vec3 operator^(const vec3 &v) const;

	// Addition/Subtraction/Copy
	vec3 operator+(const vec3 &v) const;
	vec3 operator+=(const vec3 &v);
	vec3 operator-(const vec3 &v) const;
	vec3 operator-=(const vec3 &v);
	vec3 operator=(const vec3 &v);

	// Multiplication by scalar
	vec3 operator*=(const float &f);

	// Division by scalar
	vec3 operator/=(const float &f);
	vec3 operator/(const float &f);

	// Get floats
	float const *floats() const { return &x; }

public:
	float x, y, z;

};

vec3 operator*(const float &f, const vec3 &v);
vec3 operator*(const vec3 &v, const float &f);

std::ostream &operator<<(std::ostream &out, vec3 v);
std::istream &operator>>(std::istream &in, vec3 &v);
};

#endif // __vec3_H

