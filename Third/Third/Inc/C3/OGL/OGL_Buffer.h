#ifndef __C3_OGL_BUFFER_H__
#define __C3_OGL_BUFFER_H__

#include <OGL/OGL_Basics.h>
#include <OGL/OGL_Object.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------

class Buffer;

/// @name Buffer Functions
//@{
const Buffer CreateBuffer(const GLenum target, GLuint name = 0);
const Buffer DeleteBuffer(Buffer &buffer);

GLuint BufferBinding(const GLenum target);

bool BindBuffer(const GLenum target, const GLuint name);
bool BindBuffer(const Buffer &buffer);
//@}

//------------------------------------------------------------------------------
//==============================================================================
//
// Buffer Object
//

/**
	Try http://oss.sgi.com/projects/ogl-sample/registry/ARB/vertex_buffer_object.txt .
*/

class Buffer : public Object {

public:

/// @name Con-/Destruction
//@{
	inline Buffer()
		: Object(), _target(0) {}

	inline Buffer(const GLenum target, const GLuint name)
		: Object(name), _target(target) {}

	virtual ~Buffer() { /* No, we don't auto-delete objects! */ }
//@}

/// @name Object Validation
//@{
	inline bool ok() const { return glIsBuffer(name()) && targetValid(); }
//@}

	inline GLenum target() const { return _target; }

/// @name Parameters
//@{
	inline GLint parameteri(const GLenum pname) const {

		BindBuffer(*this);
		GLint pvalue;
		glGetBufferParameteriv(target(), pname, &pvalue);
		return pvalue;
	}

	inline GLint size()   const { return parameteri(GL_BUFFER_SIZE); }
	inline GLint usage()  const { return parameteri(GL_BUFFER_USAGE); }
	inline GLint access() const { return parameteri(GL_BUFFER_ACCESS); }
	inline GLint mapped() const { return parameteri(GL_BUFFER_MAPPED); }
//@}

/// @name Data I/O
//@{
	inline void data(const GLsizeiptr size, const void *data, const GLenum usage) {
		BindBuffer(*this); glBufferData(target(), size, data, usage);
	}

	inline void subData(const GLintptr offset, const GLsizeiptr size, const void *data) {
		BindBuffer(*this); glBufferSubData(target(), offset, size, data);
	}

	inline void getSubData(const GLintptr offset, const GLsizeiptr size, void *data) {
		BindBuffer(*this); glGetBufferSubData(target(), offset, size, data);
	}
//@}

/// @name Mapping
//@{
	inline void *map(const GLenum access) {
		return BindBuffer(*this) ? glMapBuffer(target(), access) : 0;
	}

	inline GLboolean unmap() {
		return BindBuffer(*this) ? glUnmapBuffer(target()) : GL_FALSE;
	}
//@}

private:

	inline bool targetValid() const {

		GLuint tb = BufferBinding(target());
		bool   tv = BindBuffer(target(), name());
		BindBuffer(target(), tb);
		return tv;
	}

private:

	GLenum _target;
};

//------------------------------------------------------------------------------
//==============================================================================
//
// Buffer Inlines
//

inline GLuint BufferBinding(const GLenum target) {

	static GLenum bbl[] = {GL_ARRAY_BUFFER_BINDING_ARB, GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB};
	return GetInteger(bbl[target-GL_ARRAY_BUFFER_ARB]);
}

inline bool BindBuffer(const GLenum target, const GLuint name) {

	if (BufferBinding(target) == name) return true;
	glBindBuffer(target, name);
	return BufferBinding(target) == name;
}

inline bool BindBuffer(const Buffer &buffer) {
	return BindBuffer(buffer.target(), buffer.name());
}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_BUFFER_H__
