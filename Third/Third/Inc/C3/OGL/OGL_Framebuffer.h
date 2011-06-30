#ifndef __C3_OGL_FRAMEBUFFER_H__
#define __C3_OGL_FRAMEBUFFER_H__

#include <OGL/OGL_Basics.h>
#include <OGL/OGL_Object.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------

class Framebuffer;
class Renderbuffer;

/// @name Framebuffer Functions
//@{
const Framebuffer CreateFramebuffer(GLuint name = 0);
const Framebuffer CreateFramebuffer(const Texture &colors);
const Framebuffer CreateFramebuffer(const Texture &colors, const Texture &depths);
const Framebuffer CreateFramebuffer(const Texture &colors, const Renderbuffer &depths);

const Framebuffer DeleteFramebuffer(Framebuffer &fb);

GLuint FramebufferBinding();

bool BindFramebuffer(const GLuint name);

bool BindFramebuffer(const Framebuffer &fb);

void GenerateMipmap(const GLenum target);
//@}

//------------------------------------------------------------------------------
//==============================================================================
//
// Framebuffer Object
//

/**
	Try http://oss.sgi.com/projects/ogl-sample/registry/EXT/framebuffer_object.txt .
*/

class Framebuffer : public Object {

public:

/// @name Con-/Destruction
//@{
	inline Framebuffer()
		: Object() {}

	inline Framebuffer(const GLuint name)
		: Object(name) {}

	virtual ~Framebuffer() { /* No, we don't auto-delete objects! */ }
//@}

/// @name Object Validation
//@{
	inline bool ok() const { return glIsFramebufferEXT(name()) == GL_TRUE; }
//@}

/// @name Status
//@{
	inline GLenum status() const {
		BindFramebuffer(*this); return glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	}

	inline bool complete() const {
		return status() == GL_FRAMEBUFFER_COMPLETE_EXT;
	}
///@}

/// @name Attachments
//@{
	bool attach(const GLenum       attachment,
	            const Renderbuffer &rb);

	bool attach(const GLenum  attachment,
	            const Texture &tex,
				const GLint   level = 0,
				const GLint   zoffset = 0);
//@}

/// @name Attachment Parameters
//@{
	inline GLint attachmentParameteri(const GLenum attachment, const GLenum pname) const {

		BindFramebuffer(*this);
		GLint pvalue;
		glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT, attachment, pname, &pvalue);
		return pvalue;
	}

	inline GLint attachmentType(const GLenum attachment) const {
		return attachmentParameteri(attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT);
	}

	inline GLint attachmentName(const GLenum attachment) const {
		return attachmentParameteri(attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT);
	}

	inline GLint attachmentTexLevel(const GLenum attachment) const {
		return attachmentParameteri(attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT);
	}

	inline GLint attachmentTexCubeMapFace(const GLenum attachment) const {
		return attachmentParameteri(attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT);
	}

	inline GLint attachmentTex3DZOffset(const GLenum attachment) const {
		return attachmentParameteri(attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT);
	}
//@}
};

//------------------------------------------------------------------------------
//==============================================================================
//
// Framebuffer Inlines
//

inline GLuint FramebufferBinding() {
	return GetInteger(GL_FRAMEBUFFER_BINDING_EXT);
}

inline bool BindFramebuffer(const GLuint name) {
	if (FramebufferBinding() == name) return true;
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, name);
	return FramebufferBinding() == name;
}

inline bool BindFramebuffer(const Framebuffer &fb) {
	return BindFramebuffer(fb.name());
}

inline void GenerateMipmap(const GLenum target) {
	glGenerateMipmapEXT(target);
}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_FRAMEBUFFER_H__
