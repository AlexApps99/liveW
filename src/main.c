#include "config.h"
#include "renderer.h"
#include "shader.h"
#include "utils.h"
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool cont = 1;
struct config cfg;
int win_width, win_height;

void sig_handler(int sig_no) {
    if (sig_no == SIGINT) {
        printf("\rExiting\n");
        cont = 0;
    }
}

int main(int argc, char *argv[]) {
    // Handle Ctrl+C
    struct sigaction action;
    action.sa_handler = &sig_handler;
    sigaction(SIGINT, &action, NULL);

    // Parse arguments
    if (!parseArgs(argc, argv)) {
        printHelp();
        return 0;
    }

    // Init renderer
    renderer *rend = init_rend();

    // Load shaders
    char *vertPath = NULL, *fragPath = NULL;
    if (cfg.shaderName) {
        vertPath = (char *)malloc(
            (strlen("Shaders//vert.glsl") + strlen(cfg.shaderName)) *
            sizeof(char));
        fragPath = (char *)malloc(
            (strlen("Shaders//frag.glsl") + strlen(cfg.shaderName)) *
            sizeof(char));
        sprintf(vertPath, "Shaders/%s/vert.glsl", cfg.shaderName);
        sprintf(fragPath, "Shaders/%s/frag.glsl", cfg.shaderName);
    }
    rend->progID = loadShaders(vertPath, fragPath);

    linkBuffers(rend);

    while (cont) {
        render(rend);

        usleep(1000000 / cfg.fps);
    }

    usleep(1000000 / cfg.fps);

    return 0;
}
