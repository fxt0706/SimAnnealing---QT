#include "simannealing.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimAnnealing w;
	w.show();
	return a.exec();
}
