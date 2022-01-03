#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexColor;

out vec2 vFragColor;
out vec2 vFragPosition; 


uniform mat3 uModelMatrix;


void main() {
  vFragColor = aVertexColor;

  gl_Position = vec4(aVertexPosition, 0, 1);
};