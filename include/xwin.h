#ifndef _XWIN_H
#define _XWIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xatom.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/Xrender.h>
#include <X11/extensions/shape.h>

#include "config.h"
#include "opengl.h"

typedef struct xwin {
    Display *display;
    Window root;
    Window window;
    Window desktop;
    GLint screenNum;

    XSetWindowAttributes swa;
    GLXFBConfig fbc, *fbcs;
    XVisualInfo *vi;
    XRenderPictFormat *pict;
    Colormap cmap;

    GLint offX, offY;
    GLint width, height;
} xwin;

xwin *init_xwin();
void swapBuffers();

#endif
