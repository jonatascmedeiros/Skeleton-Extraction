#ifndef __C3_MATH_SCALAR_H__
#define __C3_MATH_SCALAR_H__

namespace C3 {
namespace Math {

//------------------------------------------------------------------------------
//==============================================================================
//
/// @name Floating Point Constants

const float	PI    = 3.14159265358979323846f;
const float E     = 2.71828182845904523536f;
const float SQRT2 = 1.41421356237309504880f;

// to be continued...
/*
const float	FLT_INFINITY = 1e30f;
const float FLT_EPSILON  = 1.192092896e-07f; ///< float + EPSILON != float
*/
#define FLT_INF_BITS 0x7F800000
#define FLT_NAN_BITS 0x7F800001
/// @}

//------------------------------------------------------------------------------
//==============================================================================
//
/// @name Template Functions
template <class T> inline T min(const T a, const T b) {
	return (a < b) ? a : b;
}

template <class T> inline T max(const T a, const T b) {
	return (a > b) ? a : b;
}

template <class T> inline T sqr(const T x) {
	return x * x;
}

template <class T> inline T clamp(const T x, const T min, const T max) {
	return (x < max) ? (x < min) ? min : x : max;
}

template <class T> inline T wrap(const T x, const T min, const T max) {
	T _step(max - min), _x(x);
	if (_step > 0) {
		while (_x < min)  _x += _step;
		while (max <= _x) _x -= _step; // changed to <=
	}
	return _x;
}
/// @}

//------------------------------------------------------------------------------
//==============================================================================
//
/// @name Power-Of-Two Functions

inline bool is_pow2(const unsigned int x) {
	return !(x & (x - 1));
}

inline unsigned int next_pow2(const unsigned int x) {
	unsigned int y(1);
	for (; y && (y < x); y <<= 1);
	return y;
}
/// @}

//------------------------------------------------------------------------------
//==============================================================================
//
/// @name Reciprocal Square Roots

inline float rsqrtf(const float x) {
	return 1.0f / sqrtf(x);
}

inline float fast_rsqrtf(const float x) {
	long i;
	float y, r;
	y = x * 0.5f;
	i = *reinterpret_cast<const long *>(&x);
	i = 0x5f3759df - (i >> 1);
	r = *reinterpret_cast<float *>(&i);
	r = r * (1.5f - r * r * y);
	return r;
}
/// @}

//------------------------------------------------------------------------------
//==============================================================================
//
/// @name Misc Useful Functions

inline int sign(const int x) {

/*
	int sign((x & 0x80000000) >> 31);
	return -sign + (1-sign);
*/

//	return 1 - ((x & 0x80000000) >> 30);

	return (x) ? (1 - ((x & 0x80000000) >> 30)) : 0;
}

inline float sign(const float x) {
/*
	int i = *reinterpret_cast<const int *>(&x);
	return (i & 0x80000000) ? -1.0f : 1.0f;
*/

/*
	float r(1.0f);
	// transfer sign bit of x to r
	*reinterpret_cast<int*>(&r) |= ((*reinterpret_cast<const int*>(&x)) & 0x80000000);
	return r;
*/

	float r(1.0f);
	// transfer sign bit of x to r
	*reinterpret_cast<int*>(&r) |= ((*reinterpret_cast<const int*>(&x)) & 0x80000000);
	return (x) ? r : 0;
}

inline float fract(const float x) {
	return x - floor(x);
}

inline float trunc(const float x) {
	return static_cast<float>(static_cast<int>(x));
}

inline float round(const float x) {
	float f(floor(x));
	return f + static_cast<float>(static_cast<int>((x - f) * 2.0f));
}

inline float lerp(const float x, const float y, const float a) {
	return x + (y - x) * a;
}

inline float deg2rad(const float x) {
	return (PI / 180.0f) * x;
}

inline float rad2deg(const float x) {
	return (180.0f / PI) * x;
}
/// @}

//------------------------------------------------------------------------------
//==============================================================================
//
/// @name Special Floats

inline bool is_inf(const float x) {
	return (*reinterpret_cast<const int *>(&x) & FLT_INF_BITS) == FLT_INF_BITS;
}

inline bool is_nan(const float x) {
	return (*reinterpret_cast<const int *>(&x) & FLT_NAN_BITS) == FLT_NAN_BITS;
}
/// @}

//-----------------------------------------------------------------------------

}; // namespace Math
}; // namespace C3

#endif // __C3_MATH_SCALAR_H__
