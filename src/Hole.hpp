#pragma once

#include "Tile.hpp"

class Hole : public Tile {
private:
    std::string m_imageTex = "assets/textures/hole.png";

public:
    Hole(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height, GLuint& texture)
        : Tile(posX, posY, width, height, texture)
    {
    }
};
