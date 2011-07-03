#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QQuaternion>
#include "Matrix4x4.h"

class Camera
{
	private:
		QVector3D position;
		QVector3D target;
		QVector3D xAxis, yAxis, zAxis;
		QQuaternion quaternion;
		Matrix4x4 viewMatrix;
		double zoomOffset;
		double zoomSpeed;
		double rotationSpeed;

		void updateViewMatrix(void);
		void updateTranslationViewMatrix(void);
		Matrix4x4 matrixFromQuaternion();		

	public:
		Camera();
		void setPosition(QVector3D newPosition){position = newPosition;};		
		void setXRotation(int angle);
        void setYRotation(int angle);
		void updateXRotation(int delta);
        void updateYRotation(int delta);
		void updateZoomOffset(int delta);
		void setZoomOffset(int newZoomOffset);
		const float* getViewMatrix(void);		
};

#endif