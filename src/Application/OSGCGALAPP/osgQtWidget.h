#pragma once
#include <QtOpenGL/QGLWidget>
#include <osgviewer/ViewerBase>
#include <osgViewer/GraphicsWindow>
#include <QMutex>
#include <QEvent>
#include <QQueue>
#include <QSet>
#include <osg/Version>
#include <QInputEvent>
#include <QGestureEvent>

// forward declarations
class GraphicsWindowQt;

#if OSG_VERSION_LESS_THAN(3, 5, 6)
/// The function sets the WindowingSystem to Qt.
void initQtWindowingSystem();
#endif

/** The function sets the viewer that will be used after entering
 *  the Qt main loop (QCoreApplication::exec()).
 *
 *  The function also initializes internal structures required for proper
 *  scene rendering.
 *
 *  The method must be called from main thread. */
void setViewer(osgViewer::ViewerBase *viewer);

class osgQtWidget : public QGLWidget
{
	typedef QGLWidget inherited;

public:

	osgQtWidget(QWidget* parent = NULL, const QGLWidget* shareWidget = NULL, Qt::WindowFlags f = 0, bool forwardKeyEvents = false);
	osgQtWidget(QGLContext* context, QWidget* parent = NULL, const QGLWidget* shareWidget = NULL, Qt::WindowFlags f = 0, bool forwardKeyEvents = false);
	osgQtWidget(const QGLFormat& format, QWidget* parent = NULL, const QGLWidget* shareWidget = NULL, Qt::WindowFlags f = 0, bool forwardKeyEvents = false);
	virtual ~osgQtWidget();

	inline void setGraphicsWindow(GraphicsWindowQt* gw) { _gw = gw; }
	inline GraphicsWindowQt* getGraphicsWindow() { return _gw; }
	inline const GraphicsWindowQt* getGraphicsWindow() const { return _gw; }

	inline bool getForwardKeyEvents() const { return _forwardKeyEvents; }
	virtual void setForwardKeyEvents(bool f) { _forwardKeyEvents = f; }

	inline bool getTouchEventsEnabled() const { return _touchEventsEnabled; }
	void setTouchEventsEnabled(bool e);

	void setKeyboardModifiers(QInputEvent* event);

	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);
	virtual bool gestureEvent(QGestureEvent* event);

protected:

	int getNumDeferredEvents()
	{
		QMutexLocker lock(&_deferredEventQueueMutex);
		return _deferredEventQueue.count();
	}
	void enqueueDeferredEvent(QEvent::Type eventType, QEvent::Type removeEventType = QEvent::None)
	{
		QMutexLocker lock(&_deferredEventQueueMutex);

		if (removeEventType != QEvent::None)
		{
			if (_deferredEventQueue.removeOne(removeEventType))
				_eventCompressor.remove(eventType);
		}

		if (_eventCompressor.find(eventType) == _eventCompressor.end())
		{
			_deferredEventQueue.enqueue(eventType);
			_eventCompressor.insert(eventType);
		}
	}
	void processDeferredEvents();

	friend class GraphicsWindowQt;
	GraphicsWindowQt* _gw;

	QMutex _deferredEventQueueMutex;
	QQueue<QEvent::Type> _deferredEventQueue;
	QSet<QEvent::Type> _eventCompressor;

	bool _touchEventsEnabled;

	bool _forwardKeyEvents;
	qreal _devicePixelRatio;

	virtual void resizeEvent(QResizeEvent* event);
	virtual void moveEvent(QMoveEvent* event);
	virtual void glDraw();
	virtual bool event(QEvent* event);
};

class GraphicsWindowQt : public osgViewer::GraphicsWindow
{
public:
	GraphicsWindowQt(osg::GraphicsContext::Traits* traits, QWidget* parent = NULL, const QGLWidget* shareWidget = NULL, Qt::WindowFlags f = 0);
	GraphicsWindowQt(osgQtWidget* widget);
	virtual ~GraphicsWindowQt();

	inline osgQtWidget* getGLWidget() { return _widget; }
	inline const osgQtWidget* getGLWidget() const { return _widget; }

	/// deprecated
	inline osgQtWidget* getGraphWidget() { return _widget; }
	/// deprecated
	inline const osgQtWidget* getGraphWidget() const { return _widget; }

	struct WindowData : public osg::Referenced
	{
		WindowData(osgQtWidget* widget = NULL, QWidget* parent = NULL) : _widget(widget), _parent(parent) {}
		osgQtWidget* _widget;
		QWidget* _parent;
	};

	bool init(QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f);

	static QGLFormat traits2qglFormat(const osg::GraphicsContext::Traits* traits);
	static void qglFormat2traits(const QGLFormat& format, osg::GraphicsContext::Traits* traits);
	static osg::GraphicsContext::Traits* createTraits(const QGLWidget* widget);

	virtual bool setWindowRectangleImplementation(int x, int y, int width, int height);
	virtual void getWindowRectangle(int& x, int& y, int& width, int& height);
	virtual bool setWindowDecorationImplementation(bool windowDecoration);
	virtual bool getWindowDecoration() const;
	virtual void grabFocus();
	virtual void grabFocusIfPointerInWindow();
	virtual void raiseWindow();
	virtual void setWindowName(const std::string& name);
	virtual std::string getWindowName();
	virtual void useCursor(bool cursorOn);
	virtual void setCursor(MouseCursor cursor);
	inline bool getTouchEventsEnabled() const { return _widget->getTouchEventsEnabled(); }
	virtual void setTouchEventsEnabled(bool e) { _widget->setTouchEventsEnabled(e); }


	virtual bool valid() const;
	virtual bool realizeImplementation();
	virtual bool isRealizedImplementation() const;
	virtual void closeImplementation();
	virtual bool makeCurrentImplementation();
	virtual bool releaseContextImplementation();
	virtual void swapBuffersImplementation();
	virtual void runOperations();

	virtual void requestWarpPointer(float x, float y);

protected:
	friend class osgQtWidget;
	osgQtWidget* _widget;
	bool _ownsWidget;
	QCursor _currentCursor;
	bool _realized;
};