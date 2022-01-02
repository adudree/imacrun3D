#include "GameRendering.hpp"

GameRendering::GameRendering(Game& game)
{
    createTiles(game, m_tiles, m_walls); // dans surcouche
    createCoins(game.m_map, m_coins);
    m_globalProjMatrix = glm::perspective(70.f, float(800) / float(800), 0.1f, 100.0f);
}

void GameRendering::drawTiles()
{
    GLint locMVPMatrix    = glGetUniformLocation(m_tilesProgram.getGLId(), "uMVPMatrix");
    GLint locMVMatrix     = glGetUniformLocation(m_tilesProgram.getGLId(), "uMVMatrix");
    GLint locNormalMatrix = glGetUniformLocation(m_tilesProgram.getGLId(), "uNormalMatrix");
    GLint locTexture      = glGetUniformLocation(m_tilesProgram.getGLId(), "uTexture");

    glm::mat4 ProjMatrix   = m_globalProjMatrix;
    glm::mat4 MVMatrix     = m_globalMvMatrix;
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    m_tilesProgram.use();
    glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniform1i(locTexture, 0);

    // draw tiles

    for (size_t i = 0; i < m_tiles.size(); i++) {
        m_tiles[i]->drawTile();
    }
}

void GameRendering::drawWalls()
{
    for (size_t i = 0; i < m_walls.size(); i++) {
        m_walls[i]->draw(m_globalProjMatrix, m_globalMvMatrix);
    }
}

void GameRendering::drawCoins()
{
    for (size_t i = 0; i < m_coins.size(); i++) {

        if (!(m_coins[i]->getIsCollected())) {
            m_coins[i]->draw(m_globalProjMatrix, m_globalMvMatrix);
        }
    }
}

void GameRendering::mainRendering(Game& game)
{
    if (game.m_player.getPosition() == glm::vec3(game.m_initPlayerPosition[0], -.5f, game.m_initPlayerPosition[1])) {
        for (size_t i = 0; i < m_coins.size(); i++) {
            m_coins[i]->setIsCollected(false);
            m_coins[i]->resetRotateFloat();
        }
    }
    else {
        m_globalMvMatrix     = game.getCamera().computeMatrix(game.getPlayerPosition());
        m_globalMvMatrix     = glm::translate(m_globalMvMatrix, glm::vec3(0, 0.2f, 0));
        m_globalNormalMatrix = glm::transpose(glm::inverse(m_globalMvMatrix));

        m_skybox.render(m_globalProjMatrix, m_globalMvMatrix);
        drawTiles();
        drawWalls();
        drawCoins();
        game.m_player.draw(m_globalProjMatrix, m_globalMvMatrix); // fonction amie

        for (size_t i = 0; i < m_coins.size(); i++) {
            if (m_coins[i]->isCollision(game.m_player.getPosition())) {
                game.m_player.addPointToScore(m_coins[i]->getNbPoint());
                m_coins[i]->setIsCollected(true);
/*                 m_coins.erase(m_coins.begin() + i);
                m_coins.shrink_to_fit(); */
            }
        }
    }
}