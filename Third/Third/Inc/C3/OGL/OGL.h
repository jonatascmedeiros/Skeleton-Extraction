#ifndef __C3_OGL_H__
#define __C3_OGL_H__

#include <OGL/OGL_Basics.h>
#include <OGL/OGL_Culling.h>
#include <OGL/OGL_DepthTest.h>
#include <OGL/OGL_PolygonMode.h>
#include <OGL/OGL_Viewport.h>
#include <OGL/OGL_Texture.h>
#include <OGL/OGL_Buffer.h>
#include <OGL/OGL_Shader.h>
#include <OGL/OGL_Program.h>
#include <OGL/OGL_Renderbuffer.h>
#include <OGL/OGL_Framebuffer.h>

namespace C3 {

//------------------------------------------------------------------------------
//==============================================================================
//
// OGL
//

/**
	Try	http://www.opengl.org/ ,
	    http://glew.sourceforge.net/ ,
		http://oss.sgi.com/projects/ogl-sample/registry/ .
*/

namespace OGL {

/// @name Common Functions
	inline GLenum Init() { return glewInit();	}

	inline GLboolean IsSupported(const char *name) { return glewIsSupported(name); }
/// @}

//------------------------------------------------------------------------------

}; // namespace OGL
}; // namespace C3

#endif // __C3_OGL_H__
