#include <QDir>
#include "App.h"
#include "MainWindow.h"


App::App(int argc, char *argv[]) : QApplication(argc, argv)
{
	setStyle(new QPlastiqueStyle);

	// setup OpenGL format
	QGLFormat fmt;
	fmt.setDoubleBuffer(true);
	fmt.setSampleBuffers(true);
	fmt.setSamples(8);
	QGLFormat::setDefaultFormat(fmt);
}

App::~App() 
{
}

int main(int argc, char *argv[]) 
{
	App app(argc, argv);
	MainWindow window;
	window.show();
	return app.exec();
}
