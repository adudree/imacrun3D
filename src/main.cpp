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
// #include <glimac/Map.hpp>

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

    // std::string bla = "maps/map1.imac";
    // Map myMap(bla); 


    // ================ CAMERA ================ //


    // ================ TILES ================= //

    Tile myFloor = Tile(0., 0., 2., 2.);
    int nbSommets = myFloor.getVertexCount(); 
    const ShapeVertex *tabSommets = myFloor.getDataPointer();

    std::cout << "nb sommets  " << nbSommets << std::endl;
    std::cout << "tab sommets " << tabSommets << std::endl;


    // ============ IBO, VBO, VAO ============= //

    GLuint vbo; 
    GLuint ibo;
    GLuint vao; 
    
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    glGenVertexArrays(1, &vao);

    // vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, nbSommets * sizeof(ShapeVertex), tabSommets, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // ibo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    uint32_t indicesRectangle[] = {0, 1, 2, 0, 2, 3};
    // 6 = taille de indicesRectangles 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indicesRectangle, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // vao
    createVAO(vbo, vao, ibo);


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
        
        glBindVertexArray(vao);

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
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &texTest);

    return EXIT_SUCCESS;
}
