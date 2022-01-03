#pragma once

#include "Tile.hpp"

class Hole : public Tile {
public:
    Hole(GLfloat posX, GLfloat posY, GLuint& texture)
        : Tile(posX, posY, texture) {}
};
