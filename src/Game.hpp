#pragma once

#include <iostream>
#include "Player.hpp"
#include "Map.hpp"

class Game {
private:
    Player m_player;
    Map m_map;

    bool m_isRunning = false;
    bool m_gameOver = false;

public: 
    Game();
    ~Game() = default;
    
    // Game states 
    void initGame();
    void runGame(); 
    void endGame();

    // Map & Player relation
    glm::vec2 getActiveTile(float tileWidth, float tileLength);
    void tilesConditions(char &tile);

};
