/*
=========================================================================================================
GLInfo.h
---------------------------------------------------------------------------------------------------------
Author:			Song Ho Ahn
Adapted by:		Rosália Galiazzi Schneider 
Last Modified:	02/04/2009
---------------------------------------------------------------------------------------------------------

To get valid OpenGL infos, OpenGL rendering context (RC) must be opened before calling glInfo::getInfo().
Otherwise it returns false.
=========================================================================================================
*/

#ifndef __GLINFO_H
#define __GLINFO_H

#include <string>
#include <vector>
#include "definitions.h"

class GLInfo
{
public:
	// Constructors
	GLInfo();
	
    bool getInfo();
    void toStream();
    bool isExtensionSupported(const char* ext);
	
private:
    std::string vendor;
    std::string renderer;
    std::string version;
    std::vector <std::string> extensions;
    int redBits;
    int greenBits;
    int blueBits;
    int alphaBits;
    int depthBits;
    int stencilBits;
    int maxTextureSize;
    int maxLights;
    int maxAttribStacks;
    int maxModelViewStacks;
    int maxProjectionStacks;
    int maxClipPlanes;
    int maxTextureStacks;
};

#endif // __GLINFO_H
