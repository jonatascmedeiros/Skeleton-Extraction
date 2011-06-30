/*
=================================================
Shader.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	03/05/2009
=================================================
*/

#ifndef __SHADER_H
#define __SHADER_H

#include "definitions.h"
#include <fstream>
#include <vector>
#include "../Third/Inc/Cg/cg.h"
#include "../Third/Inc/Cg/cgGL.h"

namespace RX
{

class Shader
{
public:
	// Create
	Shader();

	// Initialize profiles
	void initialize(std::string vertexFile, std::string geometryFile, std::string fragmentFile);

	// Enable/disable shader use
	void enable();
	void disable();

	// Set parameters - Vertex
	void setVParameter1f(float a, std::string param);
	void setVParameter3f(float a, float b, float c, std::string param);
	void setVParameter4f(float a, float b, float c, float d, std::string param);

	// Set parameters - Fragment
	void setFParameter1f(float a, std::string param);
	void setFParameter2f(float a, float b, std::string param);
	void setFParameter3f(float a, float b, float c, std::string param);
	void setFParameterTex(GLuint tex, std::string param);

private:
	// Static members
	static bool isInitialized;
	static CGcontext cgContext;

	// Initialize loading context
	// (must be called before everything else)
	void initialize();

	CGprofile cgVertexProfile, cgGeometryProfile, cgFragmentProfile;
	CGprogram vertexProgram, geometryProgram, fragmentProgram;

	bool useFragment, useVertex, useGeometry;
};

};

#endif // __SHADER_H