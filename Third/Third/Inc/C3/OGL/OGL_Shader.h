#ifndef __C3_OGL_SHADER_H__
#define __C3_OGL_SHADER_H__

#include <C3_String.h>
#include <OGL/OGL_Basics.h>
#include <OGL/OGL_Object.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------

class Shader;

/// @name Shader Creation Flags
//@{
static const GLuint COMPILE = 0x00000001; ///< compiles shader at creation
//@}

/// @name Shader Functions
//@{
const Shader CreateShader(const GLenum type);

const Shader CreateShader(const GLenum type,
						  const GLchar *string,
						  const GLint  length,
						  const GLuint flags);

const Shader CreateShader(const GLenum type,
						  const GLchar *string,
						  const GLuint flags);

const Shader DeleteShader(Shader &shader);
//@}

//------------------------------------------------------------------------------
//==============================================================================
//
// Shader Object
//

class Shader : public Object {

public:

/// @name Con-/Destruction
//@{
	inline Shader()
		: Object() {}

	inline Shader(const GLuint name)
		: Object(name) {}

	virtual ~Shader() { /* No, we don't auto-delete objects! */ }
//@}

/// @name Object Validation
//@{
	inline bool ok() const { return glIsShader(name()) == GL_TRUE; }
//@}

/// @name Parameters
//@{
	inline GLint parameteri(const GLenum pname) const {

		GLint pvalue;
		glGetShaderiv(name(), pname, &pvalue);
		return pvalue;
	}

	inline GLint type()         const { return parameteri(GL_SHADER_TYPE); }
	inline GLint transient()    const { return parameteri(GL_DELETE_STATUS); }
	inline GLint compiled()     const { return parameteri(GL_COMPILE_STATUS); }
	inline GLint sourceLength() const { return parameteri(GL_INFO_LOG_LENGTH); }
	inline GLint logLength()    const { return parameteri(GL_SHADER_SOURCE_LENGTH); }
//@}

/// @name Compilation
//@{
	inline bool compile() {

		glCompileShader(name());
		return compiled() == 1;
	}
//@}

/// @name Source & Info Log Retrieval
//@{
	inline const String source() const {

		String _source;
		_source.resize(sourceLength());
		glGetShaderSource(name(), _source.capacity(), 0, const_cast<char*>(_source.chars()));
		return _source;
	}

	inline const String log() const {

		String _log;
		_log.resize(logLength());
		glGetShaderInfoLog(name(), _log.capacity(), 0, const_cast<char*>(_log.chars()));
		return _log;
	}
//@}
};

//------------------------------------------------------------------------------
//==============================================================================
//
// Shader Inlines
//

inline const Shader CreateShader(const GLenum type,
								 const GLchar *string,
								 const GLuint flags) {

	return CreateShader(type, string, 0, flags);
}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_SHADER_H__
