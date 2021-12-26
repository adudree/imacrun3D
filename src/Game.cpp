#include "Game.hpp"

Game::Game() {}

void Game::initGame()
{
    // set player & map
    m_player.setPosition(glm::vec3(m_playerPosition[0], -1.0f, m_playerPosition[1]));
    m_player.setSpeed(m_speed);

    m_isRunning = true;
}

void Game::runGame()
{
    if (m_isRunning && !m_gameOver) {
        m_player.moveForward();

        m_playerPosition = getActiveTile(tilesW, tilesL);
        char actTile     = m_map.tileDetection(m_playerPosition);
        tilesConditions(actTile);

        m_player.fallingTest();

        // std::cout << m_player.isFalling << std::endl; AUDREY TEST
        // conditions de fin de partie
        if (m_player.isFalling) {
            m_gameOver  = true;
            m_isRunning = false;
        }
    }

    // gestion des événements inclus dedans
}

void Game::endGame()
{
    if (!m_gameOver) {
        // conditions de partie gagnée
    }
    else {
        // conditions de partie perdue
    }
}

glm::vec2 Game::getActiveTile(float tileWidth, float tileLength)
{
    return glm::vec2(round(m_player.getPosition().x / tileWidth), round(m_player.getPosition().z / tileLength));
}

void Game::tilesConditions(char& tile)
{
    switch (tile) {
    case 'P' || 'S':
        // tout est normal
        break;

    case 'H':
        if (!m_player.isFalling)
            m_player.fall();
        break;

    default:
        break;
    }
}

void Game::playerMoves(SDL_Event& e)
{
    if (e.key.keysym.sym == SDLK_d) {
        // si on est sur une case "virage" : on tourne
        // sinon :
        if (m_player.canMoveRight(m_playerPosition[0], tilesW))
            m_player.moveRight();
    }

    if (e.key.keysym.sym == SDLK_q) {
        // si on est sur une case "virage" : on tourne
        // sinon :
        if (m_player.canMoveLeft(m_playerPosition[0], tilesW))
            m_player.moveLeft();
    }

    if (e.key.keysym.sym == SDLK_z) {
        m_player.moveForward();
        if (!m_player.isFalling) {
            m_player.jump();
        }
    }

    if (e.key.keysym.sym == SDLK_s) {
        //player.squat();
        m_player.fall();
    }
}