#pragma once
#include "Singleton.h"
#include "QAction"

class MainWindow;
class QToolBar;
class QMenu;

class BuilderAction : public QObject,public Singleton<BuilderAction>
{
	Q_OBJECT
public:
	BuilderAction(MainWindow *mParent);
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
	MainWindow *mMainWindow;
};