#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "Map.hpp"
#include "Player.hpp"
#include "Coin.hpp"

class Game {
private:
    float m_speed = 0.5;

    Player m_player;
    Map    m_map;
    std::vector<std::unique_ptr<Coin>> m_coins;

    glm::vec2 m_initPlayerPosition = glm::vec2(0);
    glm::vec2 m_playerPosition     = glm::vec2(0);

public:
    bool m_isRunning = false;

    bool m_gameOver = false;
    bool m_isPaused = false;
    bool m_isEnded = false;
    bool m_isOnVirage = false; 

    Game();
    ~Game() = default;

    // Game states
    void initGame();
    void runGame();
    void pauseGame();
    void endGame();

    void turnLeft();
    void turnRight();

    inline glm::vec3    getPlayerPosition() {return m_player.getPosition();}
    inline char         getOrientation()    {return m_player.getOrientation();}
    inline Map          getMap()            {return m_map;}

    inline void setPlayerPosition(glm::vec2 pos){m_initPlayerPosition = pos;}
    inline void setSpeed(float speed)           {m_speed = speed;}

    // Map & Player relation
    glm::vec2   getActiveTile();
    void        tilesConditions(char& tile);

    void        playerMoves(SDL_Event& e);

    inline int  getScore() const { return m_player.getScore();}

    friend class GameRendering;
};