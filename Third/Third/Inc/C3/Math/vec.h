#ifndef __C3_MATH_VEC_H__
#define __C3_MATH_VEC_H__

namespace C3 {
namespace Math {

//-----------------------------------------------------------------------------
//=============================================================================
//
// vec2
//
/// 2 floats
/*!
	<b>Instance members (since Doxygen can't handle unnamed stuff):</b><br>
	<br>
	unnamed union {<br>
		struct { float x, y; }; // common representation<br>
		struct { float u, v; }; // common texture coords<br>
		struct { float s, t; }; // OpenGL texture coords<br>
		struct { float w, h; }; // width, height<br>
		struct { float a, b; }; // misc<br>
	};
*/

class vec2 {

public:

/// @name Construction
//@{
	inline vec2()
		: x(0), y(0) {}
	explicit inline vec2(const float x, const float y)
		: x(x), y(y) {}
	explicit inline vec2(const float s)
		: x(s), y(s) {}
	template <typename T>
	explicit inline vec2(const T *ptr)
		: x(static_cast<float>(ptr[0]))
		, y(static_cast<float>(ptr[1])) {}
//@}

/// @name Array Operators
//@{
	inline const float &operator[](const int n) const { return (&x)[n]; }
	inline float &operator[](const int n) { return (&x)[n]; }
//@}

/// @name Negation
//@{
	inline const vec2 operator-() const { return vec2(-x, -y); }
//@}

/// @name Addition & Substraction
//@{
	inline const vec2 operator+(const float s) const { return vec2(x+s, y+s); }
	inline const vec2 &operator+=(const float s) { x+=s; y+=s; return *this; }
	inline const vec2 operator+(const vec2 &a) const { return vec2(x+a.x, y+a.y); }
	inline const vec2 &operator+=(const vec2 &a) { x+=a.x; y+=a.y; return *this; }
	inline const vec2 operator-(const float s) const { return vec2(x-s, y-s); }
	inline const vec2 &operator-=(const float s) { x-=s; y-=s; return *this; }
	inline const vec2 operator-(const vec2 &a) const { return vec2(x-a.x, y-a.y); }
	inline const vec2 &operator-=(const vec2 &a) { x-=a.x; y-=a.y; return *this; }
//@}

	/// float + vec := vec + float
	friend inline const vec2 operator+(const float s, const vec2 &a) { return a+s; }

/// @name Scaling (Component-Wise Multiplication/Division)
//@{
	inline const vec2 operator*(const float s) const { return vec2(s*x, s*y); }
	inline const vec2 &operator*=(const float s) { return *this = *this * s; }
	inline const vec2 operator*(const vec2 &s) const { return vec2(s.x*x, s.y*y); }
	inline const vec2 &operator*=(const vec2 &s) { return *this = *this * s; }
	inline const vec2 operator/(const float s) const { return vec2(x/s, y/s); }
	inline const vec2 &operator/=(const float s) { return *this = *this / s; }
	inline const vec2 operator/(const vec2 &s) const { return vec2(x/s.x, y/s.y); }
	inline const vec2 &operator/=(const vec2 &s) { return *this = *this / s; }
//@}

	/// float * vec := vec * float
	inline friend const vec2 operator*(const float s, const vec2 &a) { return a*s; }

/// @name Comparison
//@{
	inline bool operator==(const vec2 &a) const { return x == a.x && y == a.y; }
	inline bool operator!=(const vec2 &a) const { return x != a.x || y != a.y; }
//@}

/// @name Conversion
//@{
	inline const float *to_floats() const { return &x; }
	inline float *to_floats() { return &x; }
//@}

public:

	union {
		struct { float x, y; }; ///< common representation
		struct { float u, v; }; ///< common texture coords
		struct { float s, t; }; ///< OpenGL texture coords
		struct { float w, h; }; ///< width, height
		struct { float a, b; }; ///< misc
	};

	static const vec2 zero, one;
};

//-----------------------------------------------------------------------------
//=============================================================================
//
// vec3
//
/// 3 floats
/*!
	<b>Instance members (since Doxygen can't handle unnamed stuff):</b><br>
	<br>
	unnamed union {<br>
		struct { float x, y, z; }; // common representation<br>
		struct { float s, t, r; }; // OpenGL texture coords<br>
		struct { float w, h, d; }; // width, height, depth<br>
		struct { float a, b, c; }; // misc<br>
	};
*/

class vec3 {

public:

/// @name Construction
//@{
	inline vec3()
		: x(0), y(0), z(0) {}
	explicit inline vec3(const float x, const float y, const float z)
		: x(x), y(y), z(z) {}
	explicit inline vec3(const vec2 &v, const float z)
		: x(v.x), y(v.y), z(z) {}
	explicit inline vec3(const float *fp)
		: x(fp[0]), y(fp[1]), z(fp[2]) {}
	explicit inline vec3(const float s)
		: x(s), y(s), z(s) {}
	template <typename T>
	explicit inline vec3(const T *ptr)
		: x(static_cast<float>(ptr[0]))
		, y(static_cast<float>(ptr[1]))
		, z(static_cast<float>(ptr[2])) {}
//@}

/// @name Array Operators
//@{
	inline const float &operator[](const int n) const { return (&x)[n]; }
	inline float &operator[](const int n) { return (&x)[n]; }
//@}

/// @name Negation
//@{
	inline const vec3 operator-() const { return vec3(-x, -y, -z); }
//@}

/// @name Addition & Substraction
//@{
	inline const vec3 operator+(const float s) const { return vec3(x+s, y+s, z+s); }
	inline const vec3 &operator+=(const float s) { x+=s; y+=s; z+=s; return *this; }
	inline const vec3 operator+(const vec3 &a) const { return vec3(x+a.x, y+a.y, z+a.z); }
	inline const vec3 &operator+=(const vec3 &a) { x+=a.x; y+=a.y; z+=a.z; return *this; }
	inline const vec3 operator-(const float s) const { return vec3(x-s, y-s, z-s); }
	inline const vec3 &operator-=(const float s) { x-=s; y-=s; z-=s; return *this; }
	inline const vec3 operator-(const vec3 &a) const { return vec3(x-a.x, y-a.y, z-a.z); }
	inline const vec3 &operator-=(const vec3 &a) { x-=a.x; y-=a.y; z-=a.z; return *this; }
//@}

	/// float + vec := vec + float
	inline friend const vec3 operator+(const float s, const vec3 &a) { a+s; }

/// @name Scaling (Component-Wise Multiplication/Division)
//@{
	inline const vec3 operator*(const float s) const { return vec3(s*x, s*y, s*z); }
	inline const vec3 &operator*=(const float s) { return *this = *this * s; }
	inline const vec3 operator*(const vec3 &s) const { return vec3(s.x*x, s.y*y, s.z*z); }
	inline const vec3 &operator*=(const vec3 &s) { return *this = *this * s; }
	inline const vec3 operator/(const float s) const { return vec3(x/s, y/s, z/s); }
	inline const vec3 &operator/=(const float s) { return *this = *this / s; }
	inline const vec3 operator/(const vec3 &s) const { return vec3(x/s.x, y/s.y, z/s.z); }
	inline const vec3 &operator/=(const vec3 &s) { return *this = *this / s; }
//@}

	/// float * vec := vec * float
	inline friend const vec3 operator*(const float s, const vec3 &a) { return a*s; }

/// @name Comparison
//@{
	inline bool operator==(const vec3 &a) const { return x==a.x && y==a.y && z==a.z; }
	inline bool operator!=(const vec3 &a) const { return x!=a.x || y!=a.y || z!=a.z; }
//@}

/// @name Conversion
//@{
	inline const vec2 &to_vec2() const { return *reinterpret_cast<const vec2*>(this); }
	inline vec2 &to_vec2() { return *reinterpret_cast<vec2*>(this); }
	inline const float *to_floats() const { return &x; }
	inline float *to_floats() { return &x; }
//@}

public:

	union {
		struct { float x, y, z; }; ///< common representation
		struct { float s, t, r; }; ///< OpenGL texture coords
		struct { float w, h, d; }; ///< width, height, depth
		struct { float a, b, c; }; ///< misc
	};

	static const vec3 zero, one;
};


//-----------------------------------------------------------------------------
//=============================================================================
//
// vec4
//
/// 4 floats
/*!
	<b>Instance members (since Doxygen can't handle unnamed stuff):</b><br>
	<br>
	unnamed union {<br>
		struct { float x, y, z, w; }; // common representation<br>
		struct { float s, t, r, q; }; // OpenGL texture coords<br>
		struct { float a, b, c, d; }; // misc<br>
	};
*/

class vec4 {

public:

/// @name Construction
//@{
	inline vec4()
		: x(0), y(0), z(0), w(0) {}
	explicit inline vec4(const float x, const float y, const float z, const float w)
		: x(x), y(y), z(z), w(w) {}
	explicit inline vec4(const vec2 &v, const float z, const float w)
		: x(v.x), y(v.y), z(z), w(w) {}
	explicit inline vec4(const vec3 &v, const float w)
		: x(v.x), y(v.y), z(v.z), w(w) {}
	explicit inline vec4(const float s)
		: x(s), y(s), z(s), w(s) {}
	template <typename T>
	explicit inline vec4(const T *ptr)
		: x(static_cast<float>(ptr[0]))
		, y(static_cast<float>(ptr[1]))
		, z(static_cast<float>(ptr[2]))
		, w(static_cast<float>(ptr[3])) {}
//@}

/// @name Array Operators
//@{
	inline const float &operator[](const int n) const { return (&x)[n]; }
	inline float &operator[](const int n) { return (&x)[n]; }
//@}

/// @name Negation
//@{
	inline const vec4 operator-() const { return vec4(-x, -y, -z, -w); }
//@}

/// @name Addition & Substraction
//@{
	inline const vec4 operator+(const float s) const { return vec4(x+s, y+s, z+s, w+s); }
	inline const vec4 &operator+=(const float s) { x+=s; y+=s; z+=s; w+=s; return *this; }
	inline const vec4 operator+(const vec4 &a) const { return vec4(x+a.x, y+a.y, z+a.z, w+a.w); }
	inline const vec4 &operator+=(const vec4 &a) { x+=a.x; y+=a.y; z+=a.z; w+=a.w; return *this; }
	inline const vec4 operator-(const float s) const { return vec4(x-s, y-s, z-s, w-s); }
	inline const vec4 &operator-=(const float s) { x-=s; y-=s; z-=s; w-=s; return *this; }
	inline const vec4 operator-(const vec4 &a) const { return vec4(x-a.x, y-a.y, z-a.z, w-a.w); }
	inline const vec4 &operator-=(const vec4 &a) { x-=a.x; y-=a.y; z-=a.z; w-=a.w; return *this; }
//@}

	/// float + vec := vec + float
	friend inline const vec4 operator+(const float s, const vec4 &a) { a+s; }

/// @name Scaling (Component-Wise Multiplication/Division)
//@{
	inline const vec4 operator*(const float s) const { return vec4(s*x, s*y, s*z, s*w); }
	inline const vec4 &operator*=(const float s) { return *this = *this * s; }
	inline const vec4 operator*(const vec4 &s) const { return vec4(s.x*x, s.y*y, s.z*z, s.w*w); }
	inline const vec4 &operator*=(const vec4 &s) { return *this = *this * s; }
	inline const vec4 operator/(const float s) const { return vec4(x/s, y/s, z/s, w/s); }
	inline const vec4 &operator/=(const float s) { return *this = *this / s; }
	inline const vec4 operator/(const vec4 &s) const { return vec4(x/s.x, y/s.y, z/s.z, w/s.w); }
	inline const vec4 &operator/=(const vec4 &s) { return *this = *this / s; }
//@}

	/// float * vec := vec * float
	inline friend const vec4 operator*(const float s, const vec4 &a) { return a*s; }

/// @name Comparison
//@{
	inline bool operator==(const vec4 &a) const { return x==a.x && y==a.y && z==a.z && w==a.w; }
	inline bool operator!=(const vec4 &a) const { return x!=a.x || y!=a.y || z!=a.z || w!=a.w; }
//@}

/// @name Conversion
//@{
	inline const vec3 &to_vec3() const { return *reinterpret_cast<const vec3*>(this); }
	inline vec3 &to_vec3() { return *reinterpret_cast<vec3*>(this); }
	inline const vec2 &to_vec2() const { return *reinterpret_cast<const vec2*>(this); }
	inline vec2 &to_vec2() { return *reinterpret_cast<vec2*>(this); }
	inline const float *to_floats() const { return &x;	}
	inline float *to_floats() { return &x; }
//@}

public:

	union {
		struct { float x, y, z, w; }; ///< common representation
		struct { float s, t, r, q; }; ///< OpenGL tetxure coords
		struct { float a, b, c, d; }; ///< misc
	};

	static const vec4 zero, one;
};

//-----------------------------------------------------------------------------
//=============================================================================
//
// vector functions

/// @name Min/Max Component
//@{
inline float min(const vec2 &a) { return min(a.x, a.y); }
inline float min(const vec3 &a) { return min(min(a.x, a.y), a.z); }
inline float min(const vec4 &a) { return min(min(min(a.x, a.y), a.z), a.w); }

inline float max(const vec2 &a) { return max(a.x, a.y); }
inline float max(const vec3 &a) { return max(max(a.x, a.y), a.z); }
inline float max(const vec4 &a) { return max(max(max(a.x, a.y), a.z), a.w); }
//@}

/// @name Min/Max Component Vector
//@{
inline const vec2 min_components(const vec2 &a, const vec2 &b) { return vec2(min(a.x, b.x), min(a.y, b.y)); }
inline const vec3 min_components(const vec3 &a, const vec3 &b) { return vec3(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)); }
inline const vec4 min_components(const vec4 &a, const vec4 &b) { return vec4(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)); }

inline const vec2 max_components(const vec2 &a, const vec2 &b) { return vec2(max(a.x, b.x), max(a.y, b.y)); }
inline const vec3 max_components(const vec3 &a, const vec3 &b) { return vec3(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)); }
inline const vec4 max_components(const vec4 &a, const vec4 &b) { return vec4(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)); }
//@}

/// @name Vector Abs
//@{
inline const vec2 abs(const vec2 &a) { return vec2(fabsf(a.x), fabsf(a.y)); }
inline const vec3 abs(const vec3 &a) { return vec3(fabsf(a.x), fabsf(a.y), fabsf(a.z)); }
inline const vec4 abs(const vec4 &a) { return vec4(fabsf(a.x), fabsf(a.y), fabsf(a.z), fabsf(a.w)); }
//@}

/// @name Vector Floor
//@{
inline const vec2 floor(const vec2 &a) { return vec2(floorf(a.x), floorf(a.y)); }
inline const vec3 floor(const vec3 &a) { return vec3(floorf(a.x), floorf(a.y), floorf(a.z)); }
inline const vec4 floor(const vec4 &a) { return vec4(floorf(a.x), floorf(a.y), floorf(a.z), floorf(a.w)); }
//@}

/// @name Vector Ceil
//@{
inline const vec2 ceil(const vec2 &a) { return vec2(ceilf(a.x), ceilf(a.y)); }
inline const vec3 ceil(const vec3 &a) { return vec3(ceilf(a.x), ceilf(a.y), ceilf(a.z)); }
inline const vec4 ceil(const vec4 &a) { return vec4(ceilf(a.x), ceilf(a.y), ceilf(a.z), ceilf(a.w)); }
//@}

/// @name Vector Sign
//@{
inline const vec2 sign(const vec2 &a) { return vec2(sign(a.x), sign(a.y)); }
inline const vec3 sign(const vec3 &a) { return vec3(sign(a.x), sign(a.y), sign(a.z)); }
inline const vec4 sign(const vec4 &a) { return vec4(sign(a.x), sign(a.y), sign(a.z), sign(a.w)); }
//@}

/// @name Vector Fract
//@{
inline const vec2 fract(const vec2 &a) { return vec2(fract(a.x), fract(a.y)); }
inline const vec3 fract(const vec3 &a) { return vec3(fract(a.x), fract(a.y), fract(a.z)); }
inline const vec4 fract(const vec4 &a) { return vec4(fract(a.x), fract(a.y), fract(a.z), fract(a.w)); }
//@}

/// @name Vector Trunc
//@{
inline const vec2 trunc(const vec2 &a) { return vec2(trunc(a.x), trunc(a.y)); }
inline const vec3 trunc(const vec3 &a) { return vec3(trunc(a.x), trunc(a.y), trunc(a.z)); }
inline const vec4 trunc(const vec4 &a) { return vec4(trunc(a.x), trunc(a.y), trunc(a.z), trunc(a.w)); }
//@}

/// @name Vector Round
//@{
inline const vec2 round(const vec2 &a) { return vec2(round(a.x), round(a.y)); }
inline const vec3 round(const vec3 &a) { return vec3(round(a.x), round(a.y), round(a.z)); }
inline const vec4 round(const vec4 &a) { return vec4(round(a.x), round(a.y), round(a.z), round(a.w)); }
//@}

/// @name Dot Product
//@{
inline float dot(const vec2 &a, const vec2 &b) { return a.x*b.x + a.y*b.y; }
inline float dot(const vec3 &a, const vec3 &b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
inline float dot(const vec4 &a, const vec4 &b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }
//@}

/// @name Cross Product
//@{
inline const vec3 cross(const vec3 &a, const vec3 &b) {
	return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
//@}

/// @name Length Retrieval
//@{
template <typename T>
inline float length(const T &a) { return sqrtf(dot(a, a)); }

template <typename T>
inline float fast_length(const T &a) { float slen = dot(a, a); return slen * fast_rsqrtf(slen); }

template <typename T>
inline float sqr_length(const T &a) { return dot(a, a); }
//@}

/// @name Normalization
//@{
#define __NORMALIZE(x, f) float slen = dot(x, x); \
	                      float rlen = f(slen); \
	                      x *= rlen; \
	                      return rlen * slen

template <typename T>
inline float normalize(T &a)      { __NORMALIZE(a, rsqrtf); }

template <typename T>
inline float normalize_fast(T &a) { __NORMALIZE(a, fast_rsqrtf); }

#undef __NORMALIZE
//@}

/// @name Normal Retrieval
//@{
template <typename T>
inline const T normal(const T &a)      { T n(a); normalize(n); return n; }

template <typename T>
inline const T fast_normal(const T &a) { T n(a); normalize_fast(n); return n; }
//@}

/// @name Linear Interpolation
//@{
template <typename T>
inline const T lerp(const T &a, const T &b, const float w) { return a + (b - a) * w; }

template <typename T>
inline const T lerp(const T &a, const T &b, const T &w) { return a + (b - a) * w; }
//@}

/// @name Trigonometry
//@{
/// cos
template <typename T>
inline float cos(const T &a, const T &b) { return dot(a, b) / (length(a) * length(b)); }
/*
/// a's projection onto b
template <typename T>
inline const T project(const T &a, const T &b) { return (dot(a, b) / sqr_length(b)) * b; }

/// tan
template <typename T>
inline float tan(const T &a, const T &b) { T c(project(a, b)); return length(a - c) / length(a - c); }

/// cot
template <typename T>
inline float cot(const T &a, const T &b) { T c(project(a, b)); return length(a - c) / length(b - c); }
*/

// *****************************************************************************
// Author:	Justus Pett
// Date:	10/05/2007
// *****************************************************************************
// Projects a point onto a line with the specified direction vector. The 
// difference vector between point and it's orthogonal projection is returned
// *****************************************************************************
template <typename T>
inline const T project(const T &point, const T &lineDir, const T &linePoint) { 
	return point - linePoint - ((dot(lineDir, (point - linePoint)) / dot(lineDir, lineDir)) * lineDir); 
}

// *****************************************************************************
// Author:	Justus Pett
// Date:	10/05/2007
// *****************************************************************************
// Projects a point onto a line with the specified direction vector. The 
// difference vector between point and it's orthogonal projection is returned
// *****************************************************************************
template <typename T>
inline const T projectOnSegment(const T &point, const T &segStart, const T &segEnd, const bool handleNotProjectable = true) { 
	T edge = segEnd - segStart;

	float t = (dot(edge, (point - segStart)) / dot(edge, edge));

	if(t >= 0 && t <= 1)
		return point - segStart - (t * edge); 
	else {
		if(handleNotProjectable) {
			T dist1 = point - segStart;
			T dist2 = point - segEnd;

			return dot(dist1, dist1) < dot(dist2, dist2) ? dist1 : dist2;
		} // if
		else
			return T();
	} // else
}

template <typename T>
inline const T projectOnLine(const T &point, const T &lineStart, const T &lineEnd) { 
	T edge = lineEnd - lineStart;

	float t = (dot(edge, (point - lineStart)) / dot(edge, edge));

	return point - lineStart - (t * edge); 
	
}


inline const bool pointOnLine(const vec2 & linePoint1, const vec2 & linePoint2, const vec2 & point) {
	return ((point.x - linePoint1.x) * (linePoint2.x - linePoint1.x)) +
		   ((point.y - linePoint1.y) * (linePoint2.y - linePoint1.y)) < 0.00001f;
} // method lineDistance

// *****************************************************************************
// Author:	Justus Pett
// Date:	10/05/2007
// *****************************************************************************
// Projects a point onto a plane. 
// x: Point to project
// p: Point on the plane
// n: Plane normal (unit length!)
// *****************************************************************************
template <typename T>
inline const T projectPointOnPlane(const T &x, const T &p, const T &n) {
	//T y = (x - (dot(n, n) * x)) + (dot(n, n) * p);
	T y = p + ((x - p) - dot(n, x - p) * n);

	return y;
} // function projectPointOnPlane


/// cot
inline float cot(const vec3 &a, const vec3 &b) { return dot(a, b) / length(cross(a, b)); }

/// returns angle [-PI..PI] by vector
inline float signed_angle(const vec2 &a) {
	float angle = acosf(a.x / length(a));
	// transfer sign bit of a.y to angle
	*reinterpret_cast<int*>(&angle) |= ((*reinterpret_cast<const int*>(&a.y)) & 0x80000000);
	return angle;
}
/// returns angle [0..2PI] by vector
inline float unsigned_angle(const vec2 &a) {
	float angle = acosf(a.x / length(a));
	return (a.y < 0.0f) ? 2.0f * PI - angle : angle;
}
/// returns angle [-PI..PI] (right..left) between two vectors
inline float signed_angle(const vec2 &a, const vec2 &b) {
	// compute abs(angle(a, b))
	float angle = acosf(clamp(dot(a, b) / (length(a) * length(b)), -1.0f, 1.0f));
	// handle winding direction: transfer sign bit
	// angle *= (-a.y*b.x + a.x*b.y >= 0) ? 1.0f : -1.0f;
	float f = -a.y*b.x + a.x*b.y;
	*reinterpret_cast<int*>(&angle) |= (*reinterpret_cast<int*>(&f) & 0x80000000);
	return angle;
}
//@}

inline float unsigned_angle(const vec2 &a, const vec2 &b) {
	float angle = atan2f(b.y,b.x) - atan2(a.y,a.x);

	return angle;
}

// *****************************************************************************
// Author:	Justus Pett
// Date:	11/07/2007
// *****************************************************************************
// Returns the scalar values u and v that can be used to compute the point p
// with a as origin and b-a, c-a as base vectors.
// For a detailed description please refer to
// http://www.blackpawn.com/texts/pointinpoly/default.html
// *****************************************************************************
template <typename T>
void getUV(const T & a, const T & b, const T & c, const T & p, float * u, float * v) {
	// Compute vectors        
	T v0 = c - a;
	T v1 = b - a;
	T v2 = p - a;

	// Compute dot products
	float dot00 = dot(v0, v0);
	float dot01 = dot(v0, v1);
	float dot02 = dot(v0, v2);
	float dot11 = dot(v1, v1);
	float dot12 = dot(v1, v2);

	// Compute barycentric coordinates
	float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	*u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	*v = (dot00 * dot12 - dot01 * dot02) * invDenom;

} // method getUV


// *****************************************************************************
// Author:	Justus Pett
// Date:	11/07/2007
// *****************************************************************************
// Returns the angle between the two given vectors
// *****************************************************************************
inline float unsigned_angle(const vec3 &a, const vec3 &b) {
	float angle = rad2deg(acosf(clamp(dot(a, b) / (length(a) * length(b)), -1.0f, 1.0f)));
	return angle > 90.0f ? 180.0f - angle : angle;
}

// *****************************************************************************
// Author:	Justus Pett
// Date:	11/07/2007
// *****************************************************************************
// Returns the angle between the two given vectors
// *****************************************************************************
inline float signed_angle(const vec3 &a, const vec3 &b) {
	// compute abs(angle(a, b))
	float angle = acosf(clamp(dot(a, b) / (length(a) * length(b)), -1.0f, 1.0f));
	// handle winding direction: transfer sign bit
	// angle *= (-a.y*b.x + a.x*b.y >= 0) ? 1.0f : -1.0f;
	float f = -a.y*b.x + a.x*b.y;
	*reinterpret_cast<int*>(&angle) |= (*reinterpret_cast<int*>(&f) & 0x80000000);
	return rad2deg(angle);
}

/// @name Special Vecs
//@{
template <typename T>
inline bool is_inf(const T &a) { return is_inf(dot(a, a)); }

template <typename T>
inline bool is_nav(const T &a) { return is_nan(dot(a, a)); }
//@}

//-----------------------------------------------------------------------------

inline vec3 mid_point(const vec3 a, const vec3 b){
		return vec3((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
}


}; // namespace Math
}; // namespace C3

#endif // __C3_MATH_VEC_H__
