#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_OSGAPP.h"

class ViewerWidget;

//namespace Ui {
//	class OSGAPP;
//}

class BuilderAction;
class ProjectWidget;
class Workbench;

class OSGAPP : public QMainWindow
{
	Q_OBJECT

public:
	explicit OSGAPP(QWidget *parent = nullptr);

	~OSGAPP();

	//ViewerWidget* GetViewWidget();

//private Q_SLOTS:
	//void OpenModel();
	//void SaveAsModel();

Q_SIGNALS:
	//void AddStaticModel(osg::ref_ptr<osg::Node> node);
	//void RemoveStaticModel(osg::ref_ptr<osg::Node> node);

private:
	//void createActions();
	void createStatusBar();
	void readSettings();

private:
	Ui::OSGAPP						*ui;
	ViewerWidget					*mViewWidget;
	std::unique_ptr<BuilderAction>	mBuilderAction;
	std::unique_ptr<Workbench>		mWorkbench;
};

#endif // MAINWINDOW_H
