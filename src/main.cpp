#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <vector>

#include <glimac/Image.hpp>
#include <glimac/Surcouche.hpp>
#include <glimac/Tile.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Map.hpp>

#include <fstream> 
#include <string> 
#include <glimac/glm.hpp>


using namespace glimac;

/* ======= surcouche sdl =======
- chargement shader       : [OK]
- vao                     : [OK]
- chargement textures     : [OK] 
- dessin d'un élément     : [OK]
- events clavier / souris : [OK]
- void initialisation     : -
*/

int main(/*int argc, char** argv*/) {

    // ============ INITIALIZATION =========== //

    // window
    GLint WIDTH = 800;
    GLint HEIGHT = 800;
    SDLWindowManager windowManager(WIDTH, HEIGHT, "IMAC RUN 3D");

    // glew : mettre un catch try par ici 
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    // program + shaders 
    //FilePath applicationPath(argv[0]);
    //loadShader(program, argc, argv);
    Program program;
    program = loadProgram( "./src/shaders/3D.vs.glsl", "./src/shaders/tex3D.fs.glsl");
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


    // ================= MAP ================== //

    std::string fichierMap = "./src/maps/map1.imac";
    Map myMap(fichierMap); 


    // -------- Récup infos de la map --------- //

    std::vector<Tile> tiles;
    createTiles(myMap, tiles, 1, 3); 

    // =============== TEXTURES =============== //
    // créer toutes les textures nécessaires ici 

    GLuint texTest;

    std::unique_ptr<Image> test = loadImage("./src/assets/textures/cardinale.jpg");

    createTexture(texTest, test);


    // ================= LOOP ================= //

    bool done = false;
    while(!done) {

        // events
        gestionEvent(done, windowManager); 

        // ============ RENDERING CODE =========== //

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // matrices et compagnie

        MVMatrix = glm::translate(glm::mat4(1), glm::vec3(-1, 0, -5));
        MVMatrix = glm::rotate(MVMatrix, glm::radians(10.f), glm::vec3(1, 0, 0));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        // valeurs uniformes 

        glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
        glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniform1i(locTexture, 0);

        // dessin des tuiles 

        for (size_t i = 0; i < tiles.size(); i++) {
            tiles[i].drawTile(texTest);
        }

        windowManager.swapBuffers();
    }


    // delete buffers arrays et cie : trouver moyen de le faire izi 
    // glDeleteBuffers(1, vbo);
    // glDeleteVertexArrays(1, vao);
    glDeleteTextures(1, &texTest);

    return EXIT_SUCCESS;
}
