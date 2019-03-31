#include "ViewerWidget.h"
#include "QVBoxLayout"
#include "NodeAccessCallback.h"
#include "osgGA/StateSetManipulator"

ViewerWidget::ViewerWidget(QWidget* parent /*= 0*/, Qt::WindowFlags f /*= 0*/, 
	osgViewer::ViewerBase::ThreadingModel threadingModel /*= osgViewer::CompositeViewer::SingleThreaded*/) 
	:QWidget(parent, f)
	,mParent(parent)
{
	setThreadingModel(threadingModel);

	// disable the default setting of viewer.done() by pressing Escape.
	setKeyEventSetsDone(0);

	mRootNode = new osg::Group;

	QWidget* widget1 = addViewWidget(createGraphicsWindow(0, 0, 200, 200), mRootNode);
	//QWidget* widget1 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readRefNodeFile("F:\\OSGCGAL\\OSGCGAL\\Data\\cow.osgt"));
	//QWidget* widget2 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readRefNodeFile("F:\\OSGCGAL\\OSGCGAL\\Data\\glider.osgt"));
	//QWidget* widget3 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readRefNodeFile("F:\\OSGCGAL\\OSGCGAL\\Data\\axes.osgt"));
	//QWidget* widget4 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readRefNodeFile("F:\\OSGCGAL\\OSGCGAL\\Data\\fountain.osgt"));
	//QWidget* popupWidget = addViewWidget(createGraphicsWindow(900, 100, 320, 240, "Popup window", true), osgDB::readRefNodeFile("dumptruck.osgt"));
	//popupWidget->show();

	//QGridLayout* grid = new QGridLayout;
	//grid->addWidget(widget1, 0, 0);
	//grid->addWidget(widget2, 0, 1);
	//grid->addWidget(widget3, 1, 0);
	//grid->addWidget(widget4, 1, 1);
	//setLayout(grid);
	QVBoxLayout *vLayout = new QVBoxLayout;
	vLayout->addWidget(widget1);
	setLayout(vLayout);

	connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
	_timer.start(10);
}

QWidget* ViewerWidget::addViewWidget(GraphicsWindowQt* gw, osg::ref_ptr<osg::Node> scene)
{
	osgViewer::View* view = new osgViewer::View;
	//view->getDisplaySettings()->setVertexBufferHint(osg::DisplaySettings::VERTEX_ARRAY_OBJECT);	
	addView(view);

	osg::Camera* camera = view->getCamera();
	camera->setGraphicsContext(gw);

	const osg::GraphicsContext::Traits* traits = gw->getTraits();

	camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));

	// set the draw and read buffers up for a double buffered window with rendering going to back buffer
	camera->setDrawBuffer(GL_BACK);
	camera->setReadBuffer(GL_BACK);

	camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0f, 10000.0f);

	view->setSceneData(scene);
	view->addEventHandler(new osgViewer::StatsHandler);
	view->addEventHandler(new osgGA::StateSetManipulator(view->getCamera()->getOrCreateStateSet()));
	//add the thread model handler£¬but can't change Thread mode now in Qt
	//view->addEventHandler(new osgViewer::ThreadingHandler);
	view->setCameraManipulator(new osgGA::MultiTouchTrackballManipulator);
	gw->setTouchEventsEnabled(true);
	return gw->getGLWidget();
}

GraphicsWindowQt* ViewerWidget::createGraphicsWindow(int x, int y, int w, int h, 
	const std::string& name /*= ""*/, bool windowDecoration /*= false*/)
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowName = name;
	traits->windowDecoration = windowDecoration;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = ds->getNumMultiSamples();

	return new GraphicsWindowQt(traits.get(),mParent);
}

void ViewerWidget::paintEvent(QPaintEvent* /*event*/)
{
	frame();
}

void ViewerWidget::addChild(osg::Node *node)
{
	osg::ref_ptr<NodeAccessCallback> callback = new NodeAccessCallback(mRootNode, NodeAccessCallback::ADD);
	callback->setOpNode(node);
	mRootNode->addUpdateCallback(callback);
}

void ViewerWidget::removeChild(osg::Node *node)
{
	osg::ref_ptr<NodeAccessCallback> callback = new NodeAccessCallback(mRootNode, NodeAccessCallback::REMOVE);
	callback->setOpNode(node);
	mRootNode->addUpdateCallback(callback);
}

void ViewerWidget::clearChild()
{
	osg::ref_ptr<NodeAccessCallback> callback = new NodeAccessCallback(mRootNode, NodeAccessCallback::CLEAR);
	mRootNode->addUpdateCallback(callback);
}