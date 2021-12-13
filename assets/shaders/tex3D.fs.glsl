#version 300 es
precision mediump float;

in vec3 vPosition_vs;  // Pos. du sommet transformé dans l'espace View
in vec3 vNormal_vs;    // Norma. du sommet transformé dans l'espace View
in vec2 vTexCoords;    // Coordonnées de texture du sommet

out vec4 fFragColor;

uniform sampler2D uTexture;

void main() {
  vec4 texColor = texture(uTexture, vTexCoords);
  if(texColor.a < 0.1) 
    discard;

  fFragColor = texColor;
}