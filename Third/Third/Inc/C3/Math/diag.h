#ifndef __C3_MATH_DIAG_H__
#define __C3_MATH_DIAG_H__

namespace C3 {
namespace Math {

//-----------------------------------------------------------------------------
//=============================================================================
//
// diag2
//
/// Pivot elements of a 2x2 diagonal matrix

class diag2 {

public:

/// @name Construction
//@{
	inline diag2() {}
	inline diag2(const float s)
		: x(s), y(s) {}
	inline diag2(const float x, const float y)
		: x(x), y(y) {}
	inline diag2(const vec2 &v)
		: x(v.x), y(v.y) {}
	inline diag2(const float *fp)
		: x(fp[0]), y(fp[1]) {}
//@}

/// @name Array Operators (Pivot Retrieval)
//@{
	inline const float &operator[](const int n) const {	return (&x)[n]; }
	inline float &operator[](const int n) {	return (&x)[n]; }
//@}

/// @name Negation
//@{
	inline const diag2 operator-() const { return diag2(-x, -y); }
//@}

/// @name Scaling
//@{
	inline const diag2 operator*(const float s) const { return diag2(x*s, y*s); }
	inline diag2 &operator*=(const float s) { return *this = *this * s; }
//@}

	/// float * diag
	friend inline const diag2 operator*(const float s, const diag2 &d) { return d * s; }

/// @name Transformation
//@{
	inline const vec2 operator*(const vec2 &v) const { return to_vec2() * v; }
	inline const diag2 operator*(const diag2 &d) const { return diag2(x*d.x, y*d.y); }
	inline const diag2 &operator*=(const diag2 &d) { return *this = d * *this; }
	/// (row scaling)
	inline const mat2 operator*(const mat2 &m) const {
		return mat2(x*m[0][0], x*m[1][0],
		            y*m[0][1], y*m[1][1]);
	}
//@}

	/// (column scaling)
	friend inline const mat2 operator*(const mat2 &m, const diag2 &d) {	return mat2(m.x*d.x, m.y*d.y); }
	/// (column scaling)
	friend inline const mat2 &operator*=(mat2 &m, const diag2 &d) { m = d * m; return m; }

/// @name Comparison
//@{
	inline bool operator==(const diag2 &d) const { return to_vec2() == d.to_vec2(); }
	inline bool operator!=(const diag2 &d) const { return to_vec2() != d.to_vec2(); }
//@}

/// @name Conversion
//@{
	inline const vec2 &to_vec2() const { return *reinterpret_cast<const vec2*>(this); }
	inline vec2 &to_vec2() { return *reinterpret_cast<vec2*>(this); }
	inline const float *to_floats() const { return &x; }
	inline float *to_floats() { return &x; }
//@}

public:

	float x, y;

	static const diag2 identity;
};

//-----------------------------------------------------------------------------
//=============================================================================
//
// diag3
//
/// Pivot elements of a 3x3 diagonal matrix

class diag3 {

public:

/// @name Construction
//@{
	inline diag3() {}
	inline diag3(const float s)
		: x(s), y(s), z(s) {}
	inline diag3(const float x, const float y, const float z)
		: x(x), y(y), z(z) {}
	inline diag3(const vec3 &v)
		: x(v.x), y(v.y), z(v.z) {}
	inline diag3(const float *fp)
		: x(fp[0]), y(fp[1]), z(fp[2]) {}
//@}

/// @name Array Operators (Pivot Retrieval)
//@{
	inline const float &operator[](const int n) const {	return (&x)[n]; }
	inline float &operator[](const int n) {	return (&x)[n]; }
//@}

/// @name Negation
//@{
	inline const diag3 operator-() const { return diag3(-x, -y, -z); }
//@}

/// @name Scaling
//@{
	inline const diag3 operator*(const float s) const { return diag3(x*s, y*s, z*s); }
	inline diag3 &operator*=(const float s) { return *this = *this * s; }
//@}

	/// float * diag
	friend inline const diag3 operator*(const float s, const diag3 &d) { return d * s; }

/// @name Transformation
//@{
	inline const vec3 operator*(const vec3 &v) const { return to_vec3() * v; }
	inline const diag3 operator*(const diag3 &d) const { return diag3(x*d.x, y*d.y, z*d.z);	}
	inline const diag3 &operator*=(const diag3 &d) { return *this = d * *this; }
	/// (row scaling)
	inline const mat3 operator*(const mat3 &m) const {
		return mat3(x*m[0][0], x*m[1][0], x*m[2][0],
		            y*m[0][1], y*m[1][1], y*m[2][1],
			        z*m[0][2], z*m[1][2], z*m[2][2]);
	}
//@}

	/// (column scaling)
	friend inline const mat3 operator*(const mat3 &m, const diag3 &d) {	return mat3(m.x*d.x, m.y*d.y, m.z*d.z);	}
	/// (column scaling)
	friend inline const mat3 &operator*=(mat3 &m, const diag3 &d) { m = d * m; return m; }

/// @name Comparison
//@{
	inline bool operator==(const diag3 &d) const { return to_vec3() == d.to_vec3(); }
	inline bool operator!=(const diag3 &d) const { return to_vec3() != d.to_vec3(); }
//@}

/// @name Conversion
//@{
	inline const diag2 &to_diag2() const { return *reinterpret_cast<const diag2*>(this); }
	inline diag2 &to_diag2() { return *reinterpret_cast<diag2*>(this); }
	inline const vec3 &to_vec3() const { return *reinterpret_cast<const vec3*>(this); }
	inline vec3 &to_vec3() { return *reinterpret_cast<vec3*>(this); }
	inline const vec2 &to_vec2() const { return *reinterpret_cast<const vec2*>(this); }
	inline vec2 &to_vec2() { return *reinterpret_cast<vec2*>(this); }
	inline const float *to_floats() const { return &x; }
	inline float *to_floats() { return &x; }
//@}

public:

	float x, y, z;

	static const diag3 identity;
};

//-----------------------------------------------------------------------------
//=============================================================================
//
// diag4
//
/// Pivot elements of a 4x4 diagonal matrix

class diag4 {

public:

/// @name Construction
//@{
	inline diag4() {}
	inline diag4(const float s)
		: x(s), y(s), z(s), w(s) {}
	inline diag4(const float x, const float y, const float z, const float w)
		: x(x), y(y), z(z), w(w) {}
	inline diag4(const vec4 &v)
		: x(v.x), y(v.y), z(v.z), w(v.w) {}
	inline diag4(const float *fp)
		: x(fp[0]), y(fp[1]), z(fp[2]), w(fp[3]) {}
//@}

/// @name Array Operators (Pivot Retrieval)
//@{
	inline const float &operator[](const int n) const {	return (&x)[n]; }
	inline float &operator[](const int n) {	return (&x)[n]; }
//@}

/// @name Negation
//@{
	inline const diag4 operator-() const { return diag4(-x, -y, -z, -w); }
//@}

/// @name Scaling
//@{
	inline const diag4 operator*(const float s) const { return diag4(x*s, y*s, z*s, w*s); }
	inline diag4 &operator*=(const float s) { return *this = *this * s; }
//@}

	/// float * diag
	friend inline diag4 operator*(const float s, const diag4 &d) { return d * s; }

/// @name Transformation
//@{
	inline const vec4 operator*(const vec4 &v) const { return to_vec4() * v; }
	inline const diag4 operator*(const diag4 &d) const { return diag4(x*d.x, y*d.y, z*d.z, w*d.w); }
	inline const diag4 &operator*=(const diag4 &d) { return *this = d * *this; }
	/// (row scaling)
	inline const mat4 operator*(const mat4 &m) const {
		return mat4(x*m[0][0], x*m[1][0], x*m[2][0], x*m[3][0],
		            y*m[0][1], y*m[1][1], y*m[2][1], y*m[3][1],
			        z*m[0][2], z*m[1][2], z*m[2][2], z*m[3][2],
			        w*m[0][3], w*m[1][3], w*m[2][3], w*m[3][3]);
	}
//@}

	/// (column scaling)
	friend inline const mat4 operator*(const mat4 &m, const diag4 &d) {	return mat4(m.x*d.x, m.y*d.y, m.z*d.z, m.w*d.w); }
	/// (column scaling)
	friend inline const mat4 &operator*=(mat4 &m, const diag4 &d) { m = d * m; return m; }

/// @name Comparison
//@{
	inline bool operator==(const diag4 &d) const { return to_vec4() == d.to_vec4(); }
	inline bool operator!=(const diag4 &d) const { return to_vec4() != d.to_vec4(); }
//@}

/// @name Conversion
//@{
	inline const diag3 &to_diag3() const { return *reinterpret_cast<const diag3*>(this); }
	inline diag3 &to_diag3() { return *reinterpret_cast<diag3*>(this); }
	inline const diag2 &to_diag2() const { return *reinterpret_cast<const diag2*>(this); }
	inline diag2 &to_diag2() { return *reinterpret_cast<diag2*>(this); }
	inline const vec4 &to_vec4() const { return *reinterpret_cast<const vec4*>(this); }
	inline vec4 &to_vec4() { return *reinterpret_cast<vec4*>(this); }
	inline const vec3 &to_vec3() const { return *reinterpret_cast<const vec3*>(this); }
	inline vec3 &to_vec3() { return *reinterpret_cast<vec3*>(this); }
	inline const vec2 &to_vec2() const { return *reinterpret_cast<const vec2*>(this); }
	inline vec2 &to_vec2() { return *reinterpret_cast<vec2*>(this); }
	inline const float *to_floats() const { return &x; }
	inline float *to_floats() { return &x; }
//@}

public:

	float x, y, z, w;

	static const diag4 identity;
};

//-----------------------------------------------------------------------------

}; // namespace Math
}; // namespace C3

#endif // __C3_MATH_DIAG_H__
