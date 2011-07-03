#include <memory.h>
#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(float e0, float e1, float e2, float e3,
					float e4, float e5, float e6, float e7,
					float e8, float e9, float e10, float e11,
					float e12, float e13, float e14, float e15)
{
	entries[0]=e0;
	entries[1]=e1;
	entries[2]=e2;
	entries[3]=e3;
	entries[4]=e4;
	entries[5]=e5;
	entries[6]=e6;
	entries[7]=e7;
	entries[8]=e8;
	entries[9]=e9;
	entries[10]=e10;
	entries[11]=e11;
	entries[12]=e12;
	entries[13]=e13;
	entries[14]=e14;
	entries[15]=e15;
}

void Matrix4x4::setEntry(int position, float value)
{
	if(position>=0 && position<=15)
		entries[position]=value;
}
	
float Matrix4x4::getEntry(int position) const
{
	if(position>=0 && position<=15)
		return entries[position];

	return 0.0f;
}

void Matrix4x4::loadIdentity(void)
{
	memset(entries, 0, 16*sizeof(float));
	entries[0]=1.0f;
	entries[5]=1.0f;
	entries[10]=1.0f;
	entries[15]=1.0f;
}

void Matrix4x4::loadZero(void)
{
	memset(entries, 0, 16*sizeof(float));
}

QVector4D Matrix4x4::preMultiplyByVector(const QVector4D rhs) const
{
	return QVector4D(	entries[0]*rhs.x()
					+	entries[4]*rhs.y()
					+	entries[8]*rhs.z()
					+	entries[12]*rhs.w(),

						entries[1]*rhs.x()
					+	entries[5]*rhs.y()
					+	entries[9]*rhs.z()
					+	entries[13]*rhs.w(),

						entries[2]*rhs.x()
					+	entries[6]*rhs.y()
					+	entries[10]*rhs.z()
					+	entries[14]*rhs.w(),

						entries[3]*rhs.x()
					+	entries[7]*rhs.y()
					+	entries[11]*rhs.z()
					+	entries[15]*rhs.w());
}

QVector4D Matrix4x4::posMultiplyByVector(const QVector4D rhs) const
{
	return QVector4D(	entries[0]*rhs.x()
					+	entries[1]*rhs.y()
					+	entries[2]*rhs.z()
					+	entries[3]*rhs.w(),

						entries[4]*rhs.x()
					+	entries[5]*rhs.y()
					+	entries[6]*rhs.z()
					+	entries[7]*rhs.w(),

						entries[8]*rhs.x()
					+	entries[9]*rhs.y()
					+	entries[10]*rhs.z()
					+	entries[11]*rhs.w(),

						entries[12]*rhs.x()
					+	entries[13]*rhs.y()
					+	entries[14]*rhs.z()
					+	entries[15]*rhs.w());
}

Matrix4x4 Matrix4x4::preMultiplyByMatrix(const Matrix4x4 & rhs) const
{
	return Matrix4x4(	entries[0]*rhs.entries[0]+entries[4]*rhs.entries[1]+entries[8]*rhs.entries[2]+entries[12]*rhs.entries[3],
						entries[1]*rhs.entries[0]+entries[5]*rhs.entries[1]+entries[9]*rhs.entries[2]+entries[13]*rhs.entries[3],
						entries[2]*rhs.entries[0]+entries[6]*rhs.entries[1]+entries[10]*rhs.entries[2]+entries[14]*rhs.entries[3],
						entries[3]*rhs.entries[0]+entries[7]*rhs.entries[1]+entries[11]*rhs.entries[2]+entries[15]*rhs.entries[3],
						entries[0]*rhs.entries[4]+entries[4]*rhs.entries[5]+entries[8]*rhs.entries[6]+entries[12]*rhs.entries[7],
						entries[1]*rhs.entries[4]+entries[5]*rhs.entries[5]+entries[9]*rhs.entries[6]+entries[13]*rhs.entries[7],
						entries[2]*rhs.entries[4]+entries[6]*rhs.entries[5]+entries[10]*rhs.entries[6]+entries[14]*rhs.entries[7],
						entries[3]*rhs.entries[4]+entries[7]*rhs.entries[5]+entries[11]*rhs.entries[6]+entries[15]*rhs.entries[7],
						entries[0]*rhs.entries[8]+entries[4]*rhs.entries[9]+entries[8]*rhs.entries[10]+entries[12]*rhs.entries[11],
						entries[1]*rhs.entries[8]+entries[5]*rhs.entries[9]+entries[9]*rhs.entries[10]+entries[13]*rhs.entries[11],
						entries[2]*rhs.entries[8]+entries[6]*rhs.entries[9]+entries[10]*rhs.entries[10]+entries[14]*rhs.entries[11],
						entries[3]*rhs.entries[8]+entries[7]*rhs.entries[9]+entries[11]*rhs.entries[10]+entries[15]*rhs.entries[11],
						entries[0]*rhs.entries[12]+entries[4]*rhs.entries[13]+entries[8]*rhs.entries[14]+entries[12]*rhs.entries[15],
						entries[1]*rhs.entries[12]+entries[5]*rhs.entries[13]+entries[9]*rhs.entries[14]+entries[13]*rhs.entries[15],
						entries[2]*rhs.entries[12]+entries[6]*rhs.entries[13]+entries[10]*rhs.entries[14]+entries[14]*rhs.entries[15],
						entries[3]*rhs.entries[12]+entries[7]*rhs.entries[13]+entries[11]*rhs.entries[14]+entries[15]*rhs.entries[15]);
}
	
Matrix4x4 Matrix4x4::getTranspose(void) const
{
	return Matrix4x4(	entries[ 0], entries[ 4], entries[ 8], entries[12],
						entries[ 1], entries[ 5], entries[ 9], entries[13],
						entries[ 2], entries[ 6], entries[10], entries[14],
						entries[ 3], entries[ 7], entries[11], entries[15]);
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 & rhs) const		//overloaded operators
{
	return Matrix4x4(	entries[0]+rhs.entries[0],
						entries[1]+rhs.entries[1],
						entries[2]+rhs.entries[2],
						entries[3]+rhs.entries[3],
						entries[4]+rhs.entries[4],
						entries[5]+rhs.entries[5],
						entries[6]+rhs.entries[6],
						entries[7]+rhs.entries[7],
						entries[8]+rhs.entries[8],
						entries[9]+rhs.entries[9],
						entries[10]+rhs.entries[10],
						entries[11]+rhs.entries[11],
						entries[12]+rhs.entries[12],
						entries[13]+rhs.entries[13],
						entries[14]+rhs.entries[14],
						entries[15]+rhs.entries[15]);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 & rhs) const		//overloaded operators
{
	return Matrix4x4(	entries[0]-rhs.entries[0],
						entries[1]-rhs.entries[1],
						entries[2]-rhs.entries[2],
						entries[3]-rhs.entries[3],
						entries[4]-rhs.entries[4],
						entries[5]-rhs.entries[5],
						entries[6]-rhs.entries[6],
						entries[7]-rhs.entries[7],
						entries[8]-rhs.entries[8],
						entries[9]-rhs.entries[9],
						entries[10]-rhs.entries[10],
						entries[11]-rhs.entries[11],
						entries[12]-rhs.entries[12],
						entries[13]-rhs.entries[13],
						entries[14]-rhs.entries[14],
						entries[15]-rhs.entries[15]);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & rhs) const
{
	//Optimise for matrices in which bottom row is (0, 0, 0, 1) in both matrices
	if(	entries[3]==0.0f && entries[7]==0.0f && entries[11]==0.0f && entries[15]==1.0f	&&
		rhs.entries[3]==0.0f && rhs.entries[7]==0.0f &&
		rhs.entries[11]==0.0f && rhs.entries[15]==1.0f)
	{
		return Matrix4x4(	entries[0]*rhs.entries[0]+entries[4]*rhs.entries[1]+entries[8]*rhs.entries[2],
							entries[1]*rhs.entries[0]+entries[5]*rhs.entries[1]+entries[9]*rhs.entries[2],
							entries[2]*rhs.entries[0]+entries[6]*rhs.entries[1]+entries[10]*rhs.entries[2],
							0.0f,
							entries[0]*rhs.entries[4]+entries[4]*rhs.entries[5]+entries[8]*rhs.entries[6],
							entries[1]*rhs.entries[4]+entries[5]*rhs.entries[5]+entries[9]*rhs.entries[6],
							entries[2]*rhs.entries[4]+entries[6]*rhs.entries[5]+entries[10]*rhs.entries[6],
							0.0f,
							entries[0]*rhs.entries[8]+entries[4]*rhs.entries[9]+entries[8]*rhs.entries[10],
							entries[1]*rhs.entries[8]+entries[5]*rhs.entries[9]+entries[9]*rhs.entries[10],
							entries[2]*rhs.entries[8]+entries[6]*rhs.entries[9]+entries[10]*rhs.entries[10],
							0.0f,
							entries[0]*rhs.entries[12]+entries[4]*rhs.entries[13]+entries[8]*rhs.entries[14]+entries[12],
							entries[1]*rhs.entries[12]+entries[5]*rhs.entries[13]+entries[9]*rhs.entries[14]+entries[13],
							entries[2]*rhs.entries[12]+entries[6]*rhs.entries[13]+entries[10]*rhs.entries[14]+entries[14],
							1.0f);
	}

	//Optimise for when bottom row of 1st matrix is (0, 0, 0, 1)
	if(	entries[3]==0.0f && entries[7]==0.0f && entries[11]==0.0f && entries[15]==1.0f)
	{
		return Matrix4x4(	entries[0]*rhs.entries[0]+entries[4]*rhs.entries[1]+entries[8]*rhs.entries[2]+entries[12]*rhs.entries[3],
							entries[1]*rhs.entries[0]+entries[5]*rhs.entries[1]+entries[9]*rhs.entries[2]+entries[13]*rhs.entries[3],
							entries[2]*rhs.entries[0]+entries[6]*rhs.entries[1]+entries[10]*rhs.entries[2]+entries[14]*rhs.entries[3],
							rhs.entries[3],
							entries[0]*rhs.entries[4]+entries[4]*rhs.entries[5]+entries[8]*rhs.entries[6]+entries[12]*rhs.entries[7],
							entries[1]*rhs.entries[4]+entries[5]*rhs.entries[5]+entries[9]*rhs.entries[6]+entries[13]*rhs.entries[7],
							entries[2]*rhs.entries[4]+entries[6]*rhs.entries[5]+entries[10]*rhs.entries[6]+entries[14]*rhs.entries[7],
							rhs.entries[7],
							entries[0]*rhs.entries[8]+entries[4]*rhs.entries[9]+entries[8]*rhs.entries[10]+entries[12]*rhs.entries[11],
							entries[1]*rhs.entries[8]+entries[5]*rhs.entries[9]+entries[9]*rhs.entries[10]+entries[13]*rhs.entries[11],
							entries[2]*rhs.entries[8]+entries[6]*rhs.entries[9]+entries[10]*rhs.entries[10]+entries[14]*rhs.entries[11],
							rhs.entries[11],
							entries[0]*rhs.entries[12]+entries[4]*rhs.entries[13]+entries[8]*rhs.entries[14]+entries[12]*rhs.entries[15],
							entries[1]*rhs.entries[12]+entries[5]*rhs.entries[13]+entries[9]*rhs.entries[14]+entries[13]*rhs.entries[15],
							entries[2]*rhs.entries[12]+entries[6]*rhs.entries[13]+entries[10]*rhs.entries[14]+entries[14]*rhs.entries[15],
							rhs.entries[15]);
	}

	//Optimise for when bottom row of 2nd matrix is (0, 0, 0, 1)
	if(	rhs.entries[3]==0.0f && rhs.entries[7]==0.0f &&
		rhs.entries[11]==0.0f && rhs.entries[15]==1.0f)
	{
		return Matrix4x4(	entries[0]*rhs.entries[0]+entries[4]*rhs.entries[1]+entries[8]*rhs.entries[2],
							entries[1]*rhs.entries[0]+entries[5]*rhs.entries[1]+entries[9]*rhs.entries[2],
							entries[2]*rhs.entries[0]+entries[6]*rhs.entries[1]+entries[10]*rhs.entries[2],
							entries[3]*rhs.entries[0]+entries[7]*rhs.entries[1]+entries[11]*rhs.entries[2],
							entries[0]*rhs.entries[4]+entries[4]*rhs.entries[5]+entries[8]*rhs.entries[6],
							entries[1]*rhs.entries[4]+entries[5]*rhs.entries[5]+entries[9]*rhs.entries[6],
							entries[2]*rhs.entries[4]+entries[6]*rhs.entries[5]+entries[10]*rhs.entries[6],
							entries[3]*rhs.entries[4]+entries[7]*rhs.entries[5]+entries[11]*rhs.entries[6],
							entries[0]*rhs.entries[8]+entries[4]*rhs.entries[9]+entries[8]*rhs.entries[10],
							entries[1]*rhs.entries[8]+entries[5]*rhs.entries[9]+entries[9]*rhs.entries[10],
							entries[2]*rhs.entries[8]+entries[6]*rhs.entries[9]+entries[10]*rhs.entries[10],
							entries[3]*rhs.entries[8]+entries[7]*rhs.entries[9]+entries[11]*rhs.entries[10],
							entries[0]*rhs.entries[12]+entries[4]*rhs.entries[13]+entries[8]*rhs.entries[14]+entries[12],
							entries[1]*rhs.entries[12]+entries[5]*rhs.entries[13]+entries[9]*rhs.entries[14]+entries[13],
							entries[2]*rhs.entries[12]+entries[6]*rhs.entries[13]+entries[10]*rhs.entries[14]+entries[14],
							entries[3]*rhs.entries[12]+entries[7]*rhs.entries[13]+entries[11]*rhs.entries[14]+entries[15]);
	}	
	
	return Matrix4x4(	entries[0]*rhs.entries[0]+entries[4]*rhs.entries[1]+entries[8]*rhs.entries[2]+entries[12]*rhs.entries[3],
						entries[1]*rhs.entries[0]+entries[5]*rhs.entries[1]+entries[9]*rhs.entries[2]+entries[13]*rhs.entries[3],
						entries[2]*rhs.entries[0]+entries[6]*rhs.entries[1]+entries[10]*rhs.entries[2]+entries[14]*rhs.entries[3],
						entries[3]*rhs.entries[0]+entries[7]*rhs.entries[1]+entries[11]*rhs.entries[2]+entries[15]*rhs.entries[3],
						entries[0]*rhs.entries[4]+entries[4]*rhs.entries[5]+entries[8]*rhs.entries[6]+entries[12]*rhs.entries[7],
						entries[1]*rhs.entries[4]+entries[5]*rhs.entries[5]+entries[9]*rhs.entries[6]+entries[13]*rhs.entries[7],
						entries[2]*rhs.entries[4]+entries[6]*rhs.entries[5]+entries[10]*rhs.entries[6]+entries[14]*rhs.entries[7],
						entries[3]*rhs.entries[4]+entries[7]*rhs.entries[5]+entries[11]*rhs.entries[6]+entries[15]*rhs.entries[7],
						entries[0]*rhs.entries[8]+entries[4]*rhs.entries[9]+entries[8]*rhs.entries[10]+entries[12]*rhs.entries[11],
						entries[1]*rhs.entries[8]+entries[5]*rhs.entries[9]+entries[9]*rhs.entries[10]+entries[13]*rhs.entries[11],
						entries[2]*rhs.entries[8]+entries[6]*rhs.entries[9]+entries[10]*rhs.entries[10]+entries[14]*rhs.entries[11],
						entries[3]*rhs.entries[8]+entries[7]*rhs.entries[9]+entries[11]*rhs.entries[10]+entries[15]*rhs.entries[11],
						entries[0]*rhs.entries[12]+entries[4]*rhs.entries[13]+entries[8]*rhs.entries[14]+entries[12]*rhs.entries[15],
						entries[1]*rhs.entries[12]+entries[5]*rhs.entries[13]+entries[9]*rhs.entries[14]+entries[13]*rhs.entries[15],
						entries[2]*rhs.entries[12]+entries[6]*rhs.entries[13]+entries[10]*rhs.entries[14]+entries[14]*rhs.entries[15],
						entries[3]*rhs.entries[12]+entries[7]*rhs.entries[13]+entries[11]*rhs.entries[14]+entries[15]*rhs.entries[15]);
}

Matrix4x4 Matrix4x4::operator*(const float rhs) const
{
	return Matrix4x4(	entries[0]*rhs,
						entries[1]*rhs,
						entries[2]*rhs,
						entries[3]*rhs,
						entries[4]*rhs,
						entries[5]*rhs,
						entries[6]*rhs,
						entries[7]*rhs,
						entries[8]*rhs,
						entries[9]*rhs,
						entries[10]*rhs,
						entries[11]*rhs,
						entries[12]*rhs,
						entries[13]*rhs,
						entries[14]*rhs,
						entries[15]*rhs);
}

Matrix4x4 Matrix4x4::operator/(const float rhs) const
{
	if (rhs==0.0f || rhs==1.0f)
		return (*this);
		
	float temp=1/rhs;

	return (*this)*temp;
}

Matrix4x4 operator*(float scaleFactor, const Matrix4x4 & rhs)
{
	return rhs*scaleFactor;
}

bool Matrix4x4::operator==(const Matrix4x4 & rhs) const
{
	for(int i=0; i<16; i++)
	{
		if(entries[i]!=rhs.entries[i])
			return false;
	}
	return true;
}

bool Matrix4x4::operator!=(const Matrix4x4 & rhs) const
{
	return !((*this)==rhs);
}

void Matrix4x4::operator+=(const Matrix4x4 & rhs)
{
	(*this)=(*this)+rhs;
}

void Matrix4x4::operator-=(const Matrix4x4 & rhs)
{
	(*this)=(*this)-rhs;
}

void Matrix4x4::operator*=(const Matrix4x4 & rhs)
{
	(*this)=(*this)*rhs;
}

void Matrix4x4::operator*=(const float rhs)
{
	(*this)=(*this)*rhs;
}

void Matrix4x4::operator/=(const float rhs)
{
	(*this)=(*this)/rhs;
}

Matrix4x4 Matrix4x4::operator-(void) const
{
	Matrix4x4 result(*this);

	for(int i=0; i<16; i++)
		result.entries[i]=-result.entries[i];

	return result;
}