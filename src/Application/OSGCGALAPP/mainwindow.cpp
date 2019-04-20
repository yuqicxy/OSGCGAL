#include "ui_mainwindow.h"

#include "mainwindow.h"
#include "QAction"
#include "QIcon"
#include "QMenu"
#include "QFileDialog"
#include "QDockWidget"

#include "Workbench.h"
#include "BuilderAction.h"
#include "ViewerWidget.h"

#include "SARibbonBar.h"
#include "SARibbonQuickAccessBar.h"


MainWindow::MainWindow(QWidget *parent):
    SARibbonMainWindow(parent)
{
	mBuilderAction.reset(new BuilderAction(this));
	mWorkbench.reset(new Workbench(this));
	setCentralWidget(mWorkbench->GetViewerWidget());
	addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, Workbench::getSingletonPtr()->GetProjectDockWidget());

	InitRibbon();
}

MainWindow::~MainWindow()
{
}

void MainWindow::InitRibbon()
{
	SARibbonBar* ribbon = ribbonBar();
	QFont font("Times");
	ribbon->setFont(font);
	ribbon->applitionButton()->setText(QStringLiteral("File"));
	ribbon->quickAccessBar()->setVisible(false);
	SARibbonCategory* categoryMain = ribbon->addCategoryPage(QStringLiteral("Main"));
	SARibbonPannel* pannel = categoryMain->addPannel(QStringLiteral("State"));
	pannel->addSmallAction(BuilderAction::getSingleton().mLightOnOff);
}

void MainWindow::createStatusBar()
{
}

void MainWindow::readSettings()
{

}