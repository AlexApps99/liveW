#ifndef _RENDERER_H
#define _RENDERER_H

#include "xwin.h"
#include <GL/glx.h>

typedef struct renderer {
    xwin *win;
    GLuint progID;
    GLXContext ctx;
} renderer;

extern GLuint vertArray, posBuf;

renderer *init_rend();
void linkBuffers(renderer *r);
void render(renderer *r);

#endif
