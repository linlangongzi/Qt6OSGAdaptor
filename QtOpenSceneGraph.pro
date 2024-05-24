TEMPLATE = lib
CONFIG += c++17 dll

DEFINES += BUILD_INCLUDE

# Compiler settings
QMAKE_CXXFLAGS += -std=c++17

# Include paths
INCLUDEPATH += $$PWD

# Source and header files
HEADERS += \
    $$PWD/CullVisitorEx \
    $$PWD/Export \
    $$PWD/GraphicsWindowEx \
    $$PWD/NativeWidget \
    $$PWD/NativeWindow \
    $$PWD/ViewAdaptor \
    $$PWD/RenderStageEx \
    $$PWD/StateEx

SOURCES += \
    $$PWD/CullVisitorEx.cpp \
    $$PWD/GraphicsWindowEx.cpp \
    $$PWD/NativeWidget.cpp \
    $$PWD/NativeWindow.cpp \
    $$PWD/RenderStageEx.cpp \
    $$PWD/StateEx.cpp \
    $$PWD/ViewAdaptor.cpp

# Define the output directory
DESTDIR = ../lib

# Use OpenSceneGraph libraries
QT += core gui widgets opengl openglwidgets

# Platform-specific configurations
win32:!x64 {
    LIBS += -losg \
            -losgUtil \
            -losgViewer \
            -losgGA \
            -losgDB \
            -lOpenThreads \
            -lQt6Widgets \
            -lQt6OpenGL \
            -lQt6OpenGLWidgets \
            -lopengl32  # Link against the OpenGL library

    INCLUDEPATH += C:/vcpkg/installed/x86-windows/include

    LIBS += -LC:/vcpkg/installed/x86-windows/lib \
            -L$$[QT_INSTALL_LIBS]

    # Installation settings for 32-bit Windows
    target.path = $$PWD/../generates/lib
    headers.path = $$PWD/../generates/include/QtOsgAdaptor
    INSTALLS += target headers

    target.files = $$DESTDIR/*.dll
    headers.files = $$HEADERS
}

win32:x64 {
    LIBS += -losg \
            -losgUtil \
            -losgViewer \
            -losgGA \
            -losgDB \
            -lOpenThreads \
            -lQt6Widgets \
            -lQt6OpenGL \
            -lQt6OpenGLWidgets \
            -lopengl32  # Link against the OpenGL library

    INCLUDEPATH += C:/vcpkg/installed/x64-windows/include

    LIBS += -LC:/vcpkg/installed/x64-windows/lib \
            -L$$[QT_INSTALL_LIBS]

    # Installation settings for 64-bit Windows
    target.path = $$PWD/../generates/lib
    headers.path = $$PWD/../generates/include/QtOsgAdaptor
    INSTALLS += target headers

    target.files = $$DESTDIR/*.dll
    headers.files = $$HEADERS
}

macx {
    LIBS += -losg \
            -losgUtil \
            -losgViewer \
            -losgGA \
            -losgDB \
            -lOpenThreads \
            -framework OpenGL  # Link against the OpenGL framework

    INCLUDEPATH += /opt/homebrew/Cellar/open-scene-graph/3.6.5_2/include/

    LIBS += -L/opt/homebrew/Cellar/open-scene-graph/3.6.5_2/lib \
            -L$$[QT_INSTALL_LIBS]

    # Qt paths
    INCLUDEPATH += /Volumes/E/Qt/6.7.1/macos/lib/QtCore.framework/Headers \
                   /Volumes/E/Qt/6.7.1/macos/lib/QtGui.framework/Headers \
                   /Volumes/E/Qt/6.7.1/macos/lib/QtWidgets.framework/Headers \
                   /Volumes/E/Qt/6.7.1/macos/lib/QtOpenGL.framework/Headers \
                   /Volumes/E/Qt/6.7.1/macos/lib/QtOpenGLWidgets.framework/Headers

    LIBS += -F/Volumes/E/Qt/6.7.1/macos/lib \
            -framework QtCore \
            -framework QtGui \
            -framework QtWidgets \
            -framework QtOpenGL \
            -framework QtOpenGLWidgets

    # Installation settings for macOS
    target.path = /usr/local/lib
    headers.path = /usr/local/include/QtOsgAdaptor
    INSTALLS += target headers

    target.files = $$DESTDIR/*.dylib
    headers.files = $$HEADERS
}

unix:!macx {
    LIBS += -losg \
            -losgUtil \
            -losgViewer \
            -losgGA \
            -losgDB \
            -lOpenThreads \
            -lGL  # Link against the OpenGL library

    INCLUDEPATH += /opt/homebrew/Cellar/open-scene-graph/3.6.5_2/include/

    LIBS += -L/opt/homebrew/Cellar/open-scene-graph/3.6.5_2/lib \
            -L$$[QT_INSTALL_LIBS]

    # Qt paths
    INCLUDEPATH += /usr/include/qt/QtCore \
                   /usr/include/qt/QtGui \
                   /usr/include/qt/QtWidgets \
                   /usr/include/qt/QtOpenGL \
                   /usr/include/qt/QtOpenGLWidgets

    LIBS += -lQt6Core \
            -lQt6Gui \
            -lQt6Widgets \
            -lQt6OpenGL \
            -lQt6OpenGLWidgets

    # Installation settings for Linux
    target.path = /usr/local/lib
    headers.path = /usr/local/include/QtOsgAdaptor
    INSTALLS += target headers

    target.files = $$DESTDIR/*.so
    headers.files = $$HEADERS
}
