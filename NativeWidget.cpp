#include <NativeWidget>
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

NativeWidget::NativeWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

NativeWidget::NativeWidget(osg::ArgumentParser* arguments,
                                   QWidget* parent) :
    QOpenGLWidget(parent),
    _arguments(arguments)
{
}

NativeWidget::~NativeWidget()
{
}

osgViewer::Viewer* NativeWidget::getOsgViewer()
{
    return viewAdaptor;
}

OpenThreads::ReadWriteMutex* NativeWidget::mutex()
{
    return &_osgMutex;
}

void NativeWidget::handleUpdateRequest()
{
    _osgWantsToRenderFrame = true;
    update();
}


void NativeWidget::initializeGL()
{
    // Initializes OpenGL function resolution for the current context.
    initializeOpenGLFunctions();
    createRenderer();
    emit initialized();
}

void NativeWidget::resizeGL(int w, int h)
{
    Q_ASSERT(viewAdaptor);
    QScreen* screen = windowHandle()
                      && windowHandle()->screen() ? windowHandle()->screen() :
                      qApp->screens().front();
    viewAdaptor->resize(w, h, screen->devicePixelRatio());
}

void NativeWidget::paintGL()
{
    OpenThreads::ScopedReadLock locker(_osgMutex);
	if (_isFirstFrame) {
		_isFirstFrame = false;
        viewAdaptor->getCamera()->getGraphicsContext()->setDefaultFboId(defaultFramebufferObject());
	}
    viewAdaptor->frame();
}

void NativeWidget::keyPressEvent(QKeyEvent* event)
{
    Q_ASSERT(viewAdaptor);

    if(event->key() == Qt::Key_F)
    {
        static QSize g;
        static QMargins sMargins;

        if(parent() && parent()->isWidgetType())
        {
            QMainWindow* _mainwindow = dynamic_cast<QMainWindow*>(parent());

            if(_mainwindow)
            {
                g = size();

                if(layout())
                    sMargins = layout()->contentsMargins();

                bool ok = true;

                // select screen
                if(qApp->screens().size() > 1)
                {
                    QMap<QString, QScreen*> screens;
                    int screenNumber = 0;

                    for(QScreen* screen : qApp->screens())
                    {
                        QString name = screen->name();

                        if(name.isEmpty())
                        {
                            name = tr("Screen %1").arg(screenNumber);
                        }

                        name += " (" + QString::number(screen->size().width()) + "x" + QString::number(
                                    screen->size().height()) + ")";
                        screens[name] = screen;
                        ++screenNumber;
                    }

                    QString selected = QInputDialog::getItem(this,
                                                             tr("Choose fullscreen target screen"), tr("Screen"), screens.keys(), 0, false,
                                                             &ok);

                    if(ok && !selected.isEmpty())
                    {
                        context()->setScreen(screens[selected]);
                        move(screens[selected]->geometry().x(), screens[selected]->geometry().y());
                        resize(screens[selected]->geometry().width(),
                               screens[selected]->geometry().height());
                    }
                }

                if(ok)
                {
                    // in fullscreen mode, a thiner (1px) border around
                    // viewer widget
                    if(layout())
                        layout()->setContentsMargins(1, 1, 1, 1);

                    setParent(0);
                    showFullScreen();
                }
            }
        }
        else
        {
            showNormal();
            setMinimumSize(g);
            QMainWindow* _mainwindow = dynamic_cast<QMainWindow*>(parent());
            if(_mainwindow){
                _mainwindow->setCentralWidget(this);
            }

            if(layout())
                layout()->setContentsMargins(sMargins);

            qApp->processEvents();
            setMinimumSize(QSize(1, 1));
        }
    }
    else // not 'F' key
    {
        // forward event to renderer
        viewAdaptor->keyPressEvent(event);
    }
}

void NativeWidget::keyReleaseEvent(QKeyEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->keyReleaseEvent(event);
}

void NativeWidget::mousePressEvent(QMouseEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->mousePressEvent(event);
}

void NativeWidget::mouseReleaseEvent(QMouseEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->mouseReleaseEvent(event);
}

void NativeWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->mouseDoubleClickEvent(event);
}

void NativeWidget::mouseMoveEvent(QMouseEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->mouseMoveEvent(event);
}

void NativeWidget::wheelEvent(QWheelEvent* event)
{
    Q_ASSERT(viewAdaptor);
    // forward event to renderer
    viewAdaptor->wheelEvent(event);
}

void NativeWidget::setDefaultDisplaySettings()
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    ds->setNvOptimusEnablement(1);
    ds->setStereo(false);
}

void NativeWidget::createRenderer()
{
    // call this before creating a View...
    setDefaultDisplaySettings();
	if (!_arguments) {
        viewAdaptor = new ViewAdaptor(this);
	} else {
        viewAdaptor = new ViewAdaptor(_arguments, this);
	}
    if (viewAdaptor)
    {
        connect(viewAdaptor, &ViewAdaptor::updateRequested, this, &NativeWidget::handleUpdateRequest);
    }
	QScreen* screen = windowHandle()
                      && windowHandle()->screen() ? windowHandle()->screen() :
                      qApp->screens().front();
    viewAdaptor->setupOSG(width(), height(), screen->devicePixelRatio());
}
