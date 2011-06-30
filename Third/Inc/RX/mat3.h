/*
=================================================
mat3.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	30/04/2009
=================================================
*/

#ifndef __MAT3_H
#define __MAT3_H

#include <sstream>
#include "vec3.h"
#include "vec4.h"
#include "../Third/Inc/C3/C3_Math.h"

namespace RX
{
class mat3
{
	friend std::ostream &operator<<(std::ostream &out, mat3 m);
	friend std::istream &operator>>(std::istream &in, mat3 &m);

public:
	// Create/destroy
	mat3();
	mat3(float mat[9]);
	mat3(float m00, float m01, float m02,
		 float m10, float m11, float m12,
		 float m20, float m21, float m22);
	mat3(vec3 row1, vec3 row2, vec3 row3);
	~mat3();

	// Multiply matrices
	mat3 operator!() const;
	mat3 operator*(const mat3 &other) const;
	
	// Transform a vec3
	vec3 operator*(const vec3 &v) const;
	vec3 transform(const vec3 &v) const;

	// Create matrices
	void setView(vec3 position, vec3 target, vec3 up);
	void setOrthoProj(float x0, float x1, float y0, float y1, float z0, float z1);
	void setPerspProj(float hfov, float vfov, float nearPlane, float farPlane);
	void setViewport(int left, int bottom, int right, int top);
	void setRotate(float angle, vec3 axis);
	void setScale(vec3 scaleFactor);
	void setTranslate(vec3 translationFactor);
	void setIdentity();

	const float *floats() const
	{
		return &_m[0][0];
	}

public:
	float _m[3][3];

private:
	void fromC3Math(C3::Math::mat3 matrix)
	{
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				_m[i][j] = matrix[i][j];
		
	}
	C3::Math::mat3 toC3Math() const
	{
		C3::Math::mat3 matrix;
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				matrix[i][j] = _m[i][j];
		return matrix;
	}
};

std::ostream &operator<<(std::ostream &out, mat3 m);
std::istream &operator>>(std::istream &in, mat3 &m);

};

#endif // __mat3_H