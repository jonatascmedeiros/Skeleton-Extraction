#pragma once

#define ERROR_TOLERANCE 1e-6

#include <RX/vec3.h>
#include <RX/mat4.h>

class Quaternion
{
public:
	

	Quaternion(void) : x(0),y(0),z(0),w(1) {}
	Quaternion(const float newX,const float newY,const float newZ,const float newW);
	Quaternion(RX::vec3 Axis,float Angle);

	Quaternion              &operator () (const float newX,const float newY,const float newZ);
	Quaternion              &operator () (const float newX,const float newY,const float newZ,const float newW);
	Quaternion              &operator () (Quaternion &Other);
	Quaternion              &operator () (RX::vec3 axis, float angleRad);
	Quaternion              &operator = (Quaternion &Other);// Afectação
	Quaternion              &operator ~ ();// Conjugado
	Quaternion              &SetValues(float newX,float newY,float newZ,float newW);

	bool                     operator == (Quaternion &Other);
	bool                     operator != (Quaternion &Other);

	Quaternion              operator - ();// Negação
	Quaternion              operator + (Quaternion &Other);// Adição
	Quaternion              operator - (Quaternion &Other);// Subtracção
	Quaternion              operator * (Quaternion &Other);// Multiplicação
	Quaternion              &operator += (Quaternion &Other);// Soma com afectação
	Quaternion              &operator -= (Quaternion &Other);// Subtracção com afectação
	Quaternion              &operator *= (Quaternion &Other);// Multiplicação com afectação

	Quaternion              &operator /= (float &Scalar);// Divisão com afectação
	Quaternion              &operator *= (float &Scalar);// Multiplicação com afectação


	Quaternion              &SetEuler(float Yaw, float Pitch, float Roll);// Transformação para angulo de Euler
	Quaternion              &Normalize(void);// Normalização dos vectores
	float                    GetLength (void);
	RX::mat4 matrix();

public:
	float x, y, z, w;
};


Quaternion operator * (const Quaternion &First, const Quaternion &Second);
Quaternion operator + (const Quaternion &First, const Quaternion &Second);
Quaternion operator - (const Quaternion &First, const Quaternion &Second);
Quaternion operator - (const Quaternion &Quaternion);

Quaternion operator * (Quaternion quaternion,float Scalar);
Quaternion operator * (float Scalar,Quaternion quaternion);

Quaternion RotationArc(RX::vec3 V0,RX::vec3 V1);
float DotProduct(const Quaternion &First, const Quaternion &Second);
Quaternion Slerp(const Quaternion &From, const Quaternion &To, float Interpolation);
