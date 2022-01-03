#version 330 core

in vec2 vFragColor;
in vec2 vFragPosition;

out vec3 fFragColor;
uniform vec3 uColor;
uniform sampler2D uTexture;

void main() {
  fFragColor = vec3(texture(uTexture, vFragColor).xyz);
};