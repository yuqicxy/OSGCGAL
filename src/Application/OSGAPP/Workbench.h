#pragma once

#include "Singleton.h"
#include "QWidget"

class QWidget;
class ProjectWidget;
class ViewerWidget;

class Workbench : public Singleton<Workbench>
{
public:
	Workbench(QWidget *parent);

	~Workbench();

	ProjectWidget* GetProjectWidget();

	ViewerWidget* GetViewerWidget();
private:
	QWidget			*mParent;
	ViewerWidget	*mViewWidget;
	ProjectWidget	*mProjectWidget;
};