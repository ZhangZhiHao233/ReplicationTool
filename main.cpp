#include "replicationtool.h"
#include <QtWidgets/QApplication>
#include <QPixmap>
#include <QSplashScreen	>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	/*QPixmap pixmap(":/ReplicationTool/png/welcome.jpg");
	QSplashScreen splash(pixmap);
	splash.show();
	splash.setFixedSize(500, 500);
	a.processEvents();*/

	ReplicationTool w;
	w.show();

	//splash.finish(&w);
	return a.exec();
}
