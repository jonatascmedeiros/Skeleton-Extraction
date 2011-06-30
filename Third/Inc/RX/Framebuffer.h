/*
=================================================
Framebuffer.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	03/04/2009
=================================================
*/

#ifndef __FRAMEBUFFER_H
#define __FRAMEBUFFER_H

#include "definitions.h"
#include "glInfo.h"

// determine renderbuffer object type
extern GLuint texId;
extern GLuint fboId, rboId;

class Framebuffer
{
public:
	// Constructor
	Framebuffer();

	// Set
	void setFramebuffer();

	// Begin/end 
	void begin();
	void end();

	// Bind/unbind texture
	void bind();
	void unbind();
	
public:
	// Test if supported
	bool isSupported() const;
	int texWidth, texHeight;
};

#endif // __FRAMEBUFFER_H