#pragma once

#include "Map.hpp"
#include "Player.hpp"
#include "Tile.hpp"

void createTiles(const Map& map, std::vector<std::unique_ptr<Tile>>& tiles, Player& p, const GLfloat& w, const GLfloat& h);
