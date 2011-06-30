#ifndef __C3_OIL_IMAGE_H__
#define __C3_OIL_IMAGE_H__

namespace C3 {
namespace OIL {

//------------------------------------------------------------------------------
//==============================================================================
//
// Image
//

class Image {

public:

/// @name Con-/Destruction
	Image();
	Image(ILuint name);
	virtual ~Image();
/// @}

/// @name Member Access
	ILuint name() const;
/// @}

/// @name Handle Validation
	operator bool() const;
/// @}

/// @name Properties Retrieval
	ILint width() const;
	ILint height() const;
	ILint depth() const;
	ILint format() const;
	ILint type() const;
	ILint bytesPerPixel() const;
	ILint bitsPerPixel() const;
	int   byteSize() const;
	bool  isPow2() const;
/// @}

/// @name Data Acess
	const void *data() const;
	void *data();
/// @}

/// @name TexImage
	bool texImage(ILuint w, ILuint h, ILuint d, ILubyte bpp,
		          ILenum format, ILenum type, ILvoid *data);
/// @}

/// @name Storage
	bool save(const char *filename, ILenum type = IL_TYPE_UNKNOWN) const;
	bool save(FILE *file, ILenum type) const;
	bool save(void *lump, int size, ILenum type) const;
/// @}

/// @name Blitting
	bool blit(Image &dst,
		      ILint  dx, ILint  dy, ILint  dz,
			  ILuint dw, ILuint dh, ILuint dd,
			  ILuint sx = 0, ILuint sy = 0, ILuint sz = 0) const;
	bool blit(Image &dst,
		      ILint  dx, ILint  dy,
			  ILuint dw, ILuint dh,
			  ILuint sx = 0, ILuint sy = 0) const;
/// @}

/// @name Color Keying
	bool keyColor(ILubyte l);
	bool keyColor(ILubyte l, ILubyte a);
	bool keyColor(ILubyte r, ILubyte g, ILubyte b);
	bool keyColor(ILubyte r, ILubyte g, ILubyte b, ILubyte a);
/// @}

/// @name Misc Functions
	bool convertTo(ILenum format, ILenum type);
	bool fill(ILubyte r, ILubyte g, ILubyte b, ILubyte a);
	bool invertAlpha();
	bool negative();
	bool scale(ILuint w, ILuint h, ILuint d, int filter = ILU_NEAREST);
	bool scale(ILuint w, ILuint h, int filter = ILU_NEAREST);
	bool crop(ILuint x, ILuint y, ILuint z, ILuint w, ILuint h, ILuint d);
/// @}

private:

	ILuint m_name;
};

//------------------------------------------------------------------------------
//==============================================================================
//
// misc Image functions
//

/// @name Image Functions
const Image CreateImage();

const Image CreateImage(ILuint w, ILuint h, ILuint d, ILubyte bpp,
				        ILenum format, ILenum type, void *data = 0);

const Image LoadImage(const char *filename, ILenum type = IL_TYPE_UNKNOWN);

const Image LoadImage(FILE *file, ILenum type = IL_TYPE_UNKNOWN);

const Image LoadImage(void *lump, int size, ILenum type = IL_TYPE_UNKNOWN);

// THANKS-FOR-#define-LoadImage-LoadImageW-IN-SOME-WIN32-HEADERS
inline const Image ReadImage(const char *filename, ILenum type = IL_TYPE_UNKNOWN) {
	return LoadImage(filename, type);
}
inline const Image ReadImage(FILE *file, ILenum type = IL_TYPE_UNKNOWN) {
	return LoadImage(file, type);
}
inline const Image ReadImage(void *lump, int size, ILenum type = IL_TYPE_UNKNOWN) {
	return LoadImage(lump, size, type);
}
// END

const Image DeleteImage(Image &img);

ILuint CurrentImage();

bool BindImage(ILuint name);
bool BindImage(const Image &image);

const Image CloneImage(const Image &img);
/// @}

//------------------------------------------------------------------------------
//==============================================================================
//
// Image inlines
//

//------------------------------------------------------------------------------
// Con-/Destruction

inline Image::Image()
: m_name(0) {
}

inline Image::Image(ILuint name)
: m_name(name) {
}

inline Image::~Image() {
}

//------------------------------------------------------------------------------
// Member Access

inline ILuint Image::name() const {
	return m_name;
}

//------------------------------------------------------------------------------
// Handle Validation

inline Image::operator bool() const {
	return ilIsImage(name()) == IL_TRUE;
}

//------------------------------------------------------------------------------
// Properties Retrieval

inline ILint Image::width() const {
	return BindImage(*this) ? ilGetInteger(IL_IMAGE_WIDTH) : 0;
}

inline ILint Image::height() const {
	return BindImage(*this) ? ilGetInteger(IL_IMAGE_HEIGHT) : 0;
}

inline ILint Image::depth() const {
	return BindImage(*this) ? ilGetInteger(IL_IMAGE_DEPTH) : 0;
}

inline ILint Image::format() const {
	return BindImage(*this) ? ilGetInteger(IL_IMAGE_FORMAT) : 0;
}

inline ILint Image::type() const {
	return BindImage(*this) ? ilGetInteger(IL_IMAGE_TYPE) : 0;
}

inline ILint Image::bytesPerPixel() const {
	return BindImage(*this) ? ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL) : 0;
}

inline ILint Image::bitsPerPixel() const {
	return BindImage(*this) ? ilGetInteger(IL_IMAGE_BITS_PER_PIXEL) : 0;
}

inline int Image::byteSize() const {
	return width()*height()*depth()*bytesPerPixel();
}

//------------------------------------------------------------------------------
// Data Acess

inline const void *Image::data() const {
	return BindImage(*this) ? ilGetData() : 0;
}

inline void *Image::data() {
	return BindImage(*this) ? ilGetData() : 0;
}

//------------------------------------------------------------------------------

}; // namespace OIL
}; // namespace C3

#endif // __C3_OIL_IMAGE_H__
