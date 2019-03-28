#include "OSGAPP.h"
#include "ViewerWidget.h"
#include "QAction"
#include "QIcon"
#include "QMenu"
#include "QFont"
#include "QFileDialog"
#include "BuilderAction.h"
#include "ProjectWidget.h"
#include "SARibbonBar.h"
#include "SARibbonQuickAccessBar.h"
#include "Workbench.h"

OSGAPP::OSGAPP(QWidget *parent) :
	SARibbonMainWindow(parent)//,
	//ui(new Ui::OSGAPP)
{
	//ui->setupUi(this);
	//mViewWidget = new ViewerWidget(this);
	//setCentralWidget(mViewWidget);

	//remove default toobar
	//QList<QToolBar *> allToolBars = findChildren<QToolBar *>();
	//foreach(QToolBar *tb, allToolBars)
	//{
	//	// This does not delete the tool bar.
	//	removeToolBar(tb);
	//}
	setWindowTitle(tr("OSGCGAL"));
	setWindowIcon(QIcon(":/ToolTipIcon/images/app.ico"));
	SARibbonBar* ribbon = ribbonBar();
	QFont f = ribbon->font();
	f.setFamily("Î¢ÈíÑÅºÚ");
	ribbon->setFont(f);
	ribbon->applitionButton()->setText(QStringLiteral("File"));
	SARibbonCategory* categoryMain = ribbon->addCategoryPage(QStringLiteral("Main"));
	SARibbonCategory* categoryOther = ribbon->addCategoryPage(QStringLiteral("Other"));

	//mBuilderAction.reset(new BuilderAction(this));
	mWorkbench.reset(new Workbench(this));

	//setCentralWidget(mViewWidget);
	setCentralWidget(Workbench::getSingletonPtr()->GetViewerWidget());
	addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, Workbench::getSingleton().GetProjectWidget());
	
	ribbon->quickAccessBar()->setVisible(false);
	//ribbon->quickAccessBar()->addButton(new QAction(QIcon(":/icon/icon/chartDataManager.png"), "action1", this));
	//ribbon->quickAccessBar()->addButton(new QAction(QIcon(":/icon/icon/figureIcon.png"), "action2", this));
	//ribbon->quickAccessBar()->addButton(new QAction(QIcon(":/icon/icon/information.png"), "action3", this));
	//ribbon->quickAccessBar()->addButton(new QAction(QIcon(":/icon/icon/inRangDataRemove.png"), "action4", this));

	showMaximized();
}

OSGAPP::~OSGAPP()
{
}

void OSGAPP::createStatusBar()
{

}

void OSGAPP::readSettings()
{

}