#ifndef __C3_OGL_POLYGONMODE_H__
#define __C3_OGL_POLYGONMODE_H__

#include <OGL/OGL_Basics.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------

class PolygonMode;

/// @name PolygonMode Functions
//@{
void SetPolygonMode(const GLenum front, const GLenum back);
void SetPolygonMode(const PolygonMode &pm);

const PolygonMode ActivePolygonMode();
//@}

//------------------------------------------------------------------------------
//==============================================================================
//
// PolygonMode
//

class PolygonMode {

public:

/// @name Con-/Destruction
//@{
	inline PolygonMode(const GLenum front = GL_FILL,
	                   const GLenum back  = GL_FILL)
		: front(front), back(back) {}
//@}

/// @name Conversions
//@{
	const int *to_ints() const { return &front; }
	      int *to_ints()       { return &front; }
//@}

public:

	GLint front, back;
};

//------------------------------------------------------------------------------
//==============================================================================
//
// PolygonMode Inlines
//

inline void SetPolygonMode(const GLenum front, const GLenum back) {

	glPolygonMode(GL_FRONT, front);
	glPolygonMode(GL_BACK, back);
}

inline void SetPolygonMode(const PolygonMode &pm) {
	SetPolygonMode(pm.front, pm.back);
}

inline const PolygonMode ActivePolygonMode() {

	PolygonMode pm;
	glGetIntegerv(GL_POLYGON_MODE, pm.to_ints());
	return pm;
}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_POLYGONMODE_H__
