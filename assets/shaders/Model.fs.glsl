#version 300 es
precision mediump float;

out vec4 fFragColor;

in vec3 vPosition_vs;  // Pos. du sommet transformé dans l'espace View
in vec3 vNormal_vs;    // Norma. du sommet transformé dans l'espace View
in vec2 vTexCoords;    // Coordonnées de texture du sommet

uniform sampler2D texture_diffuse1;

void main()
{    
    fFragColor = texture(texture_diffuse1, vTexCoords);
}