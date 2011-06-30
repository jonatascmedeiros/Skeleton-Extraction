#ifndef __C3_MATH_MAT_H__
#define __C3_MATH_MAT_H__

namespace C3 {
namespace Math {

//-----------------------------------------------------------------------------
//=============================================================================
//
/// @name Matrix Constants
//@{
const float MAT_INVERSE_EPSILON = 1e-14f;
const float MAT_EPSILON         = 1e-6f;
//@}

//-----------------------------------------------------------------------------
//=============================================================================
//
// some forewards

class mat2;
class mat3;
class mat4;
class modelview4;

float det(const mat2 &m);
float det(const mat3 &m);
float det(const mat4 &m);

bool invert(mat2 &m, const float epsilon);
bool invert(mat3 &m, const float epsilon);
bool invert(mat4 &m, const float epsilon);

//-----------------------------------------------------------------------------
//=============================================================================
//
// mat2
//
/// 2x2 floats - column-major storage, [col][row] indexing

class mat2 {

public:

/// @name Construction - NOTE: mat(floats) in transposed notation!!!
//@{
	inline mat2() {}
	inline mat2(const float xx, const float yx,
		        const float xy, const float yy)
		: x(xx, xy), y(yx, yy) {}
	inline mat2(const vec2 &vx, const vec2 &vy)
		: x(vx), y(vy) {}
	inline mat2(const float *fp)
		: x(&fp[0]), y(&fp[2]) {}
//@}

/// @name Array Operators (Column Retrieval)
//@{
	inline const vec2 &operator[](const int n) const { return (&x)[n]; }
	inline vec2 &operator[](const int n) { return (&x)[n]; }
//@}

/// @name Negation
//@{
	inline const mat2 operator-() const { return mat2(-x, -y); }
//@}

/// @name Addition & Substraction
//@{
	inline const mat2 operator+(const mat2 &m) const {	return mat2(x+m.y, y+m.y); }
	inline const mat2 &operator+=(const mat2 &m) {	return *this = *this + m; }
	inline const mat2 operator-(const mat2 &m) const { return mat2(x-m.x, y-m.y); }
	inline const mat2 &operator-=(const mat2 &m) { return *this = *this - m; }
//@}

/// @name Scaling
//@{
	inline const mat2 operator*(const float s) const { return mat2(x*s, y*s); }
	inline mat2 &operator*=(const float s) { return *this = *this * s; }
//@}

	/// float * mat := mat * float
	friend inline mat2 operator*(const float s, const mat2 &m) { return m * s; }

/// @name Transformation
//@{
	inline const vec2 operator*(const vec2 &v) const {
		return vec2(x*v.x + y*v.y);
	}
	inline const mat2 operator*(const mat2 &m) const {
		return mat2(*this*m.x, *this*m.y);
	}
	inline const mat2 &operator*=(const mat2 &m) {	return *this = m * *this; }
//@}

/// @name Transposed & Inverse Retrieval
//@{
	/// transposed
	inline const mat2 operator~() const {
		return mat2(x[0], x[1],
		            y[0], y[1]);
	}
	/// inverse
	inline const mat2 operator!() const { mat2 m(*this); invert(m, MAT_INVERSE_EPSILON); return m; }
//@}

/// @name Comparison
//@{
	inline bool operator==(const mat2 &m) const { return x==m.x && y==m.y; }
	inline bool operator!=(const mat2 &m) const { return x!=m.x || y!=m.y; }
//@}

/// @name Conversion
//@{
	inline const float *to_floats() const { return x.to_floats(); }
	inline float *to_floats() { return x.to_floats(); }
//@}

public:

	vec2 x, y;

	static const mat2 zero, identity;
};

//-----------------------------------------------------------------------------
//=============================================================================
//
// mat3
//
/// 3x3 floats - column-major storage, [col][row] indexing

class mat3 {

public:

/// @name Construction - NOTE: mat(floats) in transposed notation!!!
//@{
	inline mat3() {}
	inline mat3(const float xx, const float yx, const float zx,
	            const float xy, const float yy, const float zy,
	            const float xz, const float yz, const float zz)
		 : x(xx, xy, xz), y(yx, yy, yz), z(zx, zy, zz) {}
	inline mat3(const vec3 &vx, const vec3 &vy, const vec3 &vz)
		: x(vx), y(vy), z(vz) {}
	inline mat3(const mat2 &m)
		: x(m.x, 0), y(m.y, 0), z(0, 0, 1) {}
	inline mat3(const float *fp)
		: x(&fp[0]), y(&fp[3]), z(&fp[6]) {}
//@}

/// @name Array Operators (Column Retrieval)
//@{
	inline const vec3 &operator[](const int n) const {	return (&x)[n]; }
	inline vec3 &operator[](const int n) {	return (&x)[n]; }
//@}

/// @name Negation
//@{
	inline const mat3 operator-() const { return mat3(-x, -y, -z); }
//@}

/// @name Addition & Substraction
//@{
	inline const mat3 operator+(const mat3 &m) const { return mat3(x+m.x, y+m.y, z+m.z); }
	inline const mat3 &operator+=(const mat3 &m) { return *this = *this + m; }
	inline const mat3 operator-(const mat3 &m) const { return mat3(x-m.x, y-m.y, z-m.z); }
	inline const mat3 &operator-=(const mat3 &m) { return *this = *this - m; }
//@}

/// @name Scaling
//@{
	inline const mat3 operator*(const float s) const { return mat3(x*s, y*s, z*s); }
	inline mat3 &operator*=(const float s) { return *this = *this * s; }
//@}

	/// float * mat := mat * float
	inline friend mat3 operator*(const float s, const mat3 &m) { return m * s; }

/// @name Transformation
//@{
	inline const vec3 operator*(const vec3 &v) const {
		return vec3(x*v.x + y*v.y + z*v.z);
	}
	inline const mat3 operator*(const mat3 &m) const {
		return mat3(*this*m.x, *this*m.y, *this*m.z);
	}
	inline const mat3 &operator*=(const mat3 &m) {	return *this = m * *this; }
//@}

/// @name Transposed & Inverse Retrieval
//@{
	/// transposed
	inline const mat3 operator~() const {
		return mat3(x[0], x[1], x[2], 
					y[0], y[1], y[2], 
					z[0], z[1], z[2]);
	}
	/// inverse
	inline const mat3 operator!() const { mat3 m(*this); invert(m, MAT_INVERSE_EPSILON); return m; }
//@}

/// @name Comparison
//@{
	inline bool operator==(const mat3 &m) const { return x==m.x && y==m.y && z==m.z; }
	inline bool operator!=(const mat3 &m) const { return x!=m.x || y!=m.y || z!=m.z; }
//@}

/// @name Conversion
//@{
	inline const float *to_floats() const { return x.to_floats(); }
	inline float *to_floats() { return x.to_floats(); }
//@}

public:

	vec3 x, y, z;

	static const mat3 zero, identity;
};

//-----------------------------------------------------------------------------
//=============================================================================
//
// mat4
//
/// 4x4 floats - column-major storage, [col][row] indexing

class mat4 {

public:

/// @name Construction - NOTE: mat(floats) in transposed notation!!!
//@{
	inline mat4() {}
	inline mat4(const float xx, const float yx, const float zx, const float wx,
	            const float xy, const float yy, const float zy, const float wy,
	            const float xz, const float yz, const float zz, const float wz,
	            const float xw, const float yw, const float zw, const float ww)
		: x(xx, xy, xz, xw), y(yx, yy, yz, yw), z(zx, zy, zz, zw), w(wx, wy, wz, ww) {}
	inline mat4(const vec4 &vx, const vec4 &vy, const vec4 &vz, const vec4 &vw)
		: x(vx), y(vy), z(vz), w(vw) {}
	inline mat4(const mat3 &m)
		: x(m.x, 0), y(m.y, 0), z(m.z, 0), w(0, 0, 0, 1) {}
	inline mat4(const mat2 &m)
		: x(m.x, 0, 0), y(m.y, 0, 0), z(0, 0, 1, 0), w(0, 0, 0, 1) {}
	inline mat4(const float *fp)
		: x(&fp[0]), y(&fp[4]), z(&fp[8]), w(&fp[12]) {}
//@}

/// @name Non-Inline Construction by modelview4
//@{
	mat4(const modelview4 &m);
//@}

/// @name Array Operators (Column Retrieval)
//@{
	inline const vec4 &operator[](const int n) const { return (&x)[n]; }
	inline vec4 &operator[](const int n) { return (&x)[n]; }
//@}

/// @name Negation
//@{
	inline const mat4 operator-() const { return mat4(-x, -y, -z, -w);	}
//@}

/// @name Addition & Substraction
//@{
	inline const mat4 operator+(const mat4 &m) const {	return mat4(x+m.x, y+m.y, z+m.z, w+m.w); }
	inline const mat4 &operator+=(const mat4 &m) {	return *this = *this + m; }
	inline const mat4 operator-(const mat4 &m) const {	return mat4(x-m.x, y-m.y, z-m.z, w-m.w); }
	inline const mat4 &operator-=(const mat4 &m) {	return *this = *this - m; }
//@}

/// @name Scaling
//@{
	inline const mat4 operator*(const float s) const { return mat4(x*s, y*s, z*s, w*s); }
	inline mat4 &operator*=(const float s) { return *this = *this * s; }
//@}

	/// float * mat := mat * float
	inline friend mat4 operator*(const float s, const mat4 &m) { return m * s; }

/// @name Transformation
//@{
	inline const vec4 operator*(const vec4 &v) const {
		return vec4(x*v.x + y*v.y + z*v.z + w*v.w);
	}
	inline const mat4 operator*(const mat4 &m) const {
		return mat4(*this*m.x, *this*m.y, *this*m.z, *this*m.w);
	}
	inline const mat4 &operator*=(const mat4 &m) { return *this = m * *this; }
//@}

/// @name Transposed & Inverse Retrieval
//@{
	/// transposed
	inline const mat4 operator~() const {
		return mat4(x[0], x[1], x[2], x[3], 
					y[0], y[1], y[2], y[3], 
					z[0], z[1], z[2], z[3], 
					w[0], w[1], w[2], w[3]);
	}
	/// inverse
	inline const mat4 operator!() const { mat4 m(*this); invert(m, MAT_INVERSE_EPSILON); return m; }
//@}

/// @name Comparison
//@{
	inline bool operator==(const mat4 &m) const { return x==m.x && y==m.y && z==m.z && w==m.w; }
	inline bool operator!=(const mat4 &m) const { return x!=m.x || y!=m.y || z!=m.z || w!=m.w; }
//@}

/// @name Conversion
//@{
	inline const float *to_floats() const { return x.to_floats(); }
	inline float *to_floats() { return x.to_floats(); }
//@}

public:

	vec4 x, y, z, w;

	static const mat4 zero, identity;
};

//-----------------------------------------------------------------------------
//=============================================================================
//
// matrix functions

/// @name Transposition
inline void transpose(mat2 &m) { m = ~m; }
inline void transpose(mat3 &m) { m = ~m; }
inline void transpose(mat4 &m) { m = ~m; }
/// @}

/// @name Sub-Matrix Retrieval
const mat3 submat3(const mat4 &m, const int c, const int r);
/// @}

/// @name Determinants
inline float det(const mat2 &m) { return m[0][0] * m[1][1] - m[0][1] * m[1][0]; }
float det(const mat3 &m);
float det(const mat4 &m);
/// @}

/// @name Inversion
bool invert(mat2 &m, const float epsilon = MAT_INVERSE_EPSILON);
bool invert(mat3 &m, const float epsilon = MAT_INVERSE_EPSILON);
bool invert(mat4 &m, const float epsilon = MAT_INVERSE_EPSILON);
/// @}

/// @name Matrix (De)Composition
inline const vec2 get_scale(const mat2 &m) { return vec2(length(m.x), length(m.y)); }
inline const vec3 get_scale(const mat3 &m) { return vec3(length(m.x), length(m.y), length(m.z)); }
inline const vec4 get_scale(const mat4 &m) { return vec4(length(m.x), length(m.y), length(m.z), length(m.w)); }

inline void set_scale(mat2 &m, const vec2 &s) {
	m.x *= s.x * rsqrtf(dot(m.x, m.x));
	m.y *= s.y * rsqrtf(dot(m.y, m.y));
}
inline void set_scale(mat3 &m, const vec3 &s) {
	m.x *= s.x * rsqrtf(dot(m.x, m.x));
	m.y *= s.y * rsqrtf(dot(m.y, m.y));
	m.z *= s.z * rsqrtf(dot(m.z, m.z));
}
inline void set_scale(mat4 &m, const vec4 &s) {
	m.x *= s.x * rsqrtf(dot(m.x, m.x));
	m.y *= s.y * rsqrtf(dot(m.y, m.y));
	m.z *= s.z * rsqrtf(dot(m.z, m.z));
	m.w *= s.w * rsqrtf(dot(m.w, m.w));
}

inline const mat2 get_rotation(const mat2 &m) { return mat2(normal(m.x), normal(m.y)); }
inline const mat3 get_rotation(const mat3 &m) { return mat3(normal(m.x), normal(m.y), normal(m.z)); }

inline void set_rotation(mat2 &m, const mat2 &r) { vec2 s = get_scale(m); m = r; set_scale(m, s); }
inline void set_rotation(mat3 &m, const mat3 &r) { vec3 s = get_scale(m); m = r; set_scale(m, s); }
/// @}

/// @name Special Matrices Setup
const mat2 rotation2(const float angle);
const mat3 rotation3(const float angle, const vec3 &axis);

const mat4 perspective4(const float fovy, const float aspect,
					    const float zNear, const float zFar);
const mat4 inv_perspective4(const float fovy, const float aspect,
					        const float zNear, const float zFar);

const mat4 ortho4(const float left, const float right,
				  const float bottom, const float top,
				  const float zNear, float zFar);
const mat4 inv_ortho4(const float left, const float right,
				      const float bottom, const float top,
				      const float zNear, float zFar);
/// @}

/// @name Some Standard Expressions
inline const mat2 vvT(const vec2 &v) { return mat2(v.x * v, v.y * v); }
inline const mat3 vvT(const vec3 &v) { return mat3(v.x * v, v.y * v, v.z * v); }
inline const mat4 vvT(const vec4 &v) { return mat4(v.x * v, v.y * v, v.z * v, v.w * v); }

inline const float vTmv(const mat2 &m, const vec2 &v) { return dot(v, m * v); }
inline const float vTmv(const mat3 &m, const vec3 &v) { return dot(v, m * v); }
inline const float vTmv(const mat4 &m, const vec4 &v) { return dot(v, m * v); }
/// @}

//-----------------------------------------------------------------------------


}; // namespace Math
}; // namespace C3

#endif // __C3_MATH_MAT_H__
