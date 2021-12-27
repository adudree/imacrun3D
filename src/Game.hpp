#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "Player.hpp"
#include "Map.hpp"

class Game {
private:
    float m_speed = 0.5;

    Player m_player;
    Map m_map;

    glm::vec2 m_initPlayerPosition = glm::vec2(0);
    glm::vec2 m_playerPosition = glm::vec2(0);


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

    inline glm::vec3 getPlayerPosition() {return m_player.getPosition();}
    inline Map getMap() { return m_map;}
    inline char getOrientation() { return m_player.getOrientation();}

    inline void setPlayerPosition(glm::vec2 pos) {m_initPlayerPosition = pos;}
    inline void setSpeed(float speed) {m_speed = speed;}

    // Map & Player relation
    glm::vec2 getActiveTile();
    void tilesConditions(char &tile);

    void playerMoves(SDL_Event &e);


    void draw(glm::mat4 proj, glm::mat4 mv); 
};