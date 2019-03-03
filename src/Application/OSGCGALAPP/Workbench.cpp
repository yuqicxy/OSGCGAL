#include "Workbench.h"
#include "ProjectWidget.h"
#include "ViewerWidget.h"

template<> Workbench* Singleton<Workbench>::mSingleton = nullptr;

Workbench::Workbench(QWidget *parent)
	:mParent(parent)
{
	mProjectWidget	= new ProjectWidget(mParent);
	mViewWidget		= new ViewerWidget(mParent);
}

Workbench::~Workbench()
{
}

ProjectWidget* Workbench::GetProjectWidget()
{
	assert(mProjectWidget);
	return mProjectWidget;
}

ViewerWidget* Workbench::GetViewerWidget()
{
	assert(mViewWidget);
	return mViewWidget;
}