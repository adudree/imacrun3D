#include "Game.hpp"

Game::Game() {}

void Game::initGame()
{
    // set player & map

    m_player.setPosition(glm::vec3(m_initPlayerPosition[0], -.5f, m_initPlayerPosition[1]));
    m_player.setSpeed(m_speed);

    m_gameOver = false;
    m_isPaused = false;
    m_isEnded = false;
    m_isOnVirage = false; 
    m_player.m_isFalling = false;
    m_player.m_isJumping = false;
    m_isRunning = true;
}

void Game::runGame()
{
    if (m_isRunning && !m_gameOver) {
        m_player.update();

        m_playerPosition = getActiveTile();
        char actTile     = m_map.getTypeTile(m_playerPosition);
        tilesConditions(actTile);

        // défaite
        if (m_player.m_isFalling) {
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
        m_isOnVirage = false; 
        break;

    case 'H':
        m_isOnVirage = false; 
        if (!m_player.m_isFalling)
            m_player.fall();
        break;

    case 'V':
        m_isOnVirage = true; 
        break;

    case 'E':
        m_isOnVirage = false; 
        endGame();
        break;

    default:
        break;
    }
}

void Game::playerMoves(SDL_Event& e)
{
    if (e.key.keysym.sym == SDLK_d) {
        if (m_player.canMoveRight(m_playerPosition[0]) && !m_isOnVirage)
            m_player.moveRight();
        else if (m_isOnVirage)
            turnRight();
    }

    if (e.key.keysym.sym == SDLK_q) {
        if (m_player.canMoveLeft(m_playerPosition[0]) && !m_isOnVirage)
            m_player.moveLeft();
        else if (m_isOnVirage)
            turnLeft();
    }

    if (e.key.keysym.sym == SDLK_z) {
        if (m_player.getPosition().y <= -0.5 && !m_player.m_isJumping) 
            m_player.jump();
    }

    if (e.key.keysym.sym == SDLK_s) {
        m_player.bendDown();
    }
}

void Game::draw(glm::mat4 proj, glm::mat4 mv)
{
    m_player.draw(proj, mv);
}


void Game::turnRight()
{
    switch (m_player.getOrientation())
    {
    case 'N':
        m_player.setOrientation('E');
        break;
    case 'E':
        m_player.setOrientation('S');
        break;
    case 'S':
        m_player.setOrientation('O');
        break;
    case 'O':
        m_player.setOrientation('N');
        break;
    
    default:
        break;
    }
}


void Game::turnLeft()
{
    switch (m_player.getOrientation())
    {
    case 'N':
        m_player.setOrientation('O');
        break;
    case 'O':
        m_player.setOrientation('S');
        break;
    case 'S':
        m_player.setOrientation('E');
        break;
    case 'E':
        m_player.setOrientation('N');
        break;
    
    default:
        break;
    }
}