#ifndef __C3_OGL_OBJECT_H__
#define __C3_OGL_OBJECT_H__

#include <OGL/OGL_Basics.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------
//==============================================================================
//
// Object
//

class Object {

public:

/// @name Con-/Destruction
//@{
	inline Object()	: _name(0) {}
	inline Object(const GLuint name) : _name(name) {}
	virtual ~Object() { /* No, we don't auto-delete objects! */ }
//@}

	inline GLuint name() const { return _name; }

private:

	GLuint _name;
};

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_OBJECT_H__
