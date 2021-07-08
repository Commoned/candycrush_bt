#include "Gui.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include "Feld.h"
#include <qthread.h>


int x, y;
char input;


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Gui gui;

	gui.show();
	a.processEvents();
	return a.exec();

}
