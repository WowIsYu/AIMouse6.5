
#ifndef GLOBAL_H
#define GLOBAL_H

#if defined(_WIN32)
#ifdef _MSC_VER
#pragma warning(disable : 4251)
#if defined(HDATASYSTEM_LIBRARY)
#define HDATASYSTEM_API __declspec(dllexport)
#else
#define HDATASYSTEM_API __declspec(dllimport)
#endif

#elif defined(__linux__)
#if defined(HDATASYSTEM_LIBRARY)
#define HDATASYSTEM_API __attribute__((visibility("default")))
#else
#define HDATASYSTEM_API __attribute__((visibility("default")))
#endif
#endif
#endif

#if !defined(HDATASYSTEM_API)
#define HDATASYSTEM_API
#endif
#endif // GLOBAL_H
