#pragma once

#include "Map.hpp"
#include "Player.hpp"
#include "Tile.hpp"

void createTiles(const Map& map, std::vector<Tile>& tiles, Player& p, const GLfloat& w, const GLfloat& h);
