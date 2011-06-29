//////////////////////////////////////////////////////////////////////////////////////////
//	VECTOR4D.cpp
//	Function definitions for 4d vector class
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	15th August 2002	-	prevent divide by zero in operator VECTOR3D()
//	Modified:	8th November 2002	-	Changed Constructor layout
//									-	Some speed Improvements
//									-	Corrected Lerp
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	

#include "Maths.h"

void VECTOR4D::RotateX(float angle)
{
	(*this)=GetRotatedX(angle);
}

VECTOR4D VECTOR4D::GetRotatedX(float angle) const
{
	VECTOR3D v3d(x, y, z);

	v3d.RotateX(angle);

	return VECTOR4D(v3d.x, v3d.y, v3d.z, w);
}

void VECTOR4D::RotateY(float angle)
{
	(*this)=GetRotatedY(angle);
}

VECTOR4D VECTOR4D::GetRotatedY(float angle) const
{
	VECTOR3D v3d(x, y, z);

	v3d.RotateY(angle);

	return VECTOR4D(v3d.x, v3d.y, v3d.z, w);
}

void VECTOR4D::RotateZ(float angle)
{
	(*this)=GetRotatedZ(angle);
}

VECTOR4D VECTOR4D::GetRotatedZ(float angle) const
{
	VECTOR3D v3d(x, y, z);

	v3d.RotateZ(angle);

	return VECTOR4D(v3d.x, v3d.y, v3d.z, w);
}

void VECTOR4D::RotateAxis(float angle, const VECTOR3D & axis)
{
	(*this)=GetRotatedAxis(angle, axis);
}

VECTOR4D VECTOR4D::GetRotatedAxis(float angle, const VECTOR3D & axis) const
{
	VECTOR3D v3d(x, y, z);

	v3d.RotateAxis(angle, axis);

	return VECTOR4D(v3d.x, v3d.y, v3d.z, w);
}


VECTOR4D operator*(float scaleFactor, const VECTOR4D & rhs)
{
	return rhs*scaleFactor;
}

bool VECTOR4D::operator==(const VECTOR4D & rhs) const
{
	if(x==rhs.x && y==rhs.y && z==rhs.z && w==rhs.w)
		return true;

	return false;
}

VECTOR4D::operator VECTOR3D()
{
	if(w==0.0f || w==1.0f)
		return VECTOR3D(x, y, z);
	else
		return VECTOR3D(x/w, y/w, z/w);
}
