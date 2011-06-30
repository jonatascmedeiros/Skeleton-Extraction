#ifndef __C3_OGL_CULLING_H__
#define __C3_OGL_CULLING_H__

#include <OGL/OGL_Basics.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------

class Culling;

/// @name Culling Functions
//@{
void SetCulling(const GLenum front, const GLenum mode, const bool enabled);
void SetCulling(const Culling &c);

const Culling ActiveCulling();
//@}

//------------------------------------------------------------------------------
//==============================================================================
//
// Culling
//

class Culling {

public:

/// @name Con-/Destruction
//@{
	inline Culling(const GLenum front   = GL_CCW,
	               const GLenum mode    = GL_BACK,
				   const bool   enabled = false)
		: front(front), mode(mode), enabled(enabled) {}
//@}

public:

	GLenum front;
	GLenum mode;
	bool   enabled;
};

//------------------------------------------------------------------------------
//==============================================================================
//
// Culling Inlines
//

inline void SetCulling(const GLenum front, const GLenum mode, const bool enabled) {

	glFrontFace(front);
	glCullFace(mode);
	if (enabled) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
}

inline void SetCulling(const Culling &c) {
	SetCulling(c.front, c.mode, c.enabled);
}

inline const Culling ActiveCulling() {

	Culling c;
	c.front   = GetInteger(GL_FRONT_FACE);
	c.mode    = GetInteger(GL_CULL_FACE_MODE);
	c.enabled = glIsEnabled(GL_CULL_FACE) == GL_TRUE;
	return c;
}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_CULLING_H__
