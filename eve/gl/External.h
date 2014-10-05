
#pragma once
#ifndef __EVE_OPENGL_EXTERNAL_H__
#define __EVE_OPENGL_EXTERNAL_H__


#ifndef __EVE_CORE_SYSTEM_DEFINITION__
#include "eve/core/SystemDefinition.h"
#endif


#if defined( EVE_OS_WIN )
#include <glew/GL/glew.h>
#include <glew/GL/wglew.h>
#endif 


#if defined( EVE_OS_LINUX )
#include <glew/GL/glew.h>
#define GL_GLEXT_PROTOTYPES 1
#include <glew/GL/gl.h>
#include <glew/GL/glext.h>
#endif


#if defined( EVE_OS_DARWIN )
#include <OpenGL/gl.h>
#  define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#endif


#endif // __EVE_OPENGL_EXTERNAL_H__
