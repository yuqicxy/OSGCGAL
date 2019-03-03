#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "SARibbonBar.h"
class ViewerWidget;

namespace Ui {
class MainWindow;
}

class BuilderAction;
class ProjectWidget;
class Workbench;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
	
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
	Ui::MainWindow					*ui;
	std::unique_ptr<BuilderAction>	mBuilderAction;
	std::unique_ptr<Workbench>		mWorkbench;
};

#endif // MAINWINDOW_H
