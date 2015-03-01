#version 330 core

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

layout (location = 0) in vec3 position_model;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec3 position_vs;
out vec3 normal_vs;
out vec2 uv_vs;

void main() {
    mat4 mvp = projMatrix * viewMatrix * modelMatrix;
    gl_Position = mvp * vec4(position_model, 1.0);
    position_vs = position_model;
    normal_vs = normal;
    uv_vs = uv;
}