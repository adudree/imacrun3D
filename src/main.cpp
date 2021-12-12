#include <GL/glew.h>
#include <array>
#include <fstream>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "CameraFirstPerson.hpp"
#include "CameraThirdPerson.hpp"
#include "Map.hpp"
#include "Sphere.hpp"
#include "Surcouche.hpp"
#include "Tile.hpp"

using namespace glimac;

unsigned int loadCubemap(const std::array<const char*, 6>& texturesPaths)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (unsigned int i = 0; i < texturesPaths.size(); i++) {
        const auto image = glimac::loadImage(texturesPaths[i]);
        if (image) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
        }
        else {
            std::cout << "Cubemap tex failed to load at path: " << texturesPaths[i] << std::endl;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

int main()
{
    // ============ INITIALIZATION =========== //

    // window
    GLint            WIDTH  = 800;
    GLint            HEIGHT = 800;
    SDLWindowManager windowManager(WIDTH, HEIGHT, "IMAC RUN 3D");
    SDL_EnableKeyRepeat(1000, 10);

    // glew : mettre un catch try par ici
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    // program + shaders
    //
    Program program       = loadProgram("assets/shaders/3D.vs.glsl", "assets/shaders/tex3D.fs.glsl");
    Program skyboxProgram = loadProgram("assets/shaders/skybox.vs.glsl", "assets/shaders/skybox.fs.glsl");

    glEnable(GL_DEPTH_TEST);

    // ================ MATRIX ================ //
    program.use();
    GLint locMVPMatrix    = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint locMVMatrix     = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint locNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint locTexture      = glGetUniformLocation(program.getGLId(), "uTexture");

    glm::mat4 ProjMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;

    ProjMatrix = glm::perspective(70.f, float(WIDTH / HEIGHT), 0.1f, 100.0f);

    // =============== TEXTURES =============== //

    const unsigned int cubemapTexture = loadCubemap({"assets/CubeMap/bluecloud_rt.jpg",
                                                     "assets/CubeMap/bluecloud_lf.jpg",
                                                     "assets/CubeMap/bluecloud_up.jpg",
                                                     "assets/CubeMap/bluecloud_dn.jpg",
                                                     "assets/CubeMap/bluecloud_bk.jpg",
                                                     "assets/CubeMap/bluecloud_ft.jpg"});

    GLuint skyboxVAO;
    glGenVertexArrays(1, &skyboxVAO);
    glBindVertexArray(skyboxVAO);

    // ================= MAP ================== //

    std::string       fichierMap = "assets/maps/map1.imac";
    Map               myMap(fichierMap);
    std::vector<Tile> tiles;
    createTiles(myMap, tiles, 1, 1); // 1 & 3 w & h de chaque tuile

    // ================ CAMERA ================ //

    CameraThirdPerson cameraThirdPerson;
    CameraFirstPerson cameraFirstPerson;
    ICamera*          camera = &cameraThirdPerson;

    // ================= LOOP ================= //

    bool done = false;
    while (!done) {
        // ============ RENDERING CODE =========== //

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthMask(GL_FALSE);
        skyboxProgram.use();
        // ... set view and projection matrix
        glBindVertexArray(skyboxVAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);
        // ... draw rest of the scene

        // matrices et compagnie

        MVMatrix     = camera->computeMatrix({0.f, -0.3f, 0.f}); // TODO remplacer par la position du joueur
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        // valeurs uniformes

        program.use();
        glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniform1i(locTexture, 0);

        // dessin des tuiles
        for (size_t i = 0; i < tiles.size(); i++) {
            tiles[i].drawTile();
        }

        windowManager.swapBuffers();

        // Commandes de Event

        SDL_Event e;

        while (windowManager.pollEvent(e)) {
            switch (e.type) {
            case SDL_QUIT:
                done = true;
                break;

            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_x)
                    done = true;

                // ========= MOUVEMENT ========== //

                if (e.key.keysym.sym == SDLK_d) {
                }
                // si on est sur une case "virage" : on tourne
                // sinon : perso.posX ++;
                //player.avance_droite();

                if (e.key.keysym.sym == SDLK_q) {
                }
                // si on est sur une case "virage" : on tourne
                // sinon : perso.posX --;
                //player.avance_gauche();

                if (e.key.keysym.sym == SDLK_z) {
                }
                // le perso saute
                //player.avance_tout_droit();

                if (e.key.keysym.sym == SDLK_s) {
                }
                // le perso se baisse
                //player.avance_en_arriere();

                if (e.key.keysym.sym == SDLK_e) {
                }
                // le perso se baisse
                //player.avance_haut();

                if (e.key.keysym.sym == SDLK_f) {
                }
                // le perso se baisse
                //player.avance_bas();

                // =========== CAMERA =========== //

                if (e.key.keysym.sym == SDLK_c) {
                    if (camera == &cameraFirstPerson) {
                        camera = &cameraThirdPerson;
                    }
                    else {
                        camera = &cameraFirstPerson;
                    }
                }

                if (e.key.keysym.sym == SDLK_l) {
                }
                // lock vue caméra

                // Rotations
                if (e.key.keysym.sym == SDLK_LEFT) {
                    camera->tourne_gauche();
                }

                if (e.key.keysym.sym == SDLK_RIGHT) {
                    camera->tourne_droite();
                }

                if (e.key.keysym.sym == SDLK_UP) {
                    camera->tourne_haut();
                }

                if (e.key.keysym.sym == SDLK_DOWN) {
                    camera->tourne_bas();
                }

                // =========== MENU ============ //

                if (e.key.keysym.sym == SDLK_ESCAPE) {
                }
                // le menu s'ouvre

                break;

            default:
                break;
            }
        }
    }

    // delete buffers arrays et cie : trouver moyen de le faire izi
    // glDeleteBuffers(1, vbo);
    // glDeleteVertexArrays(1, vao);
    //glDeleteTextures(1, &texTest);
    glDeleteVertexArrays(1, &skyboxVAO);

    return EXIT_SUCCESS;
}
