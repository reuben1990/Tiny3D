#version 330 core

layout (location = 0) in vec3 position_model;
//uniform mat4 projMatrix;
//uniform mat4 viewMatrix;
//uniform mat4 modelMatrix;

void main() {
    //mat4 mvp = projMatrix * viewMatrix * modelMatrix;
    gl_Position = vec4(position_model, 1.0);
}
