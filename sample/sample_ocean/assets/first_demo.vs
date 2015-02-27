#version 330 core

layout (location = 0) in vec3 position_model;
layout (location = 1) in vec2 uv;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 uv_vs;

void main() {
    mat4 mvp = projMatrix * viewMatrix * modelMatrix;
    gl_Position = viewMatrix * modelMatrix * vec4(position_model, 1.0);
    uv_vs = uv;
}
