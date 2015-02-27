#version 330 core

uniform sampler2D diffuse_sampler;
out vec4 color;
in vec2 uv_vs;

void main() {
    color = texture(diffuse_sampler, uv_vs);
}