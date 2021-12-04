#pragma once

#include "common.hpp"
#include "SDLWindowManager.hpp"
#include "Image.hpp"
#include "Program.hpp"
#include "glimac/common.hpp"
#include <iostream>
#include "Tile.hpp"
#include "Map.hpp"

namespace glimac {

void createTexture(GLuint &texture, std::unique_ptr<Image> &imagePointer);
void createVAO(GLuint &vbo, GLuint &vao);
void createVAO(GLuint &vbo, GLuint &vao, GLuint &ibo);

void createTiles(const Map &map, std::vector<Tile> &tiles, const GLfloat &w, const GLfloat &h);
}