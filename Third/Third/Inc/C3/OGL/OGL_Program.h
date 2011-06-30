#ifndef __C3_OGL_PROGRAM_H__
#define __C3_OGL_PROGRAM_H__

#include <C3_Array.h>
#include <C3_String.h>
#include <OGL/OGL_Basics.h>
#include <OGL/OGL_Object.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------

class Program;

/// @name Program Creation/Deletion Flags
//@{
static const GLuint LINK         = 0x00000001; ///< link prog at creation
static const GLuint KEEP_SHADERS = 0x00000002; ///< don't delete attached shaders
//@}

/// @name Program Functions
//@{
const Program CreateProgram();

const Program CreateProgram(const Shader &vertShader,
							const Shader &fragShader,
							const GLuint flags);

const Program CreateProgram(const GLchar *vertSource,
							const GLchar *fragSource,
							const GLuint flags);

const Program DeleteProgram(Program &prog, const GLuint flags = 0);

const GLuint ActiveProgram();

bool UseProgram(const GLuint name);
bool UseProgram(const Program &prog);
//@}

//------------------------------------------------------------------------------
//==============================================================================
//
// ProgVarInfo
//

class ProgVarInfo {

	friend class Program;

public:

	inline ProgVarInfo() {}
	inline ProgVarInfo(const GLint size, const GLenum type, const String &name)
		: _size(size), _type(type), _name(name) {}

	inline GLint         size() const { return _size; }
	inline GLenum        type() const { return _type; }
	inline const String &name() const { return _name; }

	inline bool operator==(const ProgVarInfo &info) const {
		return (size() == info.size()) &&
		       (type() == info.type()) &&
			   (name() == info.name());
	}

private:

	GLint  _size;
	GLenum _type;
	String _name;
};

//------------------------------------------------------------------------------
//==============================================================================
//
// Program Object
//

class Program : public Object {

public:

/// @name Con-/Destruction
//@{
	inline Program() : Object() {}
	inline Program(const GLuint name) : Object(name) {}
	virtual ~Program() { /* No, we don't auto-delete objects! */ }
//@}

/// @name Object Validation
//@{
	inline bool ok() const { return glIsProgram(name()) == GL_TRUE; }
//@}

/// @name Parameters
//@{
	inline GLint parameteri(GLenum pname) const {
		GLint pvalue;
		glGetProgramiv(name(), pname, &pvalue);
		return pvalue;
	}

	inline GLint transient()        const { return parameteri(GL_DELETE_STATUS); }
	inline GLint linked()           const { return parameteri(GL_LINK_STATUS); }
	inline GLint validateStatus()   const { return parameteri(GL_VALIDATE_STATUS); }
	inline GLint logLength()        const { return parameteri(GL_INFO_LOG_LENGTH); }
	inline GLint numAttachments()   const { return parameteri(GL_ATTACHED_SHADERS); }
	inline GLint numAttributes()    const { return parameteri(GL_ACTIVE_ATTRIBUTES); }
	inline GLint attribNameRange()  const { return parameteri(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH); }
	inline GLint numUniforms()      const { return parameteri(GL_ACTIVE_UNIFORMS); }
	inline GLint uniformNameRange() const { return parameteri(GL_ACTIVE_UNIFORM_MAX_LENGTH); }
//@}

/// @name Attachments
//@{
	inline bool attach(const Shader &shader) {
		GLint count = numAttachments();
		glAttachShader(name(), shader.name());
		return numAttachments() == (++count);
	}

	inline bool detach(const Shader &shader) {
		GLint count = numAttachments();
		glDetachShader(name(), shader.name());
		return numAttachments() == (--count);
	}

	const Array<Shader> attachedShaders() const;
//@}

/// @name Linking & Program Validation
//@{
	bool link() {
		glLinkProgram(name());
		return linked() == GL_TRUE;
	}

	bool validate() const {
		glValidateProgram(name());
		return validateStatus() == GL_TRUE;
	}
//@}

/// @name Info Log Retrieval
//@{
	inline const String log() const {
		String _log;
		_log.resize(logLength());
		glGetProgramInfoLog(name(), _log.capacity(), 0, const_cast<char*>(_log.chars()));
		return _log;
	}
//@}

/// @name Attributes
//@{
	inline bool bindAttribLocation(GLuint index, const GLchar *name) {
		glBindAttribLocation(this->name(), index, name);
		return (GLuint)attribLocation(name) == index;
	}

	inline GLint attribLocation(const GLchar *name) const {
		return glGetAttribLocationARB(this->name(), name);
	}

	inline const ProgVarInfo getAttribInfo(GLuint index) const {
		ProgVarInfo info;
		info._name.resize(attribNameRange());
		glGetActiveAttrib(name(), index, info.name().capacity(), 0,
		                  &info._size, &info._type, const_cast<char*>(info._name.chars()));
		return info;
	}
//@}

/// @name Uniforms
//@{
	inline GLint uniformLocation(const GLchar *name) const {
		return glGetUniformLocation(this->name(), name);
	}

	inline const ProgVarInfo getUniformInfo(GLuint index) const {
		ProgVarInfo info;
		info._name.resize(uniformNameRange());
		glGetActiveUniform(name(), index, info.name().capacity(), 0,
		                   &info._size, &info._type, const_cast<char*>(info._name.chars()));
		return info;
	}
//@}
};

//------------------------------------------------------------------------------
//==============================================================================
//
// Program Inlines
//

inline const Program CreateProgram(const GLchar *vertSource,
						           const GLchar *fragSource,
							       GLuint flags) {

	return CreateProgram(CreateShader(GL_VERTEX_SHADER_ARB, vertSource, 0, COMPILE),
		                 CreateShader(GL_FRAGMENT_SHADER_ARB, fragSource, 0, COMPILE),
						 flags);
}

inline const GLuint ActiveProgram() {
	return GetInteger(GL_CURRENT_PROGRAM);
}

inline bool UseProgram(const GLuint name) {
	if (ActiveProgram() != name) {
		glUseProgram(name);
		return ActiveProgram() == name;
	} else {
		return true;
	}
}

inline bool UseProgram(const Program &prog) {
	return UseProgram(prog.name());
}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_PROGRAM_H__
