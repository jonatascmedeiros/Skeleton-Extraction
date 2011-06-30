#ifndef __C3_OGL_DEPTHTEST_H__
#define __C3_OGL_DEPTHTEST_H__

#include <OGL/OGL_Basics.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------

class DepthTest;

/// @name DepthTest Functions
//@{
void SetDepthTest(const GLenum func, const bool enabled);
void SetDepthTest(const DepthTest &dt);

const DepthTest ActiveDepthTest();
//@}

//------------------------------------------------------------------------------
//==============================================================================
//
// DepthTest
//

class DepthTest {

public:

/// @name Con-/Destruction
//@{
	inline DepthTest(const GLenum func    = GL_LESS,
	                 const bool   enabled = false)
		: func(func), enabled(enabled) {}
//@}

public:

	GLenum func;
	bool   enabled;
};

//------------------------------------------------------------------------------
//==============================================================================
//
// DepthTest Inlines
//

inline void SetDepthTest(const GLenum func, const bool enabled) {

	glDepthFunc(func);
	if (enabled) {
		glEnable(GL_DEPTH_TEST);
	} else {
		glDisable(GL_DEPTH_TEST);
	}
}

inline void SetDepthTest(const DepthTest &dt) {
	SetDepthTest(dt.func, dt.enabled);
}

inline const DepthTest ActiveDepthTest() {

	DepthTest dt;
	dt.func    = GetInteger(GL_DEPTH_FUNC);
	dt.enabled = glIsEnabled(GL_DEPTH_TEST) == GL_TRUE;
	return dt;
}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_DEPTHTEST_H__
