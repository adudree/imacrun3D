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
- dessin d'un élément ?   : -
- void initialisation     : -
- events clavier / souris : [OK]
*/

int main(int argc, char** argv) {

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

    // program
    FilePath applicationPath(argv[0]);
    Program program;
    loadShader(program, argc, argv);
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


    std::string bla = "./src/maps/map1.imac";
    Map myMap(bla); 

    std::cout << myMap.getTypeTile(0, 0) << std::endl;


    // ============ IBO, VBO, VAO ============= //

    GLuint vbo[2]; 
    GLuint ibo[2];
    GLuint vao[2]; 
    
    glGenBuffers(2, vbo);
    glGenBuffers(2, ibo);
    glGenVertexArrays(2, vao);

    // ================ TILES ================= //

    Tile myFloor = Tile(0., 0., 2., 2., vbo[0], ibo[0], vao[0]);

    myFloor.mainVBO(); 
    myFloor.mainIBO();
    myFloor.mainVAO();


    // =============== TEXTURES =============== //

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
        
        glBindVertexArray(myFloor.getVAO());

        MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        MVMatrix = glm::rotate(MVMatrix, glm::radians(10.f), glm::vec3(1, 0, 0));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


        glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
        glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniform1i(locTexture, 0);


        glBindTexture(GL_TEXTURE_2D, texTest);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
        glBindTexture(GL_TEXTURE_2D, 0);
        
        glBindVertexArray(0);

        windowManager.swapBuffers();
    }

    // delete buffers arrays et cie 
    glDeleteBuffers(1, vbo);
    glDeleteVertexArrays(1, vao);
    glDeleteTextures(1, &texTest);

    return EXIT_SUCCESS;
}
