#version 330 core

// Attributs de sommet
layout(location = 0) in vec3 aVertexPosition; // Position 
layout(location = 1) in vec3 aVertexNormal; // Normale
layout(location = 2) in vec2 aVertexTexCoords; // Coordonnées de texture 

// Matrices de transformations reçues en uniform
uniform mat4 uMVPMatrix;        // Model View Projection (Clip Coord.)
uniform mat4 uMVMatrix;         // Model View (View Coord.)
uniform mat4 uNormalMatrix;     // Normale

// Sorties du shader
out vec3 vPosition_vs;  // Pos. du sommet transformé dans l'espace View
out vec3 vNormal_vs;    // Norma. du sommet transformé dans l'espace View
out vec2 vTexCoords;    // Coordonnées de texture du sommet

void main() {
    
    // Passage en coord. homogènes (de vec3 à vec4)
    vec4 vertexPosition = vec4(aVertexPosition, 1); // 1 car point
    vec4 vertexNormal = vec4(aVertexNormal, 0);     // 0 car vecteur

    // Calcul sorties en view coordinates
    vPosition_vs = vec3(uMVMatrix * vertexPosition);
    vNormal_vs = vec3(uNormalMatrix * vertexNormal); 
    vTexCoords = aVertexTexCoords;

    gl_Position = uMVPMatrix *  vertexPosition;
}
