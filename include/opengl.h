#ifndef _OPENGL_H
#define _OPENGL_H

#include <GL/gl.h>

extern int win_width, win_height;

void initGL();
void swapBuffers();

GLuint genRenderProg();

void checkErrors(const char *);

#endif
