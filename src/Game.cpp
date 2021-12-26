#include "Game.hpp"

Game::Game() {}

void Game::initGame()
{
    // set player & map
    m_player.setPosition(glm::vec3(m_playerPosition[0], -.5f, m_playerPosition[1]));
    m_player.setSpeed(m_speed);

    m_isRunning = true;
}

void Game::runGame()
{
    if (m_isRunning && !m_gameOver) {
        m_player.update();

        m_playerPosition = getActiveTile();
        char actTile     = m_map.getTypeTile(m_playerPosition);
        tilesConditions(actTile);

        // conditions de fin de partie
        if (m_player.isFalling) {
            m_gameOver  = true;
            m_isRunning = false;
        }
    }
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

glm::vec2 Game::getActiveTile()
{
    return glm::vec2(round(m_player.getPosition().x / tilesW), round(m_player.getPosition().z / tilesL));
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
        if (m_player.canMoveRight(m_playerPosition[0]))
            m_player.moveRight();
    }

    if (e.key.keysym.sym == SDLK_q) {
        // si on est sur une case "virage" : on tourne
        // sinon :
        if (m_player.canMoveLeft(m_playerPosition[0]))
            m_player.moveLeft();
    }

    if (e.key.keysym.sym == SDLK_z) {
        if (m_player.getPosition().y <= -1 && !m_player.isJumping) 
            m_player.jump();
    }

    if (e.key.keysym.sym == SDLK_s) {
        //player.squat();
    }
}

void Game::draw(glm::mat4 proj, glm::mat4 mv)
{
    m_player.draw(proj, mv);
}