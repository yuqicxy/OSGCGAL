#include "ViewerWidget.h"
#include "QVBoxLayout"
#include "NodeAccessCallback.h"
#include "osgGA/StateSetManipulator"

ViewerWidget::ViewerWidget(QWidget* parent /*= 0*/, Qt::WindowFlags f /*= 0*/, 
	osgViewer::ViewerBase::ThreadingModel threadingModel /*= osgViewer::CompositeViewer::SingleThreaded*/) 
	:QWidget(parent, f)
{
	QWidget::setMinimumSize(QSize(300,300));
	setThreadingModel(threadingModel);

	// disable the default setting of viewer.done() by pressing Escape.
	setKeyEventSetsDone(0);

	mRootNode = new osg::Group;

	QWidget* widget1 = addViewWidget(createGraphicsWindow(0, 0, 200, 200), mRootNode);

	QVBoxLayout *vLayout = new QVBoxLayout;
	vLayout->addWidget(widget1);
	setLayout(vLayout);

	connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
	_timer.start(10);
}

QWidget* ViewerWidget::addViewWidget(osgQt::GraphicsWindowQt* gw, osg::ref_ptr<osg::Node> scene)
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

osgQt::GraphicsWindowQt* ViewerWidget::createGraphicsWindow(int x, int y, int w, int h, 
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

	return new osgQt::GraphicsWindowQt(traits.get());
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