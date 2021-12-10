#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <vector>

#include <glimac/Image.hpp>
#include "Surcouche.hpp"
#include "Tile.hpp"
#include "Sphere.hpp"
#include "Map.hpp"
#include "Event.hpp"

#include <fstream> 
#include <string> 
#include <glimac/glm.hpp>


using namespace glimac;

int main() {

    // ============ INITIALIZATION =========== //

    // window
    GLint WIDTH = 800;
    GLint HEIGHT = 800;
    SDLWindowManager windowManager(WIDTH, HEIGHT, "IMAC RUN 3D");
    SDL_EnableKeyRepeat(100, 10);

    // glew : mettre un catch try par ici 
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    // program + shaders 
    // 
    Program program;
    program = loadProgram( "assets/shaders/3D.vs.glsl", "assets/shaders/tex3D.fs.glsl");
    program.use();

    glEnable(GL_DEPTH_TEST);


    // ================ MATRIX ================ //

    GLint locMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint locMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint locNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint locTexture = glGetUniformLocation(program.getGLId(), "uTexture");

    glm::mat4 ProjMatrix; 
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;

    ProjMatrix = glm::perspective(70.f, float(WIDTH/HEIGHT), 0.1f, 100.0f);

    // =============== TEXTURES =============== //


    // ================= MAP ================== //

    std::string fichierMap = "assets/maps/map1.imac";
    Map myMap(fichierMap); 
    std::vector<Tile> tiles;
    createTiles(myMap, tiles, 1, 1); // 1 & 3 w & h de chaque tuile

    // ================ CAMERA ================ //

    CameraThirdPerson camera;


    // ================= LOOP ================= //

    bool done = false;
    while(!done) {

        // events
        gestionEvent(done, windowManager, camera); 

        // ============ RENDERING CODE =========== //

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // matrices et compagnie

        MVMatrix = camera.computeMatrix({0.f, 0.f, 0.f}); // TODO remplacer par la position du joueur
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        // valeurs uniformes 

        glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
        glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniform1i(locTexture, 0);

        // dessin des tuiles 

        for (size_t i = 0; i < tiles.size(); i++) {
            tiles[i].drawTile();
        }

        windowManager.swapBuffers();
    }


    // delete buffers arrays et cie : trouver moyen de le faire izi 
    // glDeleteBuffers(1, vbo);
    // glDeleteVertexArrays(1, vao);
    //glDeleteTextures(1, &texTest);

    return EXIT_SUCCESS;
}
