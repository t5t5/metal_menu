#include <QApplication>
#include <QTimer>

#include "menudialog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MenuDialog m;
	m.show();

	QTimer::singleShot(0, &m, &MenuDialog::start);
	return a.exec();
}
