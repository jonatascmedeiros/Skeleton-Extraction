#ifndef __C3_MATH_MODELVIEW_H__
#define __C3_MATH_MODELVIEW_H__

namespace C3 {
namespace Math {

//-----------------------------------------------------------------------------
//=============================================================================
//
// some forewards

class modelview4;

bool invert(modelview4 &m, const float epsilon);

//-----------------------------------------------------------------------------
//=============================================================================
//
// modelview4
//
/// 3x4 floats := (mat3, vec3)

class modelview4 {

public:

/// @name Construction - NOTE: modelview4(floats) in transposed notation!!!
//@{
	inline modelview4() {}
	inline modelview4(const float xx, const float yx, const float zx, const float tx,
		              const float xy, const float yy, const float zy, const float ty,
		              const float xz, const float yz, const float zz, const float tz)
		: r(vec3(xx, xy, xz), vec3(yx, yy, yz), vec3(zx, zy, zz)), t(vec3(tx, ty, tz)) {}
	inline modelview4(const vec3 &vx, const vec3 &vy, const vec3 &vz, const vec3 &vt)
		: r(vx, vy, vz), t(vt) {}
	inline explicit modelview4(const mat3 &r, const vec3 &t)
		: r(r), t(t) {}
	inline explicit modelview4(const diag3 &d, const vec3 &t)
		: r(vec3(d.x, 0, 0), vec3(0, d.y, 0), vec3(0, 0, d.z)), t(t) {}
	inline explicit modelview4(const mat3 &r)
		: r(r), t(vec3::zero) {}
	inline explicit modelview4(const diag3 &d)
		: r(vec3(d.x, 0, 0), vec3(0, d.y, 0), vec3(0, 0, d.z)), t(vec3::zero) {}
	inline explicit modelview4(const vec3 &t)
		: r(mat3::identity), t(t) {}
//@}

/// @name Scaling
//@{
	inline const modelview4 operator*(const float s) const { return modelview4(r*s, t*s); }
	inline const modelview4 &operator*=(const float s) { return *this = *this * s; }
	inline const modelview4 operator*(const diag3 &s) const { return modelview4(r*s, t*s.to_vec3()); }
	inline const modelview4 &operator*=(const diag3 &s) { return *this = *this * s; }
	inline const modelview4 operator*(const diag4 &s) const { return modelview4(r*s.to_diag3(), t*s.to_vec3()); }
	inline const modelview4 &operator*=(const diag4 &s) { return *this = *this * s; }
//@}

	/// float * modelview
	friend inline const modelview4 operator*(const float s, const modelview4 &m) { return m * s; }
	/// diag * modelview
	friend inline const modelview4 operator*(const diag3 &s, const modelview4 &m) { return modelview4(s*m.r, s*m.t); }
	/// diag * modelview
	friend inline const modelview4 operator*(const diag4 &s, const modelview4 &m) { return modelview4(s.to_diag3()*m.r, s.to_diag3()*m.t); }

/// @name Translation
//@{
	inline const modelview4 operator+(const vec3 &t) const { return modelview4(r, this->t+t); }
	inline const modelview4 &operator+=(const vec3 &t) { this->t += t; return *this; }
	inline const modelview4 operator-(const vec3 &t) const { return modelview4(r, this->t-t); }
	inline const modelview4 &operator-=(const vec3 &t) { this->t -= t; return *this; }
//@}

/// @name Rotation
//@{
	inline const modelview4 operator*(const mat3 &r) const { return modelview4(this->r*r, t); }
	inline const modelview4 &operator*=(const mat3 &r) { return *this = *this * r; }
//@}

	/// rotation * modelview
	friend inline const modelview4 operator*(const mat3 &r, const modelview4 &m) { return modelview4(r*m.r, r*m.t); }

/// @name Transformation
//@{
	inline const vec3 operator*(const vec3 &v) const { return vec3((r*v)+t); }
	inline const modelview4 operator*(const modelview4 &m) const { return modelview4((r*m.r), (r*m.t)+t); }
	inline const modelview4 &operator*=(const modelview4 &m) { return *this = *this * m; }
//@}

/// @name Inverse Retrieval
//@{
	inline const modelview4 operator!() const { modelview4 m(*this); invert(m, MAT_INVERSE_EPSILON); return m; }
//@}

public:

	mat3 r;
	vec3 t;

	static const modelview4 identity;
};

//-----------------------------------------------------------------------------
//=============================================================================
//
// modelview4 functions

/// @name Modelview Inversion
//@{
inline bool invert(modelview4 &m, const float epsilon = MAT_INVERSE_EPSILON) {
	if (!invert(m.r, epsilon)) return false;
	m.t = -(m.r * m.t);
	return true;
}
//@}

//-----------------------------------------------------------------------------

}; // namespace Math
}; // namespace C3

#endif // __C3_MATH_MODELVIEW_H__
