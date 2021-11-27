#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Tile.hpp"

namespace glimac {

void Tile::build(GLfloat posX, GLfloat posY, GLsizei width, GLsizei height) {

    ShapeVertex NO, NE, SO, SE; 

    NE.position = glm::vec3(posX + width/2, 0, posY + height/2);
    SO.position = glm::vec3(posX - width/2, 0, posY - height/2);
    NO.position = glm::vec3(posX - width/2, 0, posY + height/2);
    SE.position = glm::vec3(posX + width/2, 0, posY - height/2);

    SO.texCoords = glm::vec2(0, 0);
    SE.texCoords = glm::vec2(1, 0);
    NO.texCoords = glm::vec2(0, 1);
    NE.texCoords = glm::vec2(1, 1);

    NO.normal = glm::vec3(0, 1, 0);
    NE.normal = glm::vec3(0, 1, 0);
    SO.normal = glm::vec3(0, 1, 0);
    SE.normal = glm::vec3(0, 1, 0);
    
    m_Vertices.push_back(SO);
    m_Vertices.push_back(NO);
    m_Vertices.push_back(NE);
    m_Vertices.push_back(SE);

    m_nVertexCount = m_Vertices.size();
}

}
