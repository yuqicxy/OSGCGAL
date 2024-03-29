#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SARibbonBar.h"
#include "SARibbonMainWindow.h"
class ViewerWidget;
class BuilderAction;
//class ProjectWidget;
class Workbench;

namespace Ui {
class MainWindow;
}

class MainWindow : public SARibbonMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:
	void OpenModel();
	void SaveAsModel();

private:
	void createActions();
	void createStatusBar();
	void readSettings();

private:
	ViewerWidget *mViewWidget;

private:
	std::unique_ptr<Workbench>		mWorkbench;
	std::unique_ptr<BuilderAction>	mBuilderAction;
};

#endif // MAINWINDOW_H
