#pragma once

#include <glimac/glm.hpp>
#include "Arc.hpp"
#include "Coin.hpp"
#include "Game.hpp"
#include "Hole.hpp"
#include "Tile.hpp"
#include "Wall.hpp"

void createTiles(Game& game, std::vector<std::unique_ptr<Tile>>& tiles, std::vector<std::unique_ptr<Wall>>& walls, std::vector<std::unique_ptr<Arc>>& arc);
