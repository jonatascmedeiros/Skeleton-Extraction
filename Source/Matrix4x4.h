#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <QVector4D>

class Matrix4x4
{
	public:
		Matrix4x4(){ loadIdentity(); }
		Matrix4x4(	float e0, float e1, float e2, float e3,
					float e4, float e5, float e6, float e7,
					float e8, float e9, float e10, float e11,
					float e12, float e13, float e14, float e15);		
		~Matrix4x4() {}

		void loadIdentity(void);
	    void loadZero(void);
		void setEntry(int position, float value);
		float getEntry(int position) const;

		Matrix4x4 getTranspose(void) const;

		QVector4D preMultiplyByVector(const QVector4D rhs) const;
		QVector4D posMultiplyByVector(const QVector4D rhs) const;
		Matrix4x4 preMultiplyByMatrix(const Matrix4x4 & rhs) const;
	
		//binary operators
		Matrix4x4 operator+(const Matrix4x4 & rhs) const;
		Matrix4x4 operator-(const Matrix4x4 & rhs) const;
		Matrix4x4 operator*(const Matrix4x4 & rhs) const;
		Matrix4x4 operator*(const float rhs) const;
		Matrix4x4 operator/(const float rhs) const;
		friend Matrix4x4 operator*(float scaleFactor, const Matrix4x4 & rhs);

		bool operator==(const Matrix4x4 & rhs) const;
		bool operator!=(const Matrix4x4 & rhs) const;

		//self-add etc
		void operator+=(const Matrix4x4 & rhs);
		void operator-=(const Matrix4x4 & rhs);
		void operator*=(const Matrix4x4 & rhs);
		void operator*=(const float rhs);
		void operator/=(const float rhs);

		//unary operators
		Matrix4x4 operator-(void) const;
		Matrix4x4 operator+(void) const {return (*this);}
	
		//member variables
		float entries[16];
};

#endif	//MATRIX4X4_H