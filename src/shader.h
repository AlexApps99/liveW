#ifndef _SHADER_H
#define _SHADER_H

#include <GL/gl.h>

void checkCompileErrors(unsigned int shader, const char *type);

GLuint loadShaders(const char *vertPath, const char *fragPath);

void checkCompileErrors(unsigned int shader, const char *type);

#endif
