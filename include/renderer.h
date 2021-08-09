#ifndef _RENDERER_H
#define _RENDERER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>

#include "config.h"
#include "utils.h"
#include "xwin.h"

typedef struct renderer {
    xwin *win;
    GLuint progID, progText;
    GLXContext ctx;
} renderer;

extern GLuint vertArray, posBuf, VAO, VBO;

renderer *init_rend();
void linkBuffers(renderer *r);
void render(renderer *r);

#endif
