#include "mainwindow.h"
#include <QApplication>

#include <QCommandLineParser>
#include <QCommandLineOption>

#ifndef VERSION_STR
	#define VERSION_STR "1.0.0"
#endif // VERSION_STR


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	QCoreApplication::setOrganizationName(QApplication::tr("YuQi"));
	QCoreApplication::setApplicationName(QApplication::tr("osgCGAL"));
	QCoreApplication::setApplicationVersion(QT_VERSION_STR);

	app.setApplicationName(QApplication::tr("osgCGAL"));
    MainWindow w;
    w.show();

    return app.exec();
}
