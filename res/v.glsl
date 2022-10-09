#version 330 core

layout (location = 0) in vec3 position;

uniform mat3 transform;

void main() {
    gl_Position = vec4(transform * position, 1.0);
}

