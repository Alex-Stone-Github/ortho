#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <GL/gl.h>

#define WIDTH 800
#define HEIGHT 600

void shaders();

int main(int argc, char** argv) {
    // init sdl2
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Failed to init sdl2: %s", SDL_GetError());
    }

    // create a window
    SDL_Window* window = SDL_CreateWindow("ortho", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    // opengl stuff
    SDL_GLContext context = SDL_GL_CreateContext(window);

    // shaders
    shaders();

    bool running = true;
    while (running) {
        // events
        SDL_Event e;while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        // process

        // draw
        glViewport(0, 0, WIDTH, HEIGHT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // white
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }

    // cleanup code
cleanup:
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
    return 0;
}

void shaders() {
}
