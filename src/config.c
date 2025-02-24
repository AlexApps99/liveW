#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

void printHelp() {
    printf("Usage: liveW <options>\n");
    printf("Options:\n");
    printf("   -h Print help\n");
    printf("   -d Turn debug on\n");
    printf("   -w Window mode\n");
    printf("   -g Window geometry WIDTHxHEIGHT (default 800x600)\n");
    printf("   -o Position of window relative to top left corner TOPxLEFT "
           "(default 0x0)\n");
    printf("   -t Transparency (default 1.0)\n");
    printf("   -p Shader name in Shaders folder\n");
    printf("   -f FPS (default 30)\n");
}

bool parseArgs(int argc, char *argv[]) {
    cfg.debug = false;
    cfg.src = NULL;
    cfg.windowed = false;
    cfg.geometry = false;
    cfg.offX = 0;
    cfg.offY = 0;
    cfg.width = 800;
    cfg.height = 600;
    cfg.transparency = 1.0;
    cfg.shaderName = NULL;
    cfg.fps = 30;

    char c;
    // TODO
    const char *opt_str = "hdws:t:g:o:f:p:";
    while ((c = getopt(argc, argv, opt_str)) != -1) {
        switch (c) {
        case 'h':
            return false;
            break;
        case 'd':
            cfg.debug = true;
            break;
        case 'w':
            cfg.windowed = true;
            break;
        case 's':
            cfg.src = strdup(optarg);
            break;
        case 't':
            sscanf(optarg, "%f", &cfg.transparency);
            break;
        case 'g':
            sscanf(optarg, "%fx%f", &cfg.width, &cfg.height);
            cfg.geometry = true;
            break;
        case 'o':
            sscanf(optarg, "%fx%f", &cfg.offX, &cfg.offY);
            cfg.geometry = true;
            break;
        case 'p':
            cfg.shaderName = strdup(optarg);
            break;
        case 'f':
            sscanf(optarg, "%u", &cfg.fps);
            break;
        default:
            return false;
            break;
        }
    }
    return true;
}
