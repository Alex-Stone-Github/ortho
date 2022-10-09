#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

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
    GLuint program = shaders();

    // buffers
    const float vertices[] = {
        0.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0,

    };
    GLuint vao;
    GLuint vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

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
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // white
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        SDL_GL_SwapWindow(window);
    }

    // cleanup code
cleanup:
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
    return 0;
}

GLuint shaders() {
    // get shader src
    constexpr size_t BUFFER_SRC_SIZE = 500;
    char* vert_src_buffer = (char*)calloc(sizeof(char), BUFFER_SRC_SIZE);
    char* frag_src_buffer = (char*)calloc(sizeof(char), BUFFER_SRC_SIZE);
    FILE* vert_file, * frag_file;
    vert_file = fopen("./res/v.glsl", "r");
    frag_file = fopen("./res/f.glsl", "r");
    fread(vert_src_buffer, BUFFER_SRC_SIZE, 1, vert_file);
    fread(frag_src_buffer, BUFFER_SRC_SIZE, 1, frag_file);
    fclose(vert_file);
    fclose(frag_file);
    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vert_shader, 1, &vert_src_buffer, 0); // null terminated
    glShaderSource(frag_shader, 1, &frag_src_buffer, 0); // null terminated
    free(vert_src_buffer);
    free(frag_src_buffer);
    GLint compile_ok;
    glCompileShader(vert_shader);
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &compile_ok);
    if (!compile_ok) {
        fprintf(stderr, "Failed to compile vertex shader\n");
        char* error = (char*)calloc(sizeof(char), 500);
        int message_length, not_relevant;
        glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &message_length);
        glGetShaderInfoLog(vert_shader, message_length, &not_relevant, error);
        fprintf(stderr, error); // spooky
        free(error);
    }
    glCompileShader(frag_shader);
    if (!compile_ok) {
        fprintf(stderr, "Failed to compile fragment shader\n");
        char* error = (char*)calloc(sizeof(char), 500);
        int message_length, not_relevant;
        glGetShaderiv(frag_shader, GL_INFO_LOG_LENGTH, &message_length);
        glGetShaderInfoLog(frag_shader, message_length, &not_relevant, error);
        fprintf(stderr, error); // spooky
        free(error);
    }
    GLuint program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
    glLinkProgram(program);
    if (!compile_ok) {
        fprintf(stderr, "Failed to link shader program\n");
        char* error = (char*)calloc(sizeof(char), 500);
        int message_length, not_relevant;
        glGetProgramiv(frag_shader, GL_INFO_LOG_LENGTH, &message_length);
        glGetProgramInfoLog(program, message_length, &not_relevant, error);
        fprintf(stderr, error); // spooky
        free(error);
    }
    return program;
}









