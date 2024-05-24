TEMPLATE = lib
CONFIG += c++17 dll

DEFINES += BUILD_OSGQOPENGL

# Include paths
INCLUDEPATH += include/osgQOpenGL

# Source and header files

HEADERS += \
    osgQOpenGL/CullVisitorEx \
    osgQOpenGL/Export \
    osgQOpenGL/GraphicsWindowEx \
    osgQOpenGL/OSGRenderer \
    osgQOpenGL/RenderStageEx \
    osgQOpenGL/StateEx \
    osgQOpenGL/osgQOpenGLWidget \
    osgQOpenGL/osgQOpenGLWindow


SOURCES += \
    CullVisitorEx.cpp \
    GraphicsWindowEx.cpp \
    OSGRenderer.cpp \
    RenderStageEx.cpp \
    StateEx.cpp \
    osgQOpenGLWidget.cpp \
    osgQOpenGLWindow.cpp

# Define the output directory
DESTDIR = ../lib

# Use OpenSceneGraph libraries
QT += core gui widgets opengl openglwidgets

# Link against OpenSceneGraph and Qt libraries
LIBS += -losg \
        -losgUtil \
        -losgViewer \
        -losgGA \
        -losgDB \
        -lOpenThreads \
        -lQt6Widgets \
        -lQt6OpenGL \
        -lQt6OpenGLWidgets \
        -lopengl32  # Add this line to link against the OpenGL library

# Include OpenSceneGraph and Qt directories
INCLUDEPATH += $$[QT_INSTALL_HEADERS] \
               $$[QT_INSTALL_HEADERS]/QtWidgets \
               $$[QT_INSTALL_HEADERS]/QtOpenGL \
               $$[QT_INSTALL_HEADERS]/QtOpenGLWidgets

# Include paths for OpenSceneGraph
INCLUDEPATH += C:/vcpkg/installed/x64-windows/include

# Library paths for OpenSceneGraph and Qt
LIBS += -LC:/vcpkg/installed/x64-windows/lib \
        -L$$[QT_INSTALL_LIBS]
