/*
=================================================
Model.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	03/05/2009
=================================================
*/

#ifndef __MODEL_H
#define __MODEL_H

#include <string>
#include <vector>
#include "definitions.h"
#include "vec2.h"
#include "vec3.h"
#include "Texture.h"

namespace RX
{
	struct Color
	{
		float r, g, b, a;
	};

	struct Material 
	{
		std::string name;
		Texture tex;
		bool textured;
		Color color;
	};

	// Sort by material to avoid switching textures
	struct MaterialFaces 
	{
		std::vector<vec3> faces;
		int material;
	};

	// The 3ds file can be made up of several meshes
	struct Mesh 
	{
		std::string name;

		std::vector<vec3> vertices;
		std::vector<vec3> normals;
		std::vector<vec2> texCoords;

		std::vector<vec3> faces;
		std::vector<MaterialFaces> matFaces;
		
		vec3 position;
		vec3 rotation;
		bool textured;
	};


	class Model
	{
	public:
		// Friends
		friend class Loader;

		// Types
		enum RenderMode {
			Solid, Wireframe, Points
		};

		// Create/destroy
		Model();

		// Draws the model
		void draw(RenderMode mode);

		// Gets
		inline float xMin() const { return _xMin; }
		inline float xMax() const { return _xMax; }
		inline float yMin() const { return _yMin; }
		inline float yMax() const { return _yMax; }
		inline float zMin() const { return _zMin; }
		inline float zMax() const { return _zMax; }

	protected:
		// Updates model after loading
		void calcNormals();
		void updateBBox();

		std::vector<Material> materials;
		std::vector<Mesh> meshes;

		float _xMin, _xMax;
		float _yMin, _yMax;
		float _zMin, _zMax;
	};
};

#endif // __MODEL_H
