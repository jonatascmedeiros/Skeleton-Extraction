/*
=================================================
Camera.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	06/03/2009
=================================================
*/

#ifndef __CAMERA_H
#define __CAMERA_H

#include "Definitions.h"
#include "mat4.h"
#include "vec3.h"

namespace RX
{	
class Camera
{
public:
	// Camera movement directions
	enum CameraDirection { 
		CDIRxCAM, CDIRyCAM, CDIRzCAM,
		CDIRxWORLD, CDIRyWORLD, CDIRzWORLD 
	};

public:
	// Constructor
	Camera();

	// Transformations
	void reset();
	//void move(float magnitude, CameraDirection direction);
	//void rotate(float angle, CameraDirection direction);

	// Gets
	inline mat4 modelview() const { return _modelview; }
	inline mat4 projection() const { return _projection; }
	inline mat4 mvp() const { return _projection * _modelview; }
	//inline vec3 position() const { return _position; }
	//inline float hfov() const { return _hfov; }
	//inline float vfov() const { return _vfov; }

	// Sets
	void setOrthoCamera(float x0, float x1, float y0, float y1, float z0, float z1);
	void setPerspCamera(float hfov, float vfov, float nearPlane, float farPlane);
	//inline void setUp(vec3 v) { _up = v; }
	//inline void setTarget(vec3 v) { _target = v; }
	//inline void setPosition(vec3 v) { _position = v; }
	
	/*
	inline void setHFoV(float hfov) {
		if(hfov > 179) hfov = 179;
		if(hfov < 1) hfov = 1;
		_hfov = hfov;
	}
	inline void setVFoV(float vfov) {
		if(vfov > 179) vfov = 179;
		if(vfov < 1) vfov = 1;
		_vfov = vfov;
	}
	inline void setNear(float nearPlane) { _near = nearPlane; }
	inline void setFar(float farPlane) { _far = farPlane; }
	*/

private:
	/*
	void updateVectors();
	*/
	vec3 _target, _position, _up, _front, _side;
	vec3 _rotation;
	float _hfov, _vfov;
	float _near, _far;

	mat4 _modelview;
	mat4 _projection;
};
};

#endif // __CAMERA_H
