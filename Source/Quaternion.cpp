#include <RX/mat4.h>
#include <QDebug>
#include "Quaternion.h"
using namespace RX;

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion::Quaternion(const float NewX,const float NewY,const float NewZ,const float NewW)
	{
	SetValues(NewX,NewY,NewZ,NewW);
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion::Quaternion(vec3 Axis,float Angle)
	{
	float Temp1,Temp2;
	Temp1 = Axis.norm();
	Q_ASSERT(Temp1 != 0 && "Quaternion Axis is zero!");
	Temp2 = sinf(Angle * 0.5F) / Temp1;
	SetValues(Axis.x * Temp2,Axis.y * Temp2,Axis.z * Temp2,cosf(Angle * 0.5F));
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::operator () (const float NewX,const float NewY,const float NewZ)
	{
	SetValues(NewX,NewY,NewZ,w);
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::operator () (const float NewX,const float NewY,const float NewZ,const float NewW)
	{
	SetValues(NewX,NewY,NewZ,NewW);
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::operator () (Quaternion &Other)
	{
	SetValues(Other.x,Other.y,Other.z,Other.w);
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::operator () (vec3 Axis,float Angle)
	{
	float Temp1,Temp2;
	Temp1 = Axis.norm();
	Q_ASSERT(Temp1 != 0 && "Quaternion Axis is zero!");
	Temp2 = sinf(Angle * 0.5F) / Temp1;
	SetValues(Axis.x * Temp2,Axis.y * Temp2,Axis.z * Temp2,cosf(Angle * 0.5F));
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::operator = (Quaternion &Other)
	{
	SetValues(Other.x,Other.y,Other.z,Other.w);
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::operator ~ ()
	{
x=-x;
	y=-y;
	z=-z;
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::SetValues(float NewX,float NewY,float NewZ,float NewW)
	{
	x=NewX;
	y=NewY;
	z=NewZ;
	w=NewW;
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

bool Quaternion::operator == (Quaternion &Other)
	{
	if ((x==Other.x) && (y==Other.y) && (z==Other.z) && (w==Other.w)) return true;
	return false;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

bool Quaternion::operator != (Quaternion &Other)
	{
	if ((x!=Other.x) || (y!=Other.y) || (z!=Other.z) || (w!=Other.w)) return true;
	return false;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion Quaternion::operator - ()
	{
	return Quaternion(-x,-y,-z,-w);
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion Quaternion::operator + (Quaternion &Other)
	{
	Quaternion Temp;
	Temp(Other.x+x,Other.y+y,Other.z+z,Other.w+w);
	return Temp;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion Quaternion::operator - (Quaternion &Other)
	{
	Quaternion Temp;
	Temp(Other.x-x,Other.y-y,Other.z-z,Other.w-w);
	return Temp;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion Quaternion::operator * (Quaternion &Other)
	{
	return Quaternion(
		w * Other.x + x * Other.w + y * Other.z - z * Other.y,
		w * Other.y + y * Other.w + z * Other.x - x * Other.z,
		w * Other.z + z * Other.w + x * Other.y - y * Other.x,
		w * Other.w - x * Other.x - y * Other.y - z * Other.z); 
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::operator += (Quaternion &Other)
	{
	x+=Other.x;
	y+=Other.y;
	z+=Other.z;
	w+=Other.w;
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::operator -= (Quaternion &Other)
	{
	x-=Other.x;
	y-=Other.y;
	z-=Other.z;
	w-=Other.w;
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::operator *= (Quaternion &Other)
	{
	x=w * Other.x + x * Other.w + y * Other.z - z * Other.y,
	y=w * Other.y + y * Other.w + z * Other.x - x * Other.z,
	z=w * Other.z + z * Other.w + x * Other.y - y * Other.x,
	w=w * Other.w - x * Other.x - y * Other.y - z * Other.z; 
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::operator /= (float &Scalar)
	{
	return SetValues(x/Scalar,y/Scalar,z/Scalar,w/Scalar);
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::operator *= (float &Scalar)
	{
	return SetValues(x*Scalar,y*Scalar,z*Scalar,w*Scalar);
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion &Quaternion::SetEuler(float Yaw, float Pitch, float Roll)
	{
	float cosY = cosf(Yaw / 2.0F);
	float sinY = sinf(Yaw / 2.0F);
	float cosP = cosf(Pitch / 2.0F);
	float sinP = sinf(Pitch / 2.0F);
	float cosR = cosf(Roll / 2.0F);
	float sinR = sinf(Roll / 2.0F);
	SetValues(
		cosR * sinP * cosY + sinR * cosP * sinY,
		cosR * cosP * sinY - sinR * sinP * cosY,
		sinR * cosP * cosY - cosR * sinP * sinY,
		cosR * cosP * cosY + sinR * sinP * sinY
		);
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
	
Quaternion &Quaternion::Normalize(void)
	{
	float Length=GetLength();
	x/=Length;
	y/=Length;
	z/=Length;
	w/=Length;
	return *this;
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

float Quaternion::GetLength(void)
	{
	return sqrtf(w*w + x*x + y*y + z*z);
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

mat4 Quaternion::matrix()
	{
	return mat4(
		vec4(1 - 2*(y*y) - 2*(z*z), 2*(x*y+w*z), 2*(x*z-w*y), 0),
		vec4(2*(x*y-w*z), 1 - 2*(x*x) - 2*(z*z), 2*(y*z+w*x), 0),
		vec4(2*(x*z+w*y), 2*(y*z-w*x), 1 - 2*(x*x) - 2*(y*y), 0),
		vec4(0, 0, 0, 1));
	}


//---------------------------------------------------------------------------
// Operadores externos
//---------------------------------------------------------------------------

Quaternion operator * (const Quaternion &First, const Quaternion &Second)
	{
	return Quaternion(
			First.w * Second.x + First.x * Second.w + First.y * Second.z - First.z * Second.y,
			First.w * Second.y + First.y * Second.w + First.z * Second.x - First.x * Second.z,
			First.w * Second.z + First.z * Second.w + First.x * Second.y - First.y * Second.x,
			First.w * Second.w - First.x * Second.x - First.y * Second.y - First.z * Second.z); 
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion operator + (const Quaternion &First, const Quaternion &Second)
	{
	return Quaternion(First.x+Second.x,First.y+Second.y,First.z+Second.z,First.w+Second.w);
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion operator - (const Quaternion &First, const Quaternion &Second)
	{
	return Quaternion(First.x-Second.x,First.y-Second.y,First.z-Second.z,First.w-Second.w);
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion operator - (const Quaternion &quaternion)
	{
	return Quaternion(-quaternion.x, -quaternion.y, -quaternion.z, -quaternion.w);
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion operator * (Quaternion quaternion,float Scalar)
	{
	return Quaternion(quaternion.x*Scalar,quaternion.y*Scalar,quaternion.z*Scalar,quaternion.w*Scalar);
	}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

Quaternion operator * (float Scalar,Quaternion quaternion)
	{
	return Quaternion(quaternion.x*Scalar,quaternion.y*Scalar,quaternion.z*Scalar,quaternion.w*Scalar);
	}

//---------------------------------------------------------------------------
//  
//---------------------------------------------------------------------------

Quaternion RotationArc(vec3 V0,vec3 V1)
	{
	Quaternion quaternion;
	// v0.normalize(); 
	// v1.normalize();  // If vector is already unit length then why do it again?
	vec3 Temp = V0 ^ V1;

	float   d = V0 * V1;
	float   s = (float)sqrt((1+d)*2);
	quaternion.x = Temp.x / s;
	quaternion.y = Temp.y / s;
	quaternion.z = Temp.z / s;
	quaternion.w = s /2.0f;
	return quaternion;
	}


// 


float DotProduct(const Quaternion &First, const Quaternion &Second)
	{
	return First.x * Second.x + First.y * Second.y + First.z * Second.z + First.w * Second.w;
	}


// 


Quaternion Slerp(const Quaternion &From, const Quaternion &To, float Interpolation)
{
	Quaternion Temp;
	float omega, cosO, sinO;
	float scale0, scale1;

	cosO = DotProduct(From, To);

	if (cosO < 0.0)
		{
		cosO = -cosO;
		Temp = -To;
		}
	else
		{
		Temp = -To;
		}

	if ((1.0 - cosO) > ERROR_TOLERANCE)
		{
		omega = (float)acos(cosO);
		sinO = sinf(omega);
		scale0 = sinf((1.0F - Interpolation) * omega) / sinO;
		scale1 = sinf(Interpolation * omega) / sinO;
		}
	else
		{
		scale0 = 1.0F - Interpolation;
		scale1 = Interpolation;
		}
	return From*scale0 + Temp*scale1 ;
	}