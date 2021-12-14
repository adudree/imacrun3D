#pragma once

#include "Tile.hpp"

class Hole : public Tile {
private:
    // std::string m_imageTex = "bin/assets/textures/hole.png"; // TODO: est-ce qu'on a besoin de le définir ici parce que le constructeur prend déjà en paramètre une texture qui et créée ailleurs

public:
    Hole(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height, GLuint& texture)
        : Tile(posX, posY, width, height, texture)
    {
    }
};
