#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>

#include <QApplication>
#include <QFileDialog>
#include <QTime>

#include "quaternion.h"
#include "Renderer.h"
#include "Utils.h"

#define _WIREFRAME 0
#define _PHONG 1

using namespace C3::Math;

ofstream logFile("log.txt");

Renderer::Renderer(QWidget *parent)
: _object(NULL)
{
	setFocusPolicy(Qt::StrongFocus);
	setAttribute(Qt::WA_DeleteOnClose, true);

	_renderTimer.setInterval(30);
	_renderTimer.start();
	connect(&_renderTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
}

Renderer::~Renderer() 
{
	makeCurrent();
	glDeleteLists(_dlList, 1);
}


void Renderer::initializeGL()
{
	phong.initialize("../Data/PhongV.cg", "", "../Data/PhongF.cg");
	phong.setFParameter3f(0.25, 0.25, 0.25, "Ka");
	phong.setFParameter3f(0.55, 0.55, 0.55, "Kd");
	phong.setFParameter3f(0.1, 0.1, 0.1, "Ks");
	phong.setFParameter1f(15.0, "shininess");

	_dlList = glGenLists(1);

	cam.setZoomOffset(10);
	cam.setXRotation(-30);	
}

void Renderer::paintGL()
{  
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
			
	if(!_object) return;

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(cam.getViewMatrix());	

	glColor3f(1.0, 0.0, 0.0f);
	phong.enable();
	_object->render(_PHONG);
	phong.disable();
	_object->render(_WIREFRAME);

}

void Renderer::resizeGL(int width, int height) 
{ 
	_width  = width;
	_height = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45, width/(float)height, 0.1, 5000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0, 0, -5, 0, 0, 0, 0, 1, 0);
}

void Renderer::keyPressEvent(QKeyEvent *event) 
{
}

void Renderer::mouseMoveEvent(QMouseEvent *event) 
{
	int dX = event->x() - lastMousePosition.x();
    int dY = event->y() - lastMousePosition.y();

	cam.updateXRotation(-dY);
	cam.updateYRotation(-dX);

	lastMousePosition = event->pos();
	updateGL();
}

void Renderer::mousePressEvent(QMouseEvent *event) 
{
	lastMousePosition = event->pos();
}

void Renderer::mouseReleaseEvent(QMouseEvent *event) 
{
}

void Renderer::wheelEvent(QWheelEvent *event)
{
	cam.updateZoomOffset(-event->delta());
	updateGL();
}


