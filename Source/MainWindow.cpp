#include <iostream>
#include <QDialog>
#include <QString>
#include <QtGui>
#include "MainWindow.h"
#include <time.h>
#include <QtDebug>

clock_t startTime, endTime;

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
		startTime = clock();
		_ls.createMatrix2(_object);
		endTime = clock();
		qDebug() << "createMatrix2: " << (double)(endTime-startTime)/CLOCKS_PER_SEC << " seconds." << "\n\n"; 
		_first = false;
	}
	startTime = clock();
	_ls.solve();
	endTime = clock();
	qDebug() << "solve: " << (double)(endTime-startTime)/CLOCKS_PER_SEC << " seconds." << "\n\n"; 
	startTime = clock();
	_ls.updateMesh2(&_object);
	endTime = clock();
	qDebug() << "updateMesh2: " << (double)(endTime-startTime)/CLOCKS_PER_SEC << " seconds." << "\n\n";
	startTime = clock();
	_ls.updateWeights(&_object);
	endTime = clock();
	qDebug() << "updateWeights: " << (double)(endTime-startTime)/CLOCKS_PER_SEC << " seconds." << "\n\n";
	startTime = clock();
	_ls.updateMatrices2(_object);
	endTime = clock();
	qDebug() << "updateMatrices2: " << (double)(endTime-startTime)/CLOCKS_PER_SEC << " seconds." << "\n\n\n";

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
