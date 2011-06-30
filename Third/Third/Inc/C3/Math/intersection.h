#ifndef __C3_MATH_INTERSECTION_H__
#define __C3_MATH_INTERSECTION_H__

namespace C3 {
namespace Math {

//-----------------------------------------------------------------------------
//=============================================================================
//
// intersection
//

/// @name Line Intersection - see http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/
//@{

/// := 0.0f if (p1,p2)||(p3,p4)
inline float isp_d(const vec2 &p1, const vec2 &p2, const vec2 &p3, const vec2 &p4) {
	return ((p4.y-p3.y)*(p2.x-p1.x))-((p4.x-p3.x)*(p2.y-p1.y));
}

/// [isp((p1,p2),(p3,p4)) within (p1,p2)] <=>  [0 <= isp_u.x <= 1], (p3,p4)/isp_u.y analog
inline const vec2 isp_u(const vec2 &p1, const vec2 &p2, const vec2 &p3, const vec2 &p4, const float d) {
	vec2 p13(p1-p3);
	return vec2(((p4.x-p3.x)*p13.y)-((p4.y-p3.y)*p13.x),
	            ((p2.x-p1.x)*p13.y)-((p2.y-p1.y)*p13.x)) / d;
}

/// false if (p1,p2)||(p3,p4), true otherwise; *p := isp if ex isp & p != 0
bool isp(const vec2 &p1, const vec2 &p2, const vec2 &p3, const vec2 &p4, vec2 *p = 0);

/// false if (p1,p2)||(p3,p4) or isp exceeds segs, true otherwise; *p := s.a.
bool seg_isp(const vec2 &p1, const vec2 &p2, const vec2 &p3, const vec2 &p4, vec2 *p = 0);
bool seg_isp(const vec2 &p1, const vec2 &p2, const vec2 &p3, const vec2 &p4, float *t);
//@}


// *****************************************************************************
// Author:	Justus Pett
// Date:	11/07/2007
// *****************************************************************************
// Checks whether the point p lies inside the triangle defined by the points
// a, b, c. For a detailed description please refer to
// http://www.blackpawn.com/texts/pointinpoly/default.html
// *****************************************************************************
const bool pointInTriangle(const vec2 & a, const vec2 & b, const vec2 & c, const vec2 & p);

// *****************************************************************************
// Author:	Justus Pett
// Date:	11/07/2007
// *****************************************************************************
// Calculates the area of a triangle
// http://www.mathopenref.com/heronsformula.html
// *****************************************************************************
const float triangleArea(const vec3 & a, const vec3 & b, const vec3 & c);


// *****************************************************************************
// Author:	Justus Pett
// Date:	01/11/2008
// *****************************************************************************
// Returns the intersection point of a line with a plane.
// Also see http://local.wasp.uwa.edu.au/~pbourke/geometry/planeline/
// *****************************************************************************
const vec3 ispLinePlane(const vec3 &linePoint1, const vec3 & linePoint2, 
						const vec3 &planePoint, const vec3 & planeNormal);


//-----------------------------------------------------------------------------

}; // namespace Math
}; // namespace C3

#endif // __C3_MATH_INTERSECTION_H__
