cmake_minimum_required(VERSION 3.14)

project(osgQt)

# Define the library name
set(LIB_NAME osgQOpenGL)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

# Define macros
add_definitions(-DBUILD_OSGQOPENGL)

# Include vcpkg toolchain if available
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

# Include paths
include_directories(
    include/osgQOpenGL
)

# Source and header files
set(HEADERS
    include/osgQOpenGL/CullVisitorEx.h
    include/osgQOpenGL/Export.h
    include/osgQOpenGL/GraphicsWindowEx.h
    include/osgQOpenGL/OSGRenderer.h
    include/osgQOpenGL/RenderStageEx.h
    include/osgQOpenGL/StateEx.h
    include/osgQOpenGL/osgQOpenGLWidget.h
    include/osgQOpenGL/osgQOpenGLWindow.h
)

set(SOURCES
    CullVisitorEx.cpp
    GraphicsWindowEx.cpp
    OSGRenderer.cpp
    RenderStageEx.cpp
    StateEx.cpp
    osgQOpenGLWidget.cpp
    osgQOpenGLWindow.cpp
)

# Find packages using vcpkg or system packages
find_package(OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer osgWidget)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)

# Platform-specific settings
if(APPLE)
    # Specify the architecture for macOS (e.g., arm64 for M1/M2)
    set(CMAKE_OSX_ARCHITECTURES "arm64")

    # macOS specific OpenGL library
    find_library(OpenGL_LIBRARY OpenGL REQUIRED)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
endif()

# Create the library
add_library(${LIB_NAME} SHARED ${SOURCES} ${HEADERS})

# Link against OpenSceneGraph, Qt, and platform-specific libraries
target_link_libraries(${LIB_NAME}
    osg
    osgUtil
    osgViewer
    osgGA
    osgDB
    OpenThreads
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    ${OpenGL_LIBRARY}
    ${COCOA_LIBRARY}
)

# Set properties for Qt6 automatic tools
set_target_properties(${LIB_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# Handle vcpkg integration
if(DEFINED ENV{VCPKG_ROOT})
    include_directories(${VCPKG_INCLUDE_DIR})
    link_directories(${VCPKG_LIBRARY_DIR})
endif()
