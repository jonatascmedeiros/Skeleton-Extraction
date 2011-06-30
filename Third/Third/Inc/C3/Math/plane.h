#ifndef __C3_MATH_PLANE_H__
#define __C3_MATH_PLANE_H__

namespace C3 {
namespace Math {

//-----------------------------------------------------------------------------
//=============================================================================
//
// plane4
//
/// 4 floats plane equation
/*!
	<b>Instance members (since Doxygen can't handle unnamed stuff):</b><br>
	<br>
	unnamed union {<br>
		struct { float x, y, z, d; }; // normal distance representation<br>
		struct { float a, b, c, d; }; // plane equation components<br>
	};
*/

class plane4 {

public:

/// @name Construction
//@{
	inline plane4() {}
	inline plane4(const float x, const float y, const float z, const float d)
		: x(x), y(y), z(z), d(d) {}
	inline plane4(const vec3 &n, const float d) { normal() = n; this->d = d; }
	inline plane4(const vec3 &v, const vec3 &n) { normal() = n; d = dot(v, n); }
//@}

/// @name Array Operators (Component Retrieval)
//@{
	inline const float operator[](unsigned int n) const { return (&x)[n]; }
	inline float &operator[](unsigned int n) { return (&x)[n]; }
//@}

/// @name Normal Retrieval
//@{
	inline const vec3 &normal() const {	return *reinterpret_cast<const vec3 *>(&x);	}
	inline vec3 &plane4::normal() {	return *reinterpret_cast<vec3 *>(&x); }
//@}

/// @name Negation
//@{
	inline const plane4 operator-() const { return plane4(x, y, z, -d); }
//@}

/// @name Translation Along Normal
//@{
	inline const plane4 operator+(const float f) const { return plane4(normal(), d + f); }
	inline const plane4 &operator+=(const float f) { return *this = *this + f; }
//@}

/// @name Translation - NOTE: plane must be normalized !
//@{
	inline const plane4 operator+(const vec3 &v) const { return plane4(normal(), d + v * normal());	}
	inline const plane4 &operator+=(const vec3 &v) { return *this = *this + v; }
//@}

/// @name Rotation - NOTE: plane must be normalized !
//@{
	inline const plane4 operator*(const mat3 &m) const { return plane4(m * normal(), d); }
	inline const plane4 &operator*=(const mat3 &m) { return *this = *this * m; }
//@}

/// @name Transformation - NOTE: plane must be normalized !
//@{
	inline const plane4 operator*(const modelview4 &m) const { return plane4(m * (-d * normal()), m * normal()); }
	inline const plane4 &operator*=(const modelview4 &m) { return *this = *this * m; }
//@}

/// @name Comparison
//@{
	inline int operator==(const plane4 &a) const { return x==a.x && y==a.y && z==a.z && d==a.d; }
	inline int operator!=(const plane4 &a) const { return x!=a.x || y!=a.y || z!=a.z || d!=a.d; }
//@}

/// @name Conversion
//@{
	inline const vec4 &to_vec4() const { return *reinterpret_cast<const vec4 *>(&x); }
	inline vec4 &to_vec4() { return *reinterpret_cast<vec4 *>(&x); }
	inline const float *to_floats() const { return reinterpret_cast<const float *>(&x); }
	inline float *to_floats() { return reinterpret_cast<float *>(&x); }
//@}

public:

	union {
		struct { float x, y, z, d; }; ///< normal distance representation
		struct { float a, b, c, d; }; ///< plane component representation
	};

	static const plane4 xy, yz, xz;
};

//-----------------------------------------------------------------------------
//=============================================================================
//
// plane functions

/// @name Plane Setup (normal pointing plane |-> front)
//@{
/// counter clockwise front
inline const plane4 plane_ccw(const vec3 &v1, const vec3 &v2, const vec3 &v3) {
	plane4 p;
	p.normal() = cross(v3 - v2, v1 - v2);
	p.d = -dot(p.normal(),  v2);
	return p;
}
/// clockwise front
inline const plane4 plane_cw(const vec3 &v1, const vec3 &v2, const vec3 &v3) {
	plane4 p;
	p.normal() = cross(v1 - v2, v3 - v2);
	p.d = -dot(p.normal(), v2);
	return p;
}
//@}

/// @name Plane Normalization
//@{
#define __NORMALIZE(p, f) float slen = dot(p.normal(), p.normal()); \
                          float rlen = rsqrtf(slen); \
	                      p.to_vec4() *= rlen; \
	                      return rlen * slen

inline float normalize(plane4 &p) { __NORMALIZE(p, rsqrtf); }
inline float normalize_fast(plane4 &p) { __NORMALIZE(p, fast_rsqrtf); }

#undef __NORMALIZE
//@}

//-----------------------------------------------------------------------------

}; // namespace Math
}; // namespace C3

#endif // __C3_MATH_PLANE_H__
