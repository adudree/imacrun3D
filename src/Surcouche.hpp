#pragma once

#include <glimac/glm.hpp>
#include "Game.hpp"
#include "Hole.hpp"
#include "Tile.hpp"
#include "Coin.hpp"

void createTiles(Game& game, std::vector<std::unique_ptr<Tile>>& tiles);