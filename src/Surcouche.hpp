#pragma once

#include "Game.hpp"
#include "Hole.hpp"
#include "Tile.hpp"

void createTiles(Game& game, std::vector<std::unique_ptr<Tile>>& tiles, const GLfloat& w, const GLfloat& h);
