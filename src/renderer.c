#include "renderer.h"

GLuint vertArray, posBuf, VAO, VBO;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

renderer *init_rend() {
    renderer *r = (renderer *)malloc(sizeof(struct renderer));

    r->win = init_xwin();

    int gl3attr[] = {GLX_CONTEXT_MAJOR_VERSION_ARB,
                     3,
                     GLX_CONTEXT_MINOR_VERSION_ARB,
                     0,
                     GLX_CONTEXT_PROFILE_MASK_ARB,
                     GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
                     GLX_CONTEXT_FLAGS_ARB,
                     GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                     None};

    r->ctx = glXCreateContextAttribsARB(r->win->display, r->win->fbc, NULL,
                                        True, gl3attr);

    if (!r->ctx) {
        printf("Couldn't create an OpenGL context\n");
        exit(1);
    }

    XTextProperty windowName;
    windowName.value = (unsigned char *)"Live wallpaper";
    windowName.encoding = XA_STRING;
    windowName.format = 8;
    windowName.nitems = strlen((char *)windowName.value);

    XSetWMName(r->win->display, r->win->window, &windowName);

    XMapWindow(r->win->display, r->win->window);
    glXMakeCurrent(r->win->display, r->win->window, r->ctx);

    if (cfg.debug) {
        printf("OpenGL:\n\tvendor %s\n\trenderer %s\n\tversion %s\n\tshader "
               "language %s\n",
               glGetString(GL_VENDOR), glGetString(GL_RENDERER),
               glGetString(GL_VERSION),
               glGetString(GL_SHADING_LANGUAGE_VERSION));
    }

    int extCount;
    glGetIntegerv(GL_NUM_EXTENSIONS, &extCount);
    Bool found = False;
    for (int i = 0; i < extCount; ++i)
        if (!strcmp((const char *)glGetStringi(GL_EXTENSIONS, i),
                    "GL_ARB_compute_shader")) {
            if (cfg.debug)
                printf("Extension \"GL_ARB_compute_shader\" found\n");
            found = True;
            break;
        }

    if (!found) {
        printf("Extension \"GL_ARB_compute_shader\" not found\n");
        exit(1);
    }

    glViewport(0, 0, r->win->width, r->win->height);

    checkErrors("Window init");

    return r;
}

void linkBuffers(renderer *r) {
    glUseProgram(r->progID);

    glGenVertexArrays(1, &vertArray);
    glBindVertexArray(vertArray);

    glGenBuffers(1, &posBuf);
    glBindBuffer(GL_ARRAY_BUFFER, posBuf);
    float data[] = {-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f};
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, data, GL_STREAM_DRAW);
    GLint posPtr = glGetAttribLocation(r->progID, "pos");
    glVertexAttribPointer(posPtr, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posPtr);

    checkErrors("Linking buffers");

    glUseProgram(r->progText);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL,
                 GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    checkErrors("Loading font");
}

void render(renderer *r) {
    // Clear screen
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Configure & link opengl
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_CONSTANT_ALPHA);

    glUseProgram(r->progID);
    glBindVertexArray(vertArray);

    // Set uniforms for shaders
    GLint timeLoc = glGetUniformLocation(r->progID, "time");
    if (timeLoc != -1)
        glUniform1f(timeLoc, getUnixTime());

    GLint resolutionLoc = glGetUniformLocation(r->progID, "resolution");
    if (resolutionLoc != -1)
        glUniform2f(resolutionLoc, (float)r->win->width, (float)r->win->height);

    // Draw screen
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    checkErrors("Draw screen");
    swapBuffers(r->win);
}

void checkErrors(const char *desc) {
    GLenum e = glGetError();
    if (e != GL_NO_ERROR) {
        printf("OpenGL error in \"%s\": %s (%d)\n", desc, gluErrorString(e), e);
        exit(1);
    }
}
