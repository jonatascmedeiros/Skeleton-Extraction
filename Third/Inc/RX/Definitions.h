/*
=================================================
Definitions.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	06/03/2009
=================================================
*/

#ifndef __DEFINITIONS_H
#define __DEFINITIONS_H

// c++
#include <fstream>
#include <iostream>
#include <list>

//windows-specific
#ifdef _WIN32

	#include <windows.h>

	#undef min
	#undef max

	#include "../Third/Inc/gl/glew.h"
	#include "../Third/Inc/gl/glext.h"

#endif

namespace RX
{
#ifdef DEBUG
	extern std::ofstream logFile;
#endif
};

#endif // __DEFINITIONS_H