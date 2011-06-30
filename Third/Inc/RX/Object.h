/*
=================================================
Object.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	13/03/2009
=================================================
*/

#ifndef __OBJECT_H
#define __OBJECT_H

#include "model.h"
#include "vec3.h"

namespace RX
{
	class Object
	{
	public:
		// Constructor
		Object();

		// Draws the object
		void draw();

		// Gets
		inline vec3 position() const { return _position; }
		inline vec3 rotation() const { return _rotation; }
		inline vec3 orientation() const { return _orientation; }
		inline vec3 direction() const { return _rotation + _orientation; }
		inline float scale() const { return _scale; }

		inline float xMin() const { return (_model != NULL)? _model->xMin() : 0.0f; }
		inline float xMax() const { return (_model != NULL)? _model->xMax() : 0.0f; }
		inline float yMin() const { return (_model != NULL)? _model->yMin() : 0.0f; }
		inline float yMax() const { return (_model != NULL)? _model->yMax() : 0.0f; }
		inline float zMin() const { return (_model != NULL)? _model->zMin() : 0.0f; }
		inline float zMax() const { return (_model != NULL)? _model->zMax() : 0.0f; }

		// Sets
		inline void setModel(Model *model) { _model = model; }
		inline void setPosition(vec3 position) { _position = position; }
		inline void setRotation(vec3 rotation) { _rotation = rotation; }
		inline void setOrientation(vec3 orientation) { _orientation = orientation; }
		inline void setScale(float scale) { _scale = scale; }
		inline void setRenderMode(Model::RenderMode renderMode) { _renderMode = renderMode; }

	public:
		Model *_model;

		vec3 _position, _rotation, _orientation;
		float _scale;
		Model::RenderMode _renderMode;

		bool lit, visible;
	};
};

#endif // __OBJECT_H