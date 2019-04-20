#include "BuilderAction.h"
#include "QFileDialog"
#include "QToolBar"
#include "QMenu"
#include "QDir"
#include <string>

#include <osg/PagedLOD>
#include <osgDB/WriteFile>

#include "Workbench.h"
#include "ViewerWidget.h"
#include "ProjectWidget.h"
#include "QTreeWidgetItem"
#include "MainWindow.h"

#include "CGALUtility.h"

template<> BuilderAction* Singleton<BuilderAction>::mSingleton = 0;

BuilderAction::BuilderAction(MainWindow *parent)
	:QObject(parent)
{
	mMainWindow = parent;
	//InitToolBar();
	InitAction();
}

BuilderAction::~BuilderAction()
{

}

void BuilderAction::InitAction()
{
	//assert(mFileToolbar);
	//assert(mFileMenu);

	const QIcon newIcon = QIcon::fromTheme(tr("openModel"), QIcon(":/ToolTipIcon/images/open.png"));
	mOpenModelAction = new QAction(newIcon, tr("Open"), this);
	mOpenModelAction->setShortcuts(QKeySequence::New);
	mOpenModelAction->setStatusTip(tr("open a new model"));
	connect(mOpenModelAction, SIGNAL(triggered()), this, SLOT(OpenModelAction()));
	//mFileToolbar->addAction(mOpenModelAction);
	//mFileMenu->addAction(mOpenModelAction);

	mAddObliqueDataAction = new QAction(tr("Add Oblique Data"), this);
	mOpenModelAction->setStatusTip(tr("Open and Arrange a Oblique Dataset"));
	connect(mAddObliqueDataAction, SIGNAL(triggered()), this, SLOT(AddObliqueDataAction()));

	const QIcon saveAsIcon = QIcon::fromTheme(tr("save-as"), QIcon(":/ToolTipIcon/images/save.png"));
	mSaveAsAction = new QAction(saveAsIcon, tr("Save As"));
	mSaveAsAction->setShortcuts(QKeySequence::SaveAs);
	mSaveAsAction->setStatusTip(tr("Save the Model"));
	connect(mSaveAsAction, SIGNAL(triggered()), this, SLOT(SaveAsAction()));
	//mFileToolbar->addAction(mSaveAsAction);
	//mFileMenu->addAction(mSaveAsAction);

	const QIcon deleteIcon = QIcon::fromTheme("delete Model", QIcon(":/ToolTipIcon/images/delete.png"));
	mRemoveModelAction = new QAction(deleteIcon, tr("Delete Model"));
	mRemoveModelAction->setShortcuts(QKeySequence::Delete);
	mRemoveModelAction->setStatusTip(tr("Delete the Model"));
	connect(mRemoveModelAction, SIGNAL(triggered()), this, SLOT(DeleteModelAction()));

	mLightOnOff = new QAction(tr("Light On/Off"));
	mLightOnOff->setStatusTip(tr("Open/Close Light Effect"));
	mLightOnOff->setCheckable(true);
	connect(mLightOnOff, SIGNAL(triggered(bool)), this, SLOT(OpenCloseLight(bool)));
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
	QString path = QFileDialog::getOpenFileName(nullptr, tr("Open Model"), "", "model(*.osg *.osgt *.obj *.osgb *.ive);ALL(*.*)");
	if (path.isEmpty())
		return;

	std::string fileName = path.toLocal8Bit().toStdString();
	osg::ref_ptr<osg::Node> node = OSGCGAL::ReadNodeFile(fileName);
	if (!node.valid())
		return;
	QFileInfo info(path);
	QString name = info.baseName();
	Workbench::getSingletonPtr()->GetProjectWidget()->AddModelItem(name,node,info.filePath());
}

void BuilderAction::SaveAsAction()
{
}

void BuilderAction::DeleteModelAction()
{
	QTreeWidgetItem *item = Workbench::getSingletonPtr()->GetProjectWidget()->GetCurrentItem();
	Workbench::getSingletonPtr()->GetProjectWidget()->RemoveItem(item);
}

void BuilderAction::AddObliqueDataAction()
{
	QString dirStr = QFileDialog::getExistingDirectory(nullptr, tr("Open Oblique Dataset Directory"),"../",
		QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);

	QDir dir(dirStr);
	if (dir.exists())
	{
		dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
		osg::ref_ptr<osg::PagedLOD> lod = new osg::PagedLOD;
		unsigned int childIndex = 0;
		for (QFileInfo info : dir.entryInfoList())
		{
			QString fileBaseName = info.baseName();
			QString osgbFileName = info.absoluteFilePath() + "/" + fileBaseName + ".osgb";
			QFileInfo osgbfileInfo(osgbFileName);

			if (osgbfileInfo.exists())
			{
				std::string fileName = osgbFileName.toLocal8Bit().toStdString();
				lod->setFileName(childIndex++, fileName);
				osg::ref_ptr<osg::Node> node = OSGCGAL::ReadNodeFile(fileName);
				if(!node.valid())
					osg::notify(osg::WARN) << fileName<< "\t is invalid node" << std::endl;
				std::string relativeFileName = fileName.substr(dirStr.size() + 1,fileName.size());
				lod->addChild(node, 0, 1e10, relativeFileName);
			}
			else
			{
				osg::notify(osg::WARN) << "Open\t" << osgbFileName.toLocal8Bit().toStdString() << "\t fail" << std::endl;
			}
		}
		if (lod->getNumFileNames() > 0)
		{
			std::string dirStdStr = dirStr.toLocal8Bit().toStdString();
			size_t pos = dirStdStr.find_last_of("\\ //");
			dirStdStr = dirStdStr.substr(0, pos);
			osgDB::writeNodeFile(*lod, dirStdStr +"//index.osg");
			AddModelByFileName(QString::fromLocal8Bit((dirStdStr +"//index.osg").c_str()));
		}
	}
}

void BuilderAction::AddModelByFileName(const QString &fileName)
{
	QFileInfo info(fileName);
	QString name = info.baseName();
	osg::ref_ptr<osg::Node> node = osgDB::readRefNodeFile(fileName.toLocal8Bit().toStdString());
	Workbench::getSingletonPtr()->GetProjectWidget()->AddModelItem(name, node, info.filePath());
}

void BuilderAction::OpenCloseLight(bool state)
{
	Workbench::getSingletonPtr()->GetViewerWidget()->lightOnOff(state);
}
