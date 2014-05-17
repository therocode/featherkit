#pragma once
#if defined(__EMSCRIPTEN__)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#else
#include <fea/rendering/gl_core_3_2.h>
#endif

#if defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#elif !defined(__EMSCRIPTEN__)
#include <GL/gl.h>
#include <GL/glu.h>
#endif
