#pragma once

#include <GL/glew.h>

class Model {
public:
    Model(const float* vertices, size_t vertex_count,
            const unsigned int* indices, size_t index_count);
    ~Model();
    void bind();
private:
    GLuint vao;
    GLuint ibo;
    GLuint vbo;
};

