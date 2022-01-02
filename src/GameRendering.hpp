#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Game.hpp"
#include "ICamera.hpp"
#include "Skybox.hpp"
#include "Surcouche.hpp"
#include "Coin.hpp"
#include "Tile.hpp"
#include "Wall.hpp"

class GameRendering {
private:
    glimac::Program m_tilesProgram = glimac::loadProgram("assets/shaders/3D.vs.glsl", "assets/shaders/tex3D.fs.glsl");

    std::vector<std::unique_ptr<Tile>> m_tiles;
    std::vector<std::unique_ptr<Wall>> m_walls;  
    std::vector<std::unique_ptr<Coin>> m_coins;

    Skybox m_skybox;

    glm::mat4 m_globalProjMatrix;
    glm::mat4 m_globalMvMatrix;
    glm::mat4 m_globalNormalMatrix;

public:
    GameRendering(Game& game);
    ~GameRendering() = default;

    void mainRendering(Game& game);

        void drawTiles(); 
        void drawWalls();
        void drawCoins();
};