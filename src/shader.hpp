#pragma once

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

class ShaderProgram {
public:
    ShaderProgram(const std::string& vshader_path, const std::string& fshader_path);
    ~ShaderProgram();
    void use();
    void set_uniform_mat3(const glm::mat3& transform);
private:
    GLuint program;
};

