cmake_minimum_required(VERSION 3.14)
project(QtOsgAdaptor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source and header files
set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/CullVisitorEx
    ${CMAKE_CURRENT_SOURCE_DIR}/DefineExport.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsWindowEx
    ${CMAKE_CURRENT_SOURCE_DIR}/NativeWidget
    ${CMAKE_CURRENT_SOURCE_DIR}/NativeWindow
    ${CMAKE_CURRENT_SOURCE_DIR}/ViewAdaptor
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderStageEx
    ${CMAKE_CURRENT_SOURCE_DIR}/StateEx
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/CullVisitorEx.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsWindowEx.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NativeWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NativeWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderStageEx.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StateEx.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ViewAdaptor.cpp
)

# Define include directories based on platform
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # 64-bit Windows
        include_directories(
            ${CMAKE_CURRENT_SOURCE_DIR}
            C:/vcpkg/installed/x64-windows/include
        )
    else()
        # 32-bit Windows
        include_directories(
            ${CMAKE_CURRENT_SOURCE_DIR}
            C:/vcpkg/installed/x86-windows/include
        )
    endif()
elseif(APPLE)
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        /Volumes/E/Qt/6.7.1/macos/lib/QtCore.framework/Headers
        /Volumes/E/Qt/6.7.1/macos/lib/QtGui.framework/Headers
        /Volumes/E/Qt/6.7.1/macos/lib/QtWidgets.framework/Headers
        /Volumes/E/Qt/6.7.1/macos/lib/QtOpenGL.framework/Headers
        /Volumes/E/Qt/6.7.1/macos/lib/QtOpenGLWidgets.framework/Headers
        /opt/homebrew/Cellar/open-scene-graph/3.6.5_2/include
    )
else()
    # Linux/Unix
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        /usr/include/qt/QtCore
        /usr/include/qt/QtGui
        /usr/include/qt/QtWidgets
        /usr/include/qt/QtOpenGL
        /usr/include/qt/QtOpenGLWidgets
        /opt/homebrew/Cellar/open-scene-graph/3.6.5_2/include
    )
endif()

# Define the library target
add_library(QtOsgAdaptor SHARED ${SOURCES} ${HEADERS})

# Link against the OpenSceneGraph and Qt libraries
find_package(OpenSceneGraph REQUIRED osg osgUtil osgViewer osgGA osgDB OpenThreads)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)

target_link_libraries(QtOsgAdaptor
    PUBLIC
        OpenSceneGraph::osg
        OpenSceneGraph::osgUtil
        OpenSceneGraph::osgViewer
        OpenSceneGraph::osgGA
        OpenSceneGraph::osgDB
        OpenSceneGraph::OpenThreads
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::OpenGLWidgets
)

# Platform-specific installation settings
if(WIN32 AND NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 32-bit Windows
    set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/../generates")
    install(TARGETS QtOsgAdaptor
        RUNTIME DESTINATION ${OUTPUT_DIR}/lib
        LIBRARY DESTINATION ${OUTPUT_DIR}/lib
        ARCHIVE DESTINATION ${OUTPUT_DIR}/lib
    )
    install(FILES ${HEADERS}
        DESTINATION ${OUTPUT_DIR}/include/QtOsgAdaptor
    )
elseif(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64-bit Windows
    set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/../generates")
    install(TARGETS QtOsgAdaptor
        RUNTIME DESTINATION ${OUTPUT_DIR}/lib
        LIBRARY DESTINATION ${OUTPUT_DIR}/lib
        ARCHIVE DESTINATION ${OUTPUT_DIR}/lib
    )
    install(FILES ${HEADERS}
        DESTINATION ${OUTPUT_DIR}/include/QtOsgAdaptor
    )
elseif(APPLE)
    # macOS
    set(OUTPUT_DIR "/usr/local")
    install(TARGETS QtOsgAdaptor
        RUNTIME DESTINATION ${OUTPUT_DIR}/lib
        LIBRARY DESTINATION ${OUTPUT_DIR}/lib
        ARCHIVE DESTINATION ${OUTPUT_DIR}/lib
    )
    install(FILES ${HEADERS}
        DESTINATION ${OUTPUT_DIR}/include/QtOsgAdaptor
    )
else()
    # Linux/Unix
    set(OUTPUT_DIR "/usr/local")
    install(TARGETS QtOsgAdaptor
        RUNTIME DESTINATION ${OUTPUT_DIR}/lib
        LIBRARY DESTINATION ${OUTPUT_DIR}/lib
        ARCHIVE DESTINATION ${OUTPUT_DIR}/lib
    )
    install(FILES ${HEADERS}
        DESTINATION ${OUTPUT_DIR}/include/QtOsgAdaptor
    )
endif()