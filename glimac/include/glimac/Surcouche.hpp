#pragma once

#include <iostream>

#include "common.hpp"
#include "SDLWindowManager.hpp"
#include "Image.hpp"
#include "Program.hpp"

#include "Tile.hpp"
#include "Hole.hpp"
#include "Map.hpp"
#include "Texture.hpp"

namespace glimac {

void createTiles(const Map &map, std::vector<Tile> &tiles, Player &p, const GLfloat &w, const GLfloat &h);
}