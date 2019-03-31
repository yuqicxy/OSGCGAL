#include "BuilderAction.h"
#include "QFileDialog"
#include "QToolBar"
#include "QMenu"
#include <string>

#include "Workbench.h"
#include "ViewerWidget.h"
#include "ProjectWidget.h"
#include "QTreeWidgetItem"
#include "MainWindow.h"

template<> BuilderAction* Singleton<BuilderAction>::mSingleton = 0;

BuilderAction::BuilderAction(MainWindow *parent)
	:QObject(parent)
{
	mMainWindow = parent;
	InitToolBar();
	InitAction();
}

BuilderAction::~BuilderAction()
{

}

void BuilderAction::InitAction()
{
	assert(mFileToolbar);
	assert(mFileMenu);

	const QIcon newIcon = QIcon::fromTheme(tr("openModel"), QIcon(":/ToolTipIcon/images/open.png"));
	mOpenModelAction = new QAction(newIcon, tr("Open"), this);
	mOpenModelAction->setShortcuts(QKeySequence::New);
	mOpenModelAction->setStatusTip(tr("open a new model"));
	connect(mOpenModelAction, SIGNAL(triggered()), this, SLOT(OpenModelAction()));
	mFileToolbar->addAction(mOpenModelAction);
	mFileMenu->addAction(mOpenModelAction);

	const QIcon saveAsIcon = QIcon::fromTheme(tr("save-as"), QIcon(":/ToolTipIcon/images/save.png"));
	mSaveAsAction = new QAction(saveAsIcon, tr("Save As"));
	mSaveAsAction->setShortcuts(QKeySequence::SaveAs);
	mSaveAsAction->setStatusTip(tr("Save the Model"));
	connect(mSaveAsAction, SIGNAL(triggered()), this, SLOT(SaveAsAction()));
	mFileToolbar->addAction(mSaveAsAction);
	mFileMenu->addAction(mSaveAsAction);

	const QIcon deleteIcon = QIcon::fromTheme("delete Model", QIcon(":/ToolTipIcon/images/delete.png"));
	mRemoveModelAction = new QAction(deleteIcon, tr("Delete Model"));
	mRemoveModelAction->setShortcuts(QKeySequence::Delete);
	mRemoveModelAction->setStatusTip(tr("Delete the Model"));
	connect(mRemoveModelAction, SIGNAL(triggered()), this, SLOT(DeleteModelAction()));
}

void BuilderAction::InitToolBar()
{
	mFileToolbar = new QToolBar(tr("File"));
	mMainWindow->addToolBar(mFileToolbar);

	mFileMenu = new QMenu(tr("&File"));
	mMainWindow->menuBar()->addMenu(mFileMenu);
}

void BuilderAction::OpenModelAction()
{
	QString path = QFileDialog::getOpenFileName(nullptr, tr("Open Model"), "", "model(*.osg *.osgt *.obj *.osgb)");
	if (path.isEmpty())
		return;

	std::string fileName = path.toStdString();
	osg::ref_ptr<osg::Node> node = osgDB::readRefNodeFile(fileName);
	
	QFileInfo info(path);
	QString name = info.baseName();
	std::map<QString, osg::ref_ptr<osg::Node>> map = Workbench::getSingletonPtr()->GetProjectWidget()->FindItemByName(name);
	if (map.size() > 0)
	{
		name = name + QString("(%1)").arg(map.size());
	}
	Workbench::getSingletonPtr()->GetViewerWidget()->addChild(node);
	node->setName(name.toStdString());
	Workbench::getSingletonPtr()->GetProjectWidget()->AddModelItem(name,node,info.filePath());
}

void BuilderAction::SaveAsAction()
{
}

void BuilderAction::DeleteModelAction()
{
	QTreeWidgetItem *item = Workbench::getSingletonPtr()->GetProjectWidget()->GetCurrentItem();
	QString itemName = item->text(0);
	std::map<QString, osg::ref_ptr<osg::Node>> map = Workbench::getSingletonPtr()->GetProjectWidget()->FindItemByName(itemName);
	if(map.size() > 0)
		Workbench::getSingletonPtr()->GetViewerWidget()->removeChild(map[itemName]);
	Workbench::getSingletonPtr()->GetProjectWidget()->RemoveItem(item);
}