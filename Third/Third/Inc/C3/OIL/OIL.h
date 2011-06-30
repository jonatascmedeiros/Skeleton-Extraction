#ifndef __C3_OIL_H__
#define __C3_OIL_H__

#ifdef _UNICODE
#undef _UNICODE
#include <il/il.h>
#include <il/ilu.h>
#define _UNICODE
#else
#include <il/il.h>
#include <il/ilu.h>
#endif // _UNICODE

#include <OIL/OIL_Image.h>

#if _WIN32
#if 0
#pragma comment (lib, "DevIL")
#pragma comment (lib, "ILU")
#endif
#endif // WIN32

namespace C3 {

//------------------------------------------------------------------------------
//==============================================================================
//
// OIL
//
/// Temporarily Abandoned

namespace OIL {

/// @name Common Functions
	bool Init();

	const char *GetEnumString(ILenum value);
	ILenum     DefaultImageType();
	void       SetDefaultImageType(ILenum type);
/// @}

/// @name Misc Functions
	void RGB2LUV(ILubyte *rl, ILubyte *gu, ILubyte *bv);
	void LUV2RGB(ILubyte *lr, ILubyte *ug, ILubyte *vb);
/// @}

//------------------------------------------------------------------------------

}; // namespace OIL
}; // namespace C3

#endif // __C3_OIL_H_
