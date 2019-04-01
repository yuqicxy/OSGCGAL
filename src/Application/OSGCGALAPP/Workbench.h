#pragma once

#include "Singleton.h"
#include "QWidget"
#include "QDockWidget"

class QWidget;
class ProjectWidget;
class ViewerWidget;

class Workbench : public Singleton<Workbench>
{
public:
	Workbench(QWidget *parent);

	~Workbench();

	ProjectWidget* GetProjectWidget();

	QDockWidget*GetProjectDockWidget();

	ViewerWidget* GetViewerWidget();
private:
	QWidget			*mParent;
	ViewerWidget	*mViewWidget;
	ProjectWidget	*mProjectWidget;
};