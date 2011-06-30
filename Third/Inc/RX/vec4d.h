/*
=================================================
vec4.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	13/05/2009
=================================================
*/

#ifndef __VEC4D_H
#define __VEC4D_H

#include <iostream>
#include <cmath>
#include "vec3d.h"

namespace RX
{

class vec4
{
public:
	// Create/destroy
	vec4d();
	vec4d(double x1, double y1, double z1, double w1);
	vec4d(const vec3d &v, double w); 
	vec4d(const vec3d &v);

	// Norm & Squared norm
	const inline double norm() const { return sqrt(x*x + y*y + z*z + w*w); }
	const inline double sqrNorm() const { return x*x + y*y + z*z + w*w; }

	// Normalize vector
	inline void normalize() {
		double norm1 = norm();
		if(norm1) {
			x /= norm1; y /= norm1; z /= norm1; w /= norm1;
		}
	}
	inline vec4d normalized() const {
	   vec4d aux = *this;
	   aux.normalize();
	   return aux;
	}

	double operator[](int id) const;

	// Operators

	// Dot product
	double operator*(const vec4d &v) const;

	// Addition/Subtraction
	vec4d operator+(const vec4d &v) const;
	vec4d operator+=(const vec4d &v);
	vec4d operator-(const vec4d &v) const;
	vec4d operator-=(const vec4d &v);

	// Transform by scalar
	vec4d operator*=(const double &f);
	vec4d operator/=(const double &f);
	vec4d operator*(const double &f);
	vec4d operator/(const double &f);

	bool operator==(const vec4 &v);

	// Get doubles
	double const *doubles() const { return &x; }

public:
	double x, y, z, w;
};

};

#endif // __vec4_H

