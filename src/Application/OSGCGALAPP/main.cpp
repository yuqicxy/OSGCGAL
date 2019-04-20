#include "mainwindow.h"
#include <QApplication>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include "osg/Notify"
#include "osg/ArgumentParser"

#ifndef VERSION_STR
	#define VERSION_STR "1.0.0"
#endif // VERSION_STR

static void usage(const char *prog, const char *msg);

int main(int argc, char *argv[])
{
	osg::ArgumentParser arguments(&argc, argv);
	arguments.getApplicationUsage()->setCommandLineUsage(arguments.getApplicationName() + " [options] filename ...");
	arguments.getApplicationUsage()->addCommandLineOption("-h or --help", "Display command line parameters");

	if (arguments.read("-h") || arguments.read("--help"))
	{
		osg::setNotifyLevel(osg::NOTICE);
		usage(arguments.getApplicationName().c_str(), 0);
	}

	std::string notifyLevel;
	while (arguments.read("--NotifyLevel", notifyLevel)) 
	{
		QString upper = QString::fromLocal8Bit(notifyLevel.c_str());
		upper.toUpper();
		notifyLevel = upper.toLocal8Bit();

		if (notifyLevel == "ALWAYS")
			osg::setNotifyLevel(osg::NotifySeverity::ALWAYS);
		else if(notifyLevel == "FATAL")
			osg::setNotifyLevel(osg::NotifySeverity::FATAL);
		else if (notifyLevel == "WARN")
			osg::setNotifyLevel(osg::NotifySeverity::WARN);
		else if (notifyLevel == "NOTICE")
			osg::setNotifyLevel(osg::NotifySeverity::NOTICE);
		else if (notifyLevel == "INFO")
			osg::setNotifyLevel(osg::NotifySeverity::INFO);
		else if (notifyLevel == "DEBUG_INFO")
			osg::setNotifyLevel(osg::NotifySeverity::DEBUG_INFO);
		else if (notifyLevel == "DEBUG_FP")
			osg::setNotifyLevel(osg::NotifySeverity::DEBUG_FP);
	}

    QApplication app(argc, argv);
	QCoreApplication::setOrganizationName(QApplication::tr("YuQi"));
	QCoreApplication::setApplicationName(QApplication::tr("osgCGAL"));
	QCoreApplication::setApplicationVersion(QT_VERSION_STR);

	app.setApplicationName(QApplication::tr("osgCGAL"));
    MainWindow w;
    w.show();

    return app.exec();
}


static void usage(const char *prog, const char *msg)
{
	if (msg)
	{
		osg::notify(osg::NOTICE) <<"Application:\t"<<prog<< std::endl;
		osg::notify(osg::NOTICE) << msg << std::endl;
	}

	osg::notify(osg::NOTICE)<< "--NotifyLevel " << std::endl;
	osg::notify(osg::NOTICE) << "\t\t Type:String Usage:Set Output Level" << std::endl;
	osg::notify(osg::NOTICE) << "\t\t Option:ALWAYS\tFATAL\tWARN\tNOTICE(default value)\tINFO\tDEBUG_INFO\tDEBUG_FP" << std::endl;
}