#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <glimac/Image.hpp>
#include <glimac/Surcouche.hpp>
#include <glimac/Map.hpp>

using namespace glimac;

/* ======= surcouche sdl =======
- chargement shader       : -
- vao                     : [OK]
- chargement textures     : [OK] 
- dessin d'un élément ?   : -
- void initialisation     : -
- events clavier / souris : [OK]
*/


// on est d'accord, on multitexture pas hein ? ça a l'air chiant à gérer


int main(/*int argc, char** argv*/) {

    // Initialize SDL and open a window
    GLint WIDTH = 800;
    GLint HEIGHT = 800;

    SDLWindowManager windowManager(WIDTH, HEIGHT, "IMAC RUN 3D");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    std::string bla = "maps/map1.imac";

    //std::vector<std::vector<char>> map = readMap(bla);

    // ============ INITIALIZATION =========== //
    
    // Test de profondeur du GPU
    glEnable(GL_DEPTH_TEST);    

    // Chargement des images 

    // Chargement caméra

    // init objets + nb sommets blabla 

    // VBO 

    // VAO 

    // textures

    // Application loop:
    bool done = false;
    while(!done) {

        // events
        gestionEvent(done, windowManager); 

        // ============ RENDERING CODE =========== //

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // glBindVertexArray(vao);

        // liens avec shaders (variables uniformes)

        // bind textures

        // gl draw arrays

        // debind 

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    // delete buffers arrays et cie 

    return EXIT_SUCCESS;
}
