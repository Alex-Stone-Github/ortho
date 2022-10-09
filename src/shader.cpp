#include "shader.hpp"

ShaderProgram::ShaderProgram(const std::string& vshader_path, const std::string& fshader_path) {
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
    program = glCreateProgram();
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
}
ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program);
}
void ShaderProgram::use() {
    glUseProgram(program);
}
void ShaderProgram::set_uniform_mat3(const glm::mat3& transform) {
    int location = glGetUniformLocation(program, "transform");
    glUniformMatrix3fv(0, 1, GL_FALSE, (const float*)&transform);
}



