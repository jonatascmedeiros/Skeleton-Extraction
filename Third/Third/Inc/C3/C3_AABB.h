#ifndef __C3_AXIS_ALIGNED_BOUNDING_BOX_H__
#define __C3_AXIS_ALIGNED_BOUNDING_BOX_H__

#include <C3_Math.h>
#include <C3_OpenGL.h>

namespace C3 {

using namespace Math;

//-----------------------------------------------------------------------------
//==============================================================================
//
// AABB2
//

class AABB2 {

public:

	inline AABB2()
		: min(vec2::zero), max(vec2::zero) {}
	inline AABB2(const vec2 &a, const vec2 &b)
		: min(a), max(a) { extend(b); }

	inline void extend(const vec2 &a) {

		min = min_components(min, a);
		max = max_components(max, a);
	}

	inline bool contains(const vec2 &a) const {

		return 	min.x < a.x && a.x < max.x &&
		        min.y < a.y && a.y < max.y;
	}

	inline bool covers(const vec2 &a) const {

		return 	min.x <= a.x && a.x <= max.x &&
		        min.y <= a.y && a.y <= max.y;
	}

	inline bool clips(const vec2 &a) const {

		return !covers(a);
	}

public:

	vec2 min, max;
};

//-----------------------------------------------------------------------------
//==============================================================================
//
// AABB3
//

class AABB3 {

public:

	inline AABB3()
		: min(vec3::zero), max(vec3::zero) {}
	inline AABB3(const vec3 &a, const vec3 &b)
		: min(a), max(a) { extend(b); }

	inline void extend(const vec3 &a) {

		min = min_components(min, a);
		max = max_components(max, a);
	}

	inline bool contains(const vec3 &a) const {

		return 	min.x < a.x && a.x < max.x &&
		        min.y < a.y && a.y < max.y &&
				min.z < a.z && a.z < max.z;
	}

	inline bool covers(const vec3 &a) const {

		return 	min.x <= a.x && a.x <= max.x &&
		        min.y <= a.y && a.y <= max.y &&
				min.z <= a.z && a.z <= max.z;
	}

	inline bool clips(const vec3 &a) const {

		return !covers(a);
	}

public:

	vec3 min, max;
};

//-----------------------------------------------------------------------------

}; // namespace C3

#endif __C3_AXIS_ALIGNED_BOUNDING_BOX_H__
