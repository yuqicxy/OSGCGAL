#pragma once
#include "osgQtWidget.h"
#include "QGridLayout"
#include "QTimer"
#include <osgDB/ReadFile>
#include <osgViewer/CompositeViewer>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/MultiTouchTrackballManipulator>

class ViewerWidget : public QWidget, public osgViewer::CompositeViewer
{
public:
	ViewerWidget(QWidget* parent = 0, Qt::WindowFlags f = 0, osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::CompositeViewer::SingleThreaded);

	QWidget* addViewWidget(GraphicsWindowQt* gw, osg::ref_ptr<osg::Node> scene);

	GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h, const std::string& name = "", bool windowDecoration = false);

	virtual void paintEvent(QPaintEvent* /*event*/);

	void addChild(osg::Node *node);

	void removeChild(osg::Node *node);

	void clearChild();

	osg::ref_ptr<osg::Group> GetRootNode() { return mRootNode; }

protected:
	osg::ref_ptr<osg::Group> mRootNode;
	QTimer _timer;
};
