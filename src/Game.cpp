#include "Game.hpp"


Game::Game()
{

}


void Game::initGame()
{
    // set player & map
}

void Game::runGame()
{
    // while (m_isRunning)
    m_player.moveForward(); 

    glm::vec2 activeTileCoords = getActiveTile(2, 4); // TO DO dynamiser
    char actTile = m_map.tileDetection(activeTileCoords);
    tilesConditions(actTile);

    // conditions de fin de partie 
    if (m_player.isFalling()) 
    {
        m_gameOver = true;
        m_isRunning = false;
    }

    // gestion des événements inclus dedans 
}

void Game::endGame()
{
    if (!m_gameOver) {
        // conditions de partie gagnée
    }
    else 
    {
        // conditions de partie perdue 
    }
}

glm::vec2 Game::getActiveTile(float tileWidth, float  tileLength) 
{
    return glm::vec2(round(m_player.getPosition().x / tileWidth), round(m_player.getPosition().z / tileLength));
}


void Game::tilesConditions(char &tile)
{
switch (tile)
    {
    case 'P' || 'S':
        // tout est normal 
        break;

    case 'H':
        m_player.fall();
        break;
    
    default:
        break;
    }
  
}

// events ? 