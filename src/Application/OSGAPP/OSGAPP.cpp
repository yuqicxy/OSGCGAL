#include "OSGAPP.h"
#include "ViewerWidget.h"
#include "QAction"
#include "QIcon"
#include "QMenu"
#include "QFileDialog"
#include "BuilderAction.h"
#include "ProjectWidget.h"
#include "Workbench.h"

OSGAPP::OSGAPP(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::OSGAPP)
{
	ui->setupUi(this);
	//mViewWidget = new ViewerWidget(this);
	//setCentralWidget(mViewWidget);

	//remove default toobar
	QList<QToolBar *> allToolBars = findChildren<QToolBar *>();
	foreach(QToolBar *tb, allToolBars)
	{
		// This does not delete the tool bar.
		removeToolBar(tb);
	}

	mBuilderAction.reset(new BuilderAction(this));
	mWorkbench.reset(new Workbench(this));

	//setCentralWidget(mViewWidget);
	setCentralWidget(Workbench::getSingletonPtr()->GetViewerWidget());
	addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, Workbench::getSingleton().GetProjectWidget());
}

OSGAPP::~OSGAPP()
{
	delete ui;
}

//void MainWindow::createActions()
//{
//	menuBar()->clear();
//	
//	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
//	QToolBar *fileToolBar = addToolBar(tr("File"));
//	const QIcon newIcon = QIcon::fromTheme("openModel", QIcon(":/ToolTipIcon/images/open.png"));
//	QAction *openAct = new QAction(newIcon, tr("&Open"), this);
//	openAct->setShortcuts(QKeySequence::New);
//	openAct->setStatusTip(tr("open a new model"));
//	connect(openAct, &QAction::triggered, this, &MainWindow::OpenModel);
//	fileMenu->addAction(openAct);
//	fileToolBar->addAction(openAct);
//
//	const QIcon saveAsIcon = QIcon::fromTheme("document-save-as", QIcon(":/ToolTipIcon/images/save.png"));
//	QAction *saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::SaveAsModel);
//	saveAsAct->setShortcuts(QKeySequence::SaveAs);
//	saveAsAct->setStatusTip(tr("Save the Model under a new name"));
//	connect(openAct, &QAction::triggered, this, &MainWindow::SaveAsModel);
//	fileMenu->addAction(saveAsAct);
//	fileToolBar->addAction(saveAsAct);
//}

void OSGAPP::createStatusBar()
{

}

void OSGAPP::readSettings()
{

}

//
////slot func set
////********************
//void MainWindow::OpenModel()
//{
//	QString path = QFileDialog::getOpenFileName(this, tr("Open Model"), "", "model(*.osg *.osgt *.obj *.osgb)");
//	if (path.isEmpty())
//		return;
//	
//	osg::ref_ptr<osg::Node> node = osgDB::readRefNodeFile(path.toLocal8Bit().toStdString());
//	mViewWidget->addChild(node);
//}
//
//void MainWindow::SaveAsModel()
//{
//
//}

//ViewerWidget* MainWindow::GetViewWidget()
//{
//	assert(mViewWidget);
//	return mViewWidget;
//}
