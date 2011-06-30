#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <QApplication>
#include <QPlastiqueStyle>
#include <QFontDatabase>

// Application
class App : public QApplication 
{
public:
	App(int argc, char *argv[]);
	virtual ~App();
};

#endif // __APPLICATION_H__
