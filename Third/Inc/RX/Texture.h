/*
=================================================
Texture.h
-------------------------------------------------
Author:			Roslia Galiazzi Schneider
Last Modified:	13/03/2009
=================================================
*/

#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <string>
#include "definitions.h"

namespace RX
{

class Texture
{

public:
	// Constructor
	Texture() {}

	// Load/save texture
	void load(std::string f);
	void save(std::string f);

	void load(std::string left, std::string right, std::string front, std::string back, std::string up, std::string down);

	// Bind/unbind texture
	void bind();
	void unbind();

	// Gets
	inline const GLuint texture() const { return tex; }

// provisory
public:
	GLuint tex;
	int width, height, bpp;
	GLuint type;

private:
	// Constants defining the cubemap faces
	static const GLuint cubeMapConst[6];

};

};

#endif // __TEXTURE_H
