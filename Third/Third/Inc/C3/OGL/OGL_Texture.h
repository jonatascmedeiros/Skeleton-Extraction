#ifndef __C3_OGL_TEXTURE_H__
#define __C3_OGL_TEXTURE_H__

#include <OGL/OGL_Basics.h>
#include <OGL/OGL_Object.h>

namespace C3 {
namespace OGL {

//------------------------------------------------------------------------------

class Texture;

/// @name Texture Functions
//@{
const Texture CreateTexture(const GLenum target,
							      GLuint name = 0);

const Texture CreateTexture(const GLenum  target,
							      GLuint  name,
                            const GLint   internalFormat,
	                        const GLsizei width,
							const GLsizei height = 0,
							const GLsizei depth = 0);

const Texture CreateTexture(const GLint   internalFormat,
	                        const GLsizei width,
							const GLsizei height = 0,
							const GLsizei depth = 0);

const Texture DeleteTexture(Texture &tex);

GLuint TextureBinding(const GLenum target);

bool BindTexture(const GLenum target,
				 const GLuint name);

bool BindTexture(const Texture &tex);
//@}

/// @name Texture Related Functions
//@{
bool IsComponentEnum(const GLenum format);
bool IsAbstractFormat(const GLenum format);
bool IsInternalFormat(const GLenum format);

GLenum ComponentEnum(const GLenum format);
int    NumComponents(const GLenum format);
GLenum GuessComponentEnum(const GLint numComp);

int BytesPerPixel(const GLenum compEnum,
				  const GLenum compType);

int BitsPerTexel(const GLenum internalFormat);

float CompressionFactor(const GLenum internalFormat);

GLsizei TexSize(const GLint   internalFormat,
                const GLsizei width,
				const GLsizei height,
				const GLsizei depth,
                const GLsizei align);

GLsizei TexImageSize(const GLenum  format,
					 const GLenum  type,
                     const GLsizei width,
					 const GLsizei height,
					 const GLsizei depth,
                     const GLsizei align);

GLenum GuessTarget(const GLsizei width,
				   const GLsizei height,
				   const GLsizei depth);
//@}

//------------------------------------------------------------------------------
//==============================================================================
//
// Texture Object
//

class Texture : public Object {

public:

/// @name Con-/Destruction
//@{
	inline Texture()
		: Object() {}

	inline Texture(const GLenum target, const GLuint name)
		: Object(name), _target(target) {}

	virtual ~Texture() { /* No, we don't auto-delete objects! */ }
//@}

/// @name Object Validation
//@{
	inline bool ok() const { return glIsTexture(name()) && targetValid(); }
//@}

	inline GLenum target() const { return _target; }

/// @name Parameters
//@{
	inline GLint parameteri(const GLenum pname) const {

		BindTexture(*this);
		GLint pvalue;
		glGetTexParameteriv(target(), GL_TEXTURE_MIN_FILTER, &pvalue);
		return pvalue;
	}

	inline GLint minFilter()    const { return parameteri(GL_TEXTURE_MIN_FILTER); }
	inline GLint magFilter()    const { return parameteri(GL_TEXTURE_MAG_FILTER); }
	inline GLint minLOD()       const { return parameteri(GL_TEXTURE_MIN_LOD); }
	inline GLint maxLOD()       const { return parameteri(GL_TEXTURE_MAX_LOD); }
	inline GLint minBaseLevel() const { return parameteri(GL_TEXTURE_BASE_LEVEL); }
	inline GLint minMaxLevel()  const { return parameteri(GL_TEXTURE_MAX_LEVEL); }
	inline GLint minWrapS()     const { return parameteri(GL_TEXTURE_WRAP_S); }
	inline GLint minWrapT()     const { return parameteri(GL_TEXTURE_WRAP_T); }
	inline GLint minWrapR()     const { return parameteri(GL_TEXTURE_WRAP_R); }
//@}

/// @name Level Parameters
//@{
	inline GLint levelParameteri(const GLint level, const GLenum pname) const {

		BindTexture(*this);
		GLint pvalue;
		glGetTexLevelParameteriv(target(), level, pname, &pvalue);
		return pvalue;
	}

	inline GLint levelWidth(const GLint level)               const { return levelParameteri(level, GL_TEXTURE_WIDTH); }
	inline GLint levelHeight(const GLint level)              const { return levelParameteri(level, GL_TEXTURE_HEIGHT); }
	inline GLint levelDepth(const GLint level)               const { return levelParameteri(level, GL_TEXTURE_DEPTH); }
	inline GLint levelInternalFormat(const GLint level)      const { return levelParameteri(level, GL_TEXTURE_INTERNAL_FORMAT); }
	inline GLint levelCompressed(const GLint level)          const { return levelParameteri(level, GL_TEXTURE_COMPRESSED); }
	inline GLint levelCompressedImageSize(const GLint level) const { return levelParameteri(level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE); }
//@}

/// @name Image I/O
//@{
	void image(const GLint   level,
	           const GLint   internalFormat,
	           const GLsizei width,
			   const GLsizei height,
			   const GLsizei depth,
	           const GLenum  format,
			   const GLenum  type,
			   const GLvoid  *pixels);

	void subImage(const GLint   level,
	              const GLint   xoffset,
				  const GLint   yoffset,
				  const GLint   zoffset,
	              const GLsizei width,
				  const GLsizei height,
				  const GLsizei depth,
	              const GLenum  format,
				  const GLenum  type,
				  const GLvoid  *pixels);

	inline void getImage(const GLint  level,
	                     const GLenum format,
						 const GLenum type,
						       GLvoid *pixels) const {

		if (BindTexture(*this)) glGetTexImage(target(), level, format, type, pixels);	
	}
//@}

/// @name Compressed Image I/O
//@{
	void compressedImage(const GLint   level,
	                     const GLenum  internalFormat, 
	                     const GLsizei width,
						 const GLsizei height,
						 const GLsizei depth,
	                     const GLsizei imageSize,
						 const void    *data);

	void compressedSubImage(const GLint   level, 
							const GLint   xoffset,
							const GLint   yoffset,
							const GLint   zoffset,
							const GLsizei width,
							const GLsizei height,
							const GLsizei depth,
							const GLenum  format,
							const GLsizei imageSize,
							const void    *data);

	inline void getCompressedImage(const GLint lod, void *img) const {
		if (BindTexture(*this))	glGetCompressedTexImage(target(), lod, img);
	}
//@}

private:

	inline bool targetValid() const {

		GLuint tb = TextureBinding(target());
		bool   tv = BindTexture(target(), name());
		BindTexture(target(), tb);
		return tv;
	}

private:

	GLenum _target;
};

//------------------------------------------------------------------------------
//==============================================================================
//
// Texture Inlines
//

inline GLuint TextureBinding(const GLenum target) {

	static GLenum tbl[] = {GL_TEXTURE_BINDING_1D, GL_TEXTURE_BINDING_2D};
	return GetInteger((target==GL_TEXTURE_3D)?GL_TEXTURE_BINDING_3D:tbl[target-GL_TEXTURE_1D]);
}

inline bool BindTexture(const GLenum target, const GLuint name) {

	if (TextureBinding(target) == name) return true;
	glBindTexture(target, name);
	return TextureBinding(target) == name;
}

inline bool BindTexture(const Texture &tex) {
	return BindTexture(tex.target(), tex.name());
}

inline GLsizei TexSize(const GLint   internalFormat,
					   const GLsizei w,
					   const GLsizei h,
					   const GLsizei d,
					         GLsizei align) {

	if (!align) glGetIntegerv(GL_PACK_ALIGNMENT, &align);
	return BitsPerTexel(internalFormat)*((w%align)?(w-(w%align)+align):w) * h * d;
}

inline GLsizei TexImageSize(const GLenum  format,
							const GLenum  type,
                            const GLsizei w,
							const GLsizei h,
							const GLsizei d,
                                  GLsizei align) {

	if (!align) glGetIntegerv(GL_PACK_ALIGNMENT, &align);
	return BytesPerPixel(format, type)*((w%align)?(w-(w%align)+align):w) * h * d;
}

inline GLenum GuessTarget(const GLsizei w, const GLsizei h, const GLsizei d) {
	return (h > 0)?(d > 0)?GL_TEXTURE_3D:GL_TEXTURE_2D:GL_TEXTURE_1D;
}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_TEXTURE_H__
