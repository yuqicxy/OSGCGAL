#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SARibbonMainWindow.h"

class SARibbonCategory;
class SARibbonContextCategory;
class QTextEdit;
class ViewerWidget;

//namespace Ui {
//	class OSGAPP;
//}

class BuilderAction;
class ProjectWidget;
class Workbench;

class OSGAPP : public SARibbonMainWindow
{
	Q_OBJECT

public:
	explicit OSGAPP(QWidget *parent = nullptr);

	virtual ~OSGAPP();

private:
	//void createActions();
	void createStatusBar();
	void readSettings();

private:
	ViewerWidget					*mViewWidget;
	std::unique_ptr<BuilderAction>	mBuilderAction;
	std::unique_ptr<Workbench>		mWorkbench;
};

#endif // MAINWINDOW_H
