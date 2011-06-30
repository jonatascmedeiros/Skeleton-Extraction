#ifndef __C3_OGL_RENDERBUFFER_H__
#define __C3_OGL_RENDERBUFFER_H__

#include <OGL/OGL_Basics.h>
#include <OGL/OGL_Object.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------

class Renderbuffer;

/// @name Renderbuffer Functions
//@{
const Renderbuffer CreateRenderbuffer(GLuint name = 0);

const Renderbuffer CreateRenderbuffer(      GLuint  name,
									  const GLenum  internalFormat,
									  const GLsizei width,
									  const GLsizei height);

const Renderbuffer DeleteRenderbuffer(Renderbuffer &rb);

GLuint RenderbufferBinding();

bool BindRenderbuffer(const GLuint name);
bool BindRenderbuffer(const Renderbuffer &rb);
//@}

//------------------------------------------------------------------------------
//==============================================================================
//
// Renderbuffer Object
//

/**
	Try http://oss.sgi.com/projects/ogl-sample/registry/EXT/framebuffer_object.txt .
*/

class Renderbuffer : public Object {

public:

/// @name Con-/Destruction
//@{
	inline Renderbuffer()
		: Object() {}

	inline Renderbuffer(const GLuint name)
		: Object(name) {}

	virtual ~Renderbuffer() { /* No, we don't auto-delete objects! */ }
//@}

/// @name Object Validation
//@{
	inline bool ok() const { return glIsRenderbufferEXT(name()) == GL_TRUE; }
//@}

/// @name Parameters
//@{
	inline GLint parameteri(const GLenum pname) const {

		BindRenderbuffer(*this);
		GLint pvalue;
		glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT, pname, &pvalue);
		return pvalue;
	}

	inline GLint width()          const { return parameteri(GL_RENDERBUFFER_WIDTH_EXT); }
	inline GLint height()         const { return parameteri(GL_RENDERBUFFER_HEIGHT_EXT); }
	inline GLint internalFormat() const { return parameteri(GL_RENDERBUFFER_INTERNAL_FORMAT_EXT); }
//@}
};

//------------------------------------------------------------------------------
//==============================================================================
//
// Renderbuffer Inlines
//

inline GLuint RenderbufferBinding() {
	return GetInteger(GL_RENDERBUFFER_BINDING_EXT);
}

inline bool BindRenderbuffer(const GLuint name) {

	if (RenderbufferBinding() == name) return true;
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, name);
	return RenderbufferBinding() == name;
}

inline bool BindRenderbuffer(const Renderbuffer &rb) {
	return BindRenderbuffer(rb.name());
}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_RENDERBUFFER_H__
