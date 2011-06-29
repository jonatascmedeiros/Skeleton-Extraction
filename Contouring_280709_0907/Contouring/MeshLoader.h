//////////////////////////////////////////////////////////////////////////////////////
//  Perspective Contouring Project
//	Jonatas Medeiros
//	UFRGS - 2008
//
//	MeshLoader.h includes headers for the MeshLoader class
//////////////////////////////////////////////////////////////////////////////////////


#ifndef MESHLOADER_H
#define MESHLOADER_H

#include "Mesh.h"

class MeshLoader
{
public:
	static bool	load(Mesh* mesh, const string& strFileName);
		//  REQUIRE: given file must contain one and only one mesh object (first iteration requirement).
		//  PROMISE: param. "mesh" contains the parsed content.
	//static void	parseMtlLib(const string& strFileName);
		//	REQUIRE: the ".mtl" file must be fully valid, unsupported keywords are ignored but recognized.
		//	REQUIRE: the .mtl file may contain more than one material.
		//	PROMISE: every material contained in the file is added to the material map, identified by its name.
	static bool	processLine(Mesh* mesh, istream& is);
		//  PROMISE: return false at end of stream.

private:
	static void	skipLine(istream& is);
	static bool	skipCommentLine(istream& is);	
};



#endif // MESHLOADER_H
