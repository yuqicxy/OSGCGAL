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

MainWindow::MainWindow(QWidget *parent) :
    SARibbonMainWindow(parent)//,
	//ui(new Ui::MainWindow)
{
	//ui->setupUi(this);
	//mViewWidget = new ViewerWidget;
	//setCentralWidget(mViewWidget);	
	//createActions();

	SARibbonBar* ribbon = ribbonBar();
	QFont font("Times");
	ribbon->setFont(font);
	ribbon->applitionButton()->setText(QStringLiteral("File"));
	ribbon->quickAccessBar()->setVisible(false);

	SARibbonCategory* categoryMain = ribbon->addCategoryPage(QStringLiteral("Main"));
	SARibbonCategory* categoryOther = ribbon->addCategoryPage(QStringLiteral("Other"));	

	mBuilderAction.reset(new BuilderAction(this));
	//
	mWorkbench.reset(new Workbench(this));
	setCentralWidget(mWorkbench->GetViewerWidget());
	//
	addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, Workbench::getSingletonPtr()->GetProjectDockWidget());
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::createActions()
{
	menuBar()->clear();
	
	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
	QToolBar *fileToolBar = addToolBar(tr("File"));
	const QIcon newIcon = QIcon::fromTheme("openModel", QIcon(":/ToolTipIcon/images/open.png"));
	QAction *openAct = new QAction(newIcon, tr("&Open"), this);
	openAct->setShortcuts(QKeySequence::New);
	openAct->setStatusTip(tr("open a new model"));
	connect(openAct, &QAction::triggered, this, &MainWindow::OpenModel);
	fileMenu->addAction(openAct);
	fileToolBar->addAction(openAct);

	const QIcon saveAsIcon = QIcon::fromTheme("document-save-as", QIcon(":/ToolTipIcon/images/save.png"));
	QAction *saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::SaveAsModel);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("Save the Model under a new name"));
	connect(openAct, &QAction::triggered, this, &MainWindow::SaveAsModel);
	fileMenu->addAction(saveAsAct);
	fileToolBar->addAction(saveAsAct);
}

void MainWindow::createStatusBar()
{

}

void MainWindow::readSettings()
{

}


//slot func set
//********************
void MainWindow::OpenModel()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open Model"), "", "model(*.osg *.osgt *.obj *.osgb)");
	if (path.isEmpty())
		return;
	
	osg::ref_ptr<osg::Node> node = osgDB::readRefNodeFile(path.toLocal8Bit().toStdString());
	mViewWidget->addChild(node);
}

void MainWindow::SaveAsModel()
{

}
//********************