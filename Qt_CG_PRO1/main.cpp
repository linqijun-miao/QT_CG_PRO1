#include "Qt_CG_PRO1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Qt_CG_PRO1 w;
	w.resize(600, 600);
	w.show();
	return a.exec();
}
