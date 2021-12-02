#include "glimac/Surcouche.hpp"

// IMPORTANT : les fonctions dans ce fichier sont à trier //


namespace glimac {

void createTexture(GLuint &texture, std::unique_ptr<Image> &imagePointer)
{
    glGenTextures(1, &texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 
                0,
                GL_RGBA,
                imagePointer->getWidth(),
                imagePointer->getHeight(),
                0,
                GL_RGBA,
                GL_FLOAT,
                imagePointer->getPixels()
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void gestionEvent(bool &done, SDLWindowManager &windowManager) 
{
    SDL_Event e;
    while(windowManager.pollEvent(e)) {
        if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_x) {
            done = true;
        }
    }

}

// voir si on peut pas grouper avec fichier shader
void loadShader(Program &program, int &argc, char** &argv)
{
    std::string vs, fs; 
    if (argc == 3) {
        vs = std::string(argv[1]);
        fs = std::string(argv[2]);
        std::cout << "Shaders chargés." << std::endl;
    }
    else {
        std::cout << "Merci de charger les shaders :" <<  std::endl;
        std::cout << "Vertex shader : ";
        std::cin >> vs;
        std::cout << "Fragment shader :";
        std::cin >> fs;
    }

    program = loadProgram( "./src/shaders/" + vs, "./src/shaders/" + fs);
}

}