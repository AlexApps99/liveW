#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct config {
    int debug;
    char *src;
    bool plasma;
    bool windowed;
    bool geometry;
    float offX, offY;
    float width, height;
    float transparency;
    char *shaderName;
    unsigned int fps;
};

extern struct config cfg;

void printHelp();
bool parseArgs(int argc, char *argv[]);

#endif // _CONFIG_H_
