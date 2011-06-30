/*
=================================================
vec3d.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	06/03/2009
=================================================
*/

#ifndef __VEC3D_H
#define __VEC3D_H

#include <iostream>
#include <fstream>
#include <cmath>

// provisory
#include <C3_Math.h>

namespace RX
{
class color;
class vec4;

class vec3d
{
	friend std::ostream &operator<<(std::ostream &out, vec3d v);
	friend std::istream &operator>>(std::istream &in, vec3d &v);

public:
	// Static members
	static const vec3d unitX, unitY, unitZ;
	static const vec3d zero, one;

	// Create/destroy
	vec3d(double x1, double y1, double z1);
	vec3d(const vec3d &v);
	vec3d(const vec4 &v);
	vec3d(const color &c);
	vec3d();

	// provisory
	C3::Math::vec3 toC3Math() 
	{
		return C3::Math::vec3(x, y, z);
	}
	void fromC3Math(C3::Math::vec3 v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	double operator[](int id) const;

	// Norm & Squared norm
	const inline double norm() const { return sqrt(x*x + y*y + z*z); }
	const inline double sqrNorm() const { return x*x + y*y + z*z; }

	// Normalize vector
	inline void normalize() {
		double norm1 = norm();
		if(norm1) x /= norm1; y /= norm1; z /= norm1;
	}

	inline vec3d normalized() const {
	   vec3d aux = *this;
	   aux.normalize();
	   return aux;
	}

	// Dot product
	double operator*(const vec3d &v) const;
	// Cross product
	vec3d operator^(const vec3d &v) const;

	// Addition/Subtraction/Copy
	vec3d operator+(const vec3d &v) const;
	vec3d operator+=(const vec3d &v);
	vec3d operator-(const vec3d &v) const;
	vec3d operator-=(const vec3d &v);
	vec3d operator=(const vec3d &v);

	// Multiplication by scalar
	vec3d operator*=(const double &f);

	// Division by scalar
	vec3d operator/=(const double &f);
	vec3d operator/(const double &f);

	// Get doubles
	double const *doubles() const { return &x; }

public:
	double x, y, z;

};

vec3d operator*(const double &f, const vec3d &v);
vec3d operator*(const vec3d &v, const double &f);

std::ostream &operator<<(std::ostream &out, vec3d v);
std::istream &operator>>(std::istream &in, vec3d &v);
};

#endif // __VEC3D_H

