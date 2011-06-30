#ifndef __C3_OGL_BASICS_H__
#define __C3_OGL_BASICS_H__

#include <gl/glew.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------

/// @name Bascis Functions
GLint   GetInteger(const GLenum pname);
GLfloat GetFloat(const GLenum pname);

const char *EnumString(const GLenum value);
//GLint       EnumValue(const char *str) { return 0; }
/// @}

//------------------------------------------------------------------------------
//==============================================================================
//
// Basic Function Inlines
//

inline GLint GetInteger(const GLenum pname) {

	GLint pvalue;
	glGetIntegerv(pname, &pvalue);
	return pvalue;
}

inline GLfloat GetFloat(const GLenum pname) {

	GLfloat pvalue;
	glGetFloatv(pname, &pvalue);
	return pvalue;
}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_BASICS_H__
