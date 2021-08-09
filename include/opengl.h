#ifndef _OPENGL_H
#define _OPENGL_H

#define GL_GLEXT_PROTOTYPES
#define GLX_GLXEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <X11/Xlib.h>

extern int win_width, win_height;

void initGL();
void swapBuffers();

GLuint genRenderProg();

void checkErrors(const char *);

#endif
