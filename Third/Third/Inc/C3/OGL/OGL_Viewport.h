#ifndef __C3_OGL_VIEWPORT_H__
#define __C3_OGL_VIEWPORT_H__

#include <OGL/OGL_Basics.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------

class Viewport;

/// @name Viewport Functions
//@{
void SetViewport(const Viewport &vp);

const Viewport ActiveViewport();
//@}

//------------------------------------------------------------------------------
//==============================================================================
//
// Viewport
//

class Viewport {

public:

/// @name Con-/Destruction
//@{
	inline Viewport() {}

	inline Viewport(const int x,const int y, const int w, const int h)
		: x(x), y(y), w(w), h(h) {}
//@}

/// @name Aspect Retrieval
//@{
	inline float aspect() const { return (float)w/h; }
//@}

/// @name Conversions
//@{
	const int *to_ints() const { return &x; }
	      int *to_ints()       { return &x; }
//@}

public:

	int x, y, w, h;
};

//------------------------------------------------------------------------------
//==============================================================================
//
// Viewport Inlines
//

inline void SetViewport(const Viewport &vp) {

	glViewport(vp.x, vp.y, vp.w, vp.h);
}

inline const Viewport ActiveViewport() {

	Viewport vp;
	glGetIntegerv(GL_VIEWPORT, vp.to_ints());
	return vp;
}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_VIEWPORT_H__
