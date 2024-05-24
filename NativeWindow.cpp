#include <NativeWindow>
#include <ViewAdaptor>

#include <osgViewer/Viewer>
#include <osg/GL>

#include <QApplication>
#include <QKeyEvent>
#include <QInputDialog>
#include <QLayout>
#include <QMainWindow>
#include <QScreen>
#include <QWindow>


NativeWindow::NativeWindow(QWidget* parent)
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate, nullptr)
{
    _widget = QWidget::createWindowContainer(this);
}

NativeWindow::~NativeWindow()
{
}

osgViewer::Viewer* NativeWindow::getOsgViewer()
{
    return viewAdaptor;
}

OpenThreads::ReadWriteMutex* NativeWindow::mutex()
{
    return &_osgMutex;
}

void NativeWindow::handleUpdateRequest()
{
    _osgWantsToRenderFrame = true;
    update();
}


void NativeWindow::initializeGL()
{
    // Initializes OpenGL function resolution for the current context.
    initializeOpenGLFunctions();
    createRenderer();
    emit initialized();
}

void NativeWindow::resizeGL(int w, int h)
{
    Q_ASSERT(viewAdaptor);
    double pixelRatio = screen()->devicePixelRatio();
    viewAdaptor->resize(w, h, pixelRatio);
}

void NativeWindow::paintGL()
{
    OpenThreads::ScopedReadLock locker(_osgMutex);
	if (_isFirstFrame) {
		_isFirstFrame = false;
        viewAdaptor->getCamera()->getGraphicsContext()->setDefaultFboId(defaultFramebufferObject());
	}
    viewAdaptor->frame();
}

void NativeWindow::keyPressEvent(QKeyEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->keyPressEvent(event);
}

void NativeWindow::keyReleaseEvent(QKeyEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->keyReleaseEvent(event);
}

void NativeWindow::mousePressEvent(QMouseEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->mousePressEvent(event);
}

void NativeWindow::mouseReleaseEvent(QMouseEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->mouseReleaseEvent(event);
}

void NativeWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->mouseDoubleClickEvent(event);
}

void NativeWindow::mouseMoveEvent(QMouseEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->mouseMoveEvent(event);
}

void NativeWindow::wheelEvent(QWheelEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->wheelEvent(event);
}

void NativeWindow::setDefaultDisplaySettings()
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    ds->setNvOptimusEnablement(1);
    ds->setStereo(false);
}

void NativeWindow::createRenderer()
{
    // call this before creating a View...
    setDefaultDisplaySettings();

    viewAdaptor = new ViewAdaptor(this);
    if (viewAdaptor)
    {
        connect(viewAdaptor, &ViewAdaptor::updateRequested, this, &NativeWindow::handleUpdateRequest);
    }
    double pixelRatio = screen()->devicePixelRatio();
    viewAdaptor->setupOSG(width(), height(), pixelRatio);
}
