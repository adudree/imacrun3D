#pragma once

#include <iostream>
#include "Player.hpp"
#include "Map.hpp"


class Game {
private:
    float m_speed = 0.5;

    Player m_player;
    Map m_map;


    glm::vec2 m_playerPosition = glm::vec2(0);


public: 
    bool m_isRunning = false;
    bool m_gameOver = false;

    Game();
    ~Game() = default;
    
    // Game states 
    void initGame();
    void runGame(); 
    void endGame();

    inline glm::vec3 getPlayerPosition() {return m_player.getPosition();}
    inline Map getMap() { return m_map;}

    inline void setPlayerPosition(glm::vec2 pos) {m_playerPosition = pos;}
    inline void setSpeed(float speed)      {m_speed = speed;}

    // Map & Player relation
    glm::vec2 getActiveTile(float tileWidth, float tileLength);
    void tilesConditions(char &tile);

    void playerMoves(SDL_Event &e);
};
