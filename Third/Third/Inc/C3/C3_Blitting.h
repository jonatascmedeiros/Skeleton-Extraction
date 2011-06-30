#ifndef __C3_BLITTING_H__
#define __C3_BLITTING_H__

#include <C3_Math.h>
#include <C3_OpenGL.h>

namespace C3 {

using namespace Math;

//------------------------------------------------------------------------------

void Blit(const vec2 &srcPos, const vec2 &srcExt,
		  const vec2 &dstPos, const vec2 &dstExt);

//------------------------------------------------------------------------------

}; // namespace C3

#endif // __C3_BLITTING_H__
