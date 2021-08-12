#ifndef _XWIN_H
#define _XWIN_H

#include <GL/glx.h>
#include <X11/extensions/Xrender.h>

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
