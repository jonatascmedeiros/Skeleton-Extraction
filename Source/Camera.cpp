#include "Camera.h"

Camera::Camera()
{
	quaternion = QQuaternion(1.0, 0.0, 0.0, 0.0);	
	target = QVector3D(0.0, 0.0, 0.0);
	xAxis = QVector3D(1.0, 0.0, 0.0);
	yAxis = QVector3D(0.0, 1.0, 0.0);
	zAxis = QVector3D(0.0, 0.0, 1.0);
	zoomOffset = 0.0;
	zoomSpeed = 0.005;
	rotationSpeed = 0.3;	
	viewMatrix.loadIdentity();		
}

void Camera::updateXRotation(int delta)
{
	QQuaternion tempQuaternion = QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, delta*rotationSpeed);	
	quaternion *= tempQuaternion;
	quaternion.normalize();
	updateViewMatrix();	
}

void Camera::updateYRotation(int delta)
{
	QQuaternion tempQuaternion = QQuaternion::fromAxisAndAngle(0.0, 1.0, 0.0, delta*rotationSpeed);
	quaternion = tempQuaternion * quaternion;
	quaternion.normalize();
	updateViewMatrix();	
}

void  Camera::setXRotation(int angle)
{
	QQuaternion tempQuaternion = QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, angle);	
	quaternion *= tempQuaternion;
	quaternion.normalize();
	updateViewMatrix();
}

void  Camera::setYRotation(int angle)
{
	QQuaternion tempQuaternion = QQuaternion::fromAxisAndAngle(0.0, 1.0, 0.0, angle);
	quaternion = tempQuaternion * quaternion;
	quaternion.normalize();
	updateViewMatrix();		
}

void Camera::setZoomOffset(int newZoomOffset)
{
	zoomOffset = newZoomOffset;
	updateTranslationViewMatrix();
}

void Camera::updateZoomOffset(int delta)
{
	zoomOffset += delta * zoomSpeed;
	updateTranslationViewMatrix();
}

const float* Camera::getViewMatrix()
{
	return viewMatrix.entries;
}

void Camera::updateViewMatrix()
{
	viewMatrix = matrixFromQuaternion();
	xAxis = QVector3D(viewMatrix.getEntry(0), viewMatrix.getEntry(4), viewMatrix.getEntry(8));
	yAxis = QVector3D(viewMatrix.getEntry(1), viewMatrix.getEntry(5), viewMatrix.getEntry(9));
	zAxis = QVector3D(viewMatrix.getEntry(2), viewMatrix.getEntry(6), viewMatrix.getEntry(10));

	updateTranslationViewMatrix();		
}

void Camera::updateTranslationViewMatrix()
{
	position = target + zAxis * zoomOffset;   	
	viewMatrix.setEntry(12, -QVector3D::dotProduct(xAxis, position)); 
	viewMatrix.setEntry(13, -QVector3D::dotProduct(yAxis, position)); 
	viewMatrix.setEntry(14, -QVector3D::dotProduct(zAxis, position));	
}

Matrix4x4 Camera::matrixFromQuaternion()
{
	Matrix4x4 m;	

    float x2 = quaternion.x() + quaternion.x(); 
    float y2 = quaternion.y() + quaternion.y(); 
    float z2 = quaternion.z() + quaternion.z();
    float xx = quaternion.x() * x2;
    float xy = quaternion.x() * y2;
    float xz = quaternion.x() * z2;
    float yy = quaternion.y() * y2;
    float yz = quaternion.y() * z2;
    float zz = quaternion.z() * z2;
    float wx = quaternion.scalar() * x2;
    float wy = quaternion.scalar() * y2;
    float wz = quaternion.scalar() * z2;    

    m.setEntry(0, 1.0f - yy - zz);
    m.setEntry(1, xy - wz);
    m.setEntry(2, xz + wy);
    m.setEntry(3, 0.0f);

    m.setEntry(4, xy + wz);
    m.setEntry(5, 1.0f - xx - zz);
    m.setEntry(6, yz - wx);
    m.setEntry(7, 0.0f);

    m.setEntry(8, xz - wy);
    m.setEntry(9, yz + wx);
    m.setEntry(10, 1.0f - xx - yy);
    m.setEntry(11, 0.0f);

    m.setEntry(12, 0.0f);
    m.setEntry(13, 0.0f);
    m.setEntry(14, 0.0f);
    m.setEntry(15, 1.0f);

	return m;	
}	