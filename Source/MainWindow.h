#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include "LeastSquares.h"
#include "Mesh.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public slots:
	void load();
	void iterateOnce();
	void quit();

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:
	Ui::MainWindow ui;
	Mesh _object;
	Mesh _skeleton;
	LeastSquares _ls;
	bool _first;
};

#endif // __MAINWINDOW_H
