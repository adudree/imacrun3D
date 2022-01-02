#include "Game.hpp"

void Game::initGame()
{
    // set player & map

    m_player.setPosition(glm::vec3(m_initPlayerPosition[0], -.5f, m_initPlayerPosition[1]));
    m_player.setSpeed(m_speed);
    m_player.setOrientation('N');
    m_player.setScore(0);

    m_cameraManager.getCameraFirstPerson().resetOffset();

    m_gameOver           = false;
    m_isPaused           = false;
    m_isEnded            = false;
    m_isOnVirage         = false;
    m_player.m_isFalling = false;
    m_player.m_isJumping = false;
    m_isRunning          = true;
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
    m_isOnVirage = false;

    switch (tile) {
    case '-':
        m_player.fall();
        break;

    case 'H':
        if (!m_player.m_isFalling)
            m_player.fall();
        break;

    case 'V':
        m_isOnVirage = true;
        break;

    case 'W':
        m_player.setSpeed(0);
        break;

    case 'E':
        endGame();
        break;

    case 'P' || 'S':
    default:
        break;
    }
}

void Game::onEvent(SDL_Event& e)
{
    m_cameraManager.onEvent(e);

    float refPosition = 0;
    switch (e.type) {
    case SDL_KEYDOWN:
        if (m_player.getOrientation() == 'N' || m_player.getOrientation() == 'S')
            refPosition = m_playerPosition[0];
        else
            refPosition = m_playerPosition[1];

        if (e.key.keysym.sym == SDLK_d) {
            if (m_player.canMoveRight(refPosition) && !m_isOnVirage) {
                m_player.moveRight();
            }
            if (m_isOnVirage) {
                turnRight();
            }

            m_isOnVirage = false;
        }

        if (e.key.keysym.sym == SDLK_q) {
            if (m_player.canMoveLeft(refPosition) && !m_isOnVirage)
                m_player.moveLeft();
            if (m_isOnVirage) {
                turnLeft();
            }
            m_isOnVirage = false;
        }

        if (e.key.keysym.sym == SDLK_z) {
            if (m_player.getPosition().y <= -0.5 && !m_player.m_isJumping)
                m_player.jump();
        }

        if (e.key.keysym.sym == SDLK_s) {
            m_player.bendDown();
        }
        break;

    default:
        break;
    }
}

void Game::turnRight()
{
    switch (m_player.getOrientation()) {
    case 'N':
        m_player.setOrientation('E');
        m_player.setPosition(glm::vec3(m_player.getPosition().x, -.5f, getActiveTile().y * tilesL));
        break;
    case 'E':
        m_player.setOrientation('S');
        m_player.setPosition(glm::vec3(getActiveTile().x * tilesW, -.5f, m_player.getPosition().z));
        break;
    case 'S':
        m_player.setOrientation('O');
        m_player.setPosition(glm::vec3(m_player.getPosition().x, -.5f, getActiveTile().y * tilesL));
        break;
    case 'O':
        m_player.setOrientation('N');
        m_player.setPosition(glm::vec3(getActiveTile().x * tilesW, -.5f, m_player.getPosition().z));
        break;

    default:
        break;
    }

    m_cameraManager.turnCameras(M_PI / 2);
}

void Game::turnLeft()
{
    switch (m_player.getOrientation()) {
    case 'N':
        m_player.setOrientation('O');
        m_player.setPosition(glm::vec3(m_player.getPosition().x, -.5f, getActiveTile().y * tilesL));
        break;
    case 'O':
        m_player.setOrientation('S');
        m_player.setPosition(glm::vec3(getActiveTile().x * tilesW, -.5f, m_player.getPosition().z));
        break;
    case 'S':
        m_player.setOrientation('E');
        m_player.setPosition(glm::vec3(m_player.getPosition().x, -.5f, getActiveTile().y * tilesL));
        break;
    case 'E':
        m_player.setOrientation('N');
        m_player.setPosition(glm::vec3(getActiveTile().x * tilesW, -.5f, m_player.getPosition().z));
        break;

    default:
        break;
    }
    m_cameraManager.turnCameras(-M_PI / 2);
}
