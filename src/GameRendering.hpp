#include <iostream>
#include "Game.hpp"
#include "Skybox.hpp"
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Tile.hpp"
#include "ICamera.hpp"
#include "Surcouche.hpp"

class GameRendering
{
    private:
    glimac::Program m_tilesProgram = glimac::loadProgram("assets/shaders/3D.vs.glsl", "assets/shaders/tex3D.fs.glsl");

    std::vector<std::unique_ptr<Tile>> m_tiles; 

    Skybox m_skybox;

    glm::mat4 m_globalProjMatrix;
    glm::mat4 m_globalMvMatrix; 
    glm::mat4 m_globalNormalMatrix;
    
    public:
        GameRendering(Game &game);
        ~GameRendering() = default; 

        void mainRendering(Game &game, ICamera* camera);

        void drawTiles(); 
};