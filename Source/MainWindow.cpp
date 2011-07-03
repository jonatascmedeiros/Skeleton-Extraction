#include <iostream>
#include <QDialog>
#include <QString>
#include <QtGui>
#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags) 
: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// initialize opengl widget
	ui.widgetMesh->setMesh(&_object);
	ui.widgetMesh->setFocus();

	// connect signals to slots
	// menu
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(quit()));
	connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(load())); 
	connect(ui.actionIterateOnce, SIGNAL(triggered()), this, SLOT(iterateOnce())); 
}


MainWindow::~MainWindow() 
{
}

void MainWindow::quit()
{
	exit(0);
}

void MainWindow::load()
{
	QString filename = QFileDialog::getOpenFileName(this->parentWidget(), tr("Open File"), QDir::currentPath());
	if(!filename.isEmpty()) {
		_object.read(filename);
		_first = true;
		
	}
}

void MainWindow::iterateOnce()
{
	if(_first) {
		_ls.createMatrix(_object);
		_first = false;
	}

	_ls.solve();
	_ls.updateMesh(&_object);
	_ls.updateWeights(&_object);
	_ls.updateMatrices(_object);

	/*
	if (!meshSetupOk){ 
		_ls.setup(_object);
		meshSetupOk = true;

		_ls.solveSystem();
		_ls.updateMesh2(&_object);
	} else {
		_ls.updateSytem(_object);
		_ls.solveSystem();
		_ls.updateMesh2(&_object);		
	}
	*/
}
