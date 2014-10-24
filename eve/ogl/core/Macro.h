
#pragma once
#ifndef __EVE_OPENGL_MACRO_H__
#define __EVE_OPENGL_MACRO_H__


// Required OpenGL version
#define EVE_WINDOWS_OPENGL_MAJOR_VERSION 4
#define EVE_WINDOWS_OPENGL_MINOR_VERSION 2


// Buffer offset
#define EVE_OGL_BUFFER_OFFSET(i) ((char *)NULL + (i))


// Attributes
#define EVE_OGL_ATTRIBUTE_POSITION  0
#define EVE_OGL_ATTRIBUTE_DIFFUSE   4
#define EVE_OGL_ATTRIBUTE_NORMAL    7


#endif // __EVE_OPENGL_MACRO_H__
