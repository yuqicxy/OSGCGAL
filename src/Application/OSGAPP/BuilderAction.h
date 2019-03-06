#pragma once
#include "Singleton.h"
#include "QAction"

class OSGAPP;
class QToolBar;
class QMenu;

class BuilderAction : public QObject,public Singleton<BuilderAction>
{
	Q_OBJECT
public:
	BuilderAction(OSGAPP *mParent);
	virtual ~BuilderAction();

private slots:
	void SaveAsAction();
	void OpenModelAction();
	void DeleteModelAction();

private:
	void InitAction();
	void InitToolBar();

public:
	QAction *mOpenModelAction;
	QAction *mRemoveModelAction;
	QAction *mSaveAsAction;

	QToolBar *mFileToolbar;
	QMenu*	mFileMenu;

private:
	OSGAPP *mMainWindow;
};