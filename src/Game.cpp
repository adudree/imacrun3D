#include "Game.hpp"

Game::Game() {}

void Game::initGame()
{
    // set player & map

    m_player.setPosition(glm::vec3(m_initPlayerPosition[0], -.5f, m_initPlayerPosition[1]));
    m_player.setSpeed(m_speed);

    m_gameOver = false;
    m_isPaused = false;
    m_isEnded  = false;

    m_player.isFalling = false;
    m_player.isJumping = false;

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

        // défaite
        if (m_player.isFalling) {
            m_gameOver = true;
            endGame();
        }
    }
}

void Game::pauseGame()
{
    if (m_isPaused) {
        m_player.setSpeed(0);
    }
    else {
        m_player.setSpeed(m_speed);
    }
}

void Game::endGame()
{
    m_isRunning = false;

    if (!m_gameOver) {
        // conditions de partie gagnée
        std::cout << "C'est gagné, bravo !" << std::endl;
    }
    else {
        // conditions de partie perdue
        std::cout << "Oh le loser..." << std::endl;
    }

    initGame();
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

    case 'E':
        endGame();
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
        if (m_player.getPosition().y <= -0.5 && !m_player.isJumping)
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