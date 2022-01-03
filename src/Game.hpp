#pragma once

#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "CameraManager.hpp"
#include "Coin.hpp"
#include "Player.hpp"

class Game {
private:
    float m_speed = 0.5;

    Player                             m_player;
    Map                                m_map;
    std::vector<std::unique_ptr<Coin>> m_coins;

    glm::vec2 m_initPlayerPosition = glm::vec2(0);
    glm::vec2 m_playerPosition     = glm::vec2(0);

    CameraManager m_cameraManager;

public:
    bool m_isRunning  = false;
    bool m_isOnVirage = false;
    bool m_gameOver   = false;
    bool m_isPaused   = false;
    bool m_isEnded    = false;

    Game(){};
    ~Game() = default;

    // Game states
    void initGame();
    void runGame();
    void pauseGame();
    void endGame();

    void turnLeft();
    void turnRight();

    // Getter
    inline glm::vec3 getPlayerPosition() { return m_player.getPosition(); }
    inline char      getOrientation() { return m_player.getOrientation(); }
    inline Map       getMap() { return m_map; }
    inline int       getScore() const { return m_player.getScore(); }

    // Setter
    inline void setPlayerPosition(glm::vec2 pos) { m_initPlayerPosition = pos; }
    inline void setSpeed(float speed) { m_speed = speed; }

    // Map & Player relation
    glm::vec2 getActiveTile();
    void      tilesConditions(const char& tile);
    void      onEvent(SDL_Event& e);

    friend class GameRendering;

    // Camera
    ICamera& getCamera() { return m_cameraManager.getCamera(); };
};
