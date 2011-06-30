/*
=================================================
Loader.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	06/03/2009
=================================================
*/

#ifndef __LOADER_H
#define __LOADER_H

#include <fstream>
#include <vector>
#include "vec3.h"
#include "Model.h"
#include "Texture.h"

namespace RX
{
	class Loader  
	{
	public:
		// Instruction header
		struct Header
		{
			unsigned short id;
			unsigned int len;
		};

	public:
		// Constructor
		Loader();
		// Destructor
		~Loader();

		// Loads a model from a filename
		void load(std::string filename, Model *model);

	private:
		// Read 3ds files
		void read3ds(long length, long findex);
		
		void readModel(long length, long findex);
		void readAnimation(long length, long findex);
				
		// Read materials
		void readMaterial(long length, long findex, Material *mat);	
		void readMaterialName(long length, long findex, Material *mat);
		void readDiffuseColor(long length, long findex, Material *mat);

		Color IntColorChunkProcessor(long length, long findex);
		Color FloatColorChunkProcessor(long length, long findex);

		void readTextureMap(long length, long findex, Material *mat);
		void readTextureName(long length, long findex, Material *mat);

		// Read geometry
		void readMesh(long length, long findex, Mesh *mesh);
		void readTriangles(long length, long findex, Mesh *mesh);
		void readVertices(long length, long findex, Mesh *mesh);
		void readTexCoords(long length, long findex, Mesh *mesh);
		void readFaces(long length, long findex, Mesh *mesh);
		void readFaceMaterials(long length, long findex, Mesh *mesh, MaterialFaces *mat);

		// Calculate the normals
		void calculateNormals();

		// Attributes
		Model *model3d;

		std::string modelname;
		std::string path;
		int totalVerts;
		int totalFaces;

		// Binary 3ds file
		std::ifstream file3ds;
	};
};

#endif // __LOADER_H
