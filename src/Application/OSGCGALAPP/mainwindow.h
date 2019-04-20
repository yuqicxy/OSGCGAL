#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SARibbonBar.h"
#include "SARibbonMainWindow.h"
class ViewerWidget;
class BuilderAction;
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

private:
	void createStatusBar();
	void readSettings();
	void InitRibbon();
private:
	ViewerWidget *mViewWidget;

private:
	std::unique_ptr<Workbench>		mWorkbench;
	std::unique_ptr<BuilderAction>	mBuilderAction;
};

#endif // MAINWINDOW_H
