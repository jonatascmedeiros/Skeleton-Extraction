#ifndef __RENDERER
#define __RENDERER

#include <fstream>
#include <RX/Shader.h>
#include <QGLWidget>
#include <QMessageBox>
#include <QWheelEvent>
#include <QTimer>
#include "Mesh.h"

using namespace std;

class Renderer : public QGLWidget
{
Q_OBJECT

public:
	Renderer(QWidget *parent);
	virtual ~Renderer();

	// Tool implementation
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void keyPressEvent(QKeyEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);	

	// Sets
	inline void setMesh(Mesh *object) { _object = object; }

private:
	int _width, _height;
	Mesh *_object;
	GLuint _dlList;
	RX::Shader phong;

	QTimer _renderTimer;

	template <template <typename T> class C>
	void updateDisplayLists(Mesh *mesh, const GLuint displayList, const C<Mesh::FHandle> &fhs) 
	{
		Mesh::NormalMode nm = Mesh::VertexNormals;

		glNewList(displayList, GL_COMPILE);
		if (mesh)
			mesh->renderFaces(fhs, nm);
		glEndList();
	}
};

#endif // __RENDERER
