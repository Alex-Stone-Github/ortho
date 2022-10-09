#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "model.hpp"

#define WIDTH 800
#define HEIGHT 600

GLuint shaders();

int main(int argc, char** argv) {
    // init sdl2
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        fprintf(stderr, "Failed to init sdl2: %s", SDL_GetError());

    // create a window
    SDL_Window* window = SDL_CreateWindow("ortho", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    // opengl stuff
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if (glewInit() != GLEW_OK)
        fprintf(stderr, "Failed to init glew\n");

    // shaders
    ShaderProgram program("./res/v.glsl", "./res/f.glsl");

    // buffers
    const float vertices[] = {
        0.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
    };
    const unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    Model model(vertices, 16, indices, 6);

    while (true) {
        // events
        SDL_Event e;while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                goto cleanup;
            }
        }

        // draw
        glViewport(0, 0, WIDTH, HEIGHT);
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // white
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        glm::mat3 matrix = glm::mat3(
                1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0
                );
        program.set_uniform_mat3(matrix);
        model.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        /*
         * Let this comment be here for a reminder of a dumb mistake, a terrible mistake. This
         * mode parameter needs to be an unsigned type, or it will not render anything correctly,
         * so always keep this as an unsigned type.
         */

        SDL_GL_SwapWindow(window);
    }
cleanup:
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
    return 0;
}










