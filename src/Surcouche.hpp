#pragma once

#include "Tile.hpp"
#include "Hole.hpp"
#include "Game.hpp"

void createTiles(Game &game, std::vector<std::unique_ptr<Tile>>& tiles, const GLfloat& w, const GLfloat& h);
