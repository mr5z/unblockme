#pragma once

/* Under Windows, we need WINGDIAPI defined */
#if !defined(WINGDIAPI) && defined(_WIN32)
 #if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__POCC__)
  /* Microsoft Visual C++, Borland C++ Builder and Pelles C */
  #define WINGDIAPI __declspec(dllimport)
 #elif defined(__LCC__)
  /* LCC-Win32 */
  #define WINGDIAPI __stdcall
 #else
  /* Others (e.g. MinGW, Cygwin) */
  #define WINGDIAPI extern
 #endif
 #define GL_WINGDIAPI_DEFINED
#endif /* WINGDIAPI */

#ifndef APIENTRY
 #ifdef _WIN32
  #define APIENTRY __stdcall
 #else
  #define APIENTRY
 #endif
 #define GL_APIENTRY_DEFINED
#endif /* APIENTRY */

#include <GL\GL.h>
#include <GL\GLu.h>

#include "Vec2f.h"

#ifndef NULL
#define NULL 0
#endif