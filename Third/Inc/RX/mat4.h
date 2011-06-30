/*
=================================================
mat4.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	30/04/2009
=================================================
*/

#ifndef __MAT4_H
#define __MAT4_H

#include <sstream>
#include "vec3.h"
#include "vec4.h"
#include "../Third/Inc/C3/C3_Math.h"

namespace RX
{
class mat4
{
	friend std::ostream &operator<<(std::ostream &out, mat4 m);
	friend std::istream &operator>>(std::istream &in, mat4 &m);

public:
	// Create/destroy
	mat4();
	mat4(float mat[16]);
	mat4(vec4 row1, vec4 row2, vec4 row3, vec4 row4);
	mat4(float m00, float m01, float m02, float m03,
		 float m10, float m11, float m12, float m13,
		 float m20, float m21, float m22, float m23,
		 float m30, float m31, float m32, float m33);

	~mat4();

	// Operations
	mat4 operator!() const;
	mat4 operator*(const mat4 &other) const;
	mat4 operator+=(const mat4 &other);
	mat4 operator-=(const mat4 &other);

	// Transform a vec4
	vec4 operator*(const vec4 &v) const;
	vec4 transform(const vec4 &v) const;

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
	float _m[4][4];

private:
	void fromC3Math(C3::Math::mat4 matrix)
	{
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < 4; ++j)
				_m[i][j] = matrix[i][j];
		
	}
	C3::Math::mat4 toC3Math() const
	{
		C3::Math::mat4 matrix;
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < 4; ++j)
				matrix[i][j] = _m[i][j];
		return matrix;
	}
};

std::ostream &operator<<(std::ostream &out, mat4 m);
std::istream &operator>>(std::istream &in, mat4 &m);

};

#endif // __MAT4_H