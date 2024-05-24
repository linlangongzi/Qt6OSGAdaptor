#ifndef OSGQOPENGL_EXPORT_H
#define OSGQOPENGL_EXPORT_H

#if defined(_WIN32) || defined(_WIN64)
#ifdef BUILD_OSGQOPENGL
#define OSGQOPENGL_EXPORT __declspec(dllexport)
#else
#define OSGQOPENGL_EXPORT __declspec(dllimport)
#endif
#elif defined(__GNUC__) && __GNUC__ >= 4
#define OSGQOPENGL_EXPORT __attribute__ ((visibility ("default")))
#else
#define OSGQOPENGL_EXPORT
#endif

#endif // OSGQOPENGL_EXPORT_H
