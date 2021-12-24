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
#include "Model.hpp"
#include "Player.hpp"
#include "Skybox.hpp"
#include "Sphere.hpp"
#include "Surcouche.hpp"
#include "Tile.hpp"
#include "VAO.hpp"
#include "Model.hpp"

using namespace glimac;

int main()
{
    // ============ INITIALIZATION =========== //

    // window
    GLint            WIDTH  = 800;
    GLint            HEIGHT = 800;
    SDLWindowManager windowManager(WIDTH, HEIGHT, "IMAC RUN 3D");

    // mouse

    const auto openMenu = [&]() {
        SDL_ShowCursor(SDL_ENABLE);
        SDL_SetWindowGrab(windowManager.getWindow(), SDL_FALSE);
    };

    const auto closeMenu = [&]() {
        SDL_ShowCursor(SDL_DISABLE);
        SDL_SetWindowGrab(windowManager.getWindow(), SDL_TRUE);
    };
    bool isMenuOpen = false;
    closeMenu();

    // program + shaders

    Program program = loadProgram("assets/shaders/3D.vs.glsl", "assets/shaders/tex3D.fs.glsl");

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

    ProjMatrix = glm::perspective(70.f, float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);

    // ================ PLAYER ================ //

    GLuint                         texTemp;
    std::unique_ptr<glimac::Image> playerTemp = glimac::loadImage("assets/textures/cardinale.jpg");
    createTexture(texTemp, playerTemp);

    Player player(texTemp);

    Model testPlayer("assets/models/test2/StarSparrow.obj");
    //Model testPlayer("assets/models/test/backpack.obj");
    //test de load de shaders pour suzi
    //Program ModelProgram = loadProgram("assets/shaders/Model.vs.glsl", "assets/shaders/Model.fs.glsl");

    // ================ SKYBOX ================ //

    Skybox skybox;

    // ================= MAP ================== //

    std::string                        fichierMap = "assets/maps/map1.imac";
    Map                                myMap(fichierMap);
    std::vector<std::unique_ptr<Tile>> tiles;

    createTiles(myMap, tiles, player, 1, 1); // 1 & 3 w & h de chaque tuile

    // ================ CAMERA ================ //

    CameraThirdPerson cameraThirdPerson;
    CameraFirstPerson cameraFirstPerson;
    ICamera*          camera         = &cameraThirdPerson;
    bool              isCameraLocked = false;

    // ================= LOOP ================= //

    bool done = false;
    while (!done) {
        // ============ RENDERING CODE =========== //

        // matrices et compagnie

        MVMatrix     = camera->computeMatrix(player.getPosition());
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        skybox.render(ProjMatrix, MVMatrix);

        // valeurs uniformes

        program.use();
        glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniform1i(locTexture, 0);

        testPlayer.Draw(program);

        // draw tiles

        for (size_t i = 0; i < tiles.size(); i++) {
            tiles[i]->drawTile();
        }

        // tile detection
        char actTile = player.tileDetection(myMap, 1, 1);
        player.tilesConditions(actTile);

        //  draw player

        player.draw();

        windowManager.swapBuffers();

        // player.moveForward(); // test
        

        // events

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
                    // si on est sur une case "virage" : on tourne
                    // sinon :
                    player.moveRight();
                }

                if (e.key.keysym.sym == SDLK_q) {
                    // si on est sur une case "virage" : on tourne
                    // sinon :
                    player.moveLeft();
                }

                if (e.key.keysym.sym == SDLK_z) {
                    player.moveForward(); // pour le test; devra avancer tout seul après
                    // player.jump();
                }

                if (e.key.keysym.sym == SDLK_s) {
                    //player.squat();
                    player.fall();
                }

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
                    isCameraLocked = !isCameraLocked;
                }

                // =========== MENU ============ //

                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    isMenuOpen = !isMenuOpen;
                    if (isMenuOpen) {
                        openMenu();
                    }
                    else {
                        closeMenu();
                    }
                }
                // le menu s'ouvre

                break;

            case SDL_MOUSEWHEEL:
                if (camera == &cameraThirdPerson) {
                    if (e.wheel.y > 0) {
                        cameraThirdPerson.zoom_avant();
                    }

                    if (e.wheel.y < 0) {
                        cameraThirdPerson.zoom_arriere();
                    }
                }

                break;

            case SDL_MOUSEMOTION:
                if (!isCameraLocked && !isMenuOpen) {
                    camera->variationPan(e.motion.xrel);
                    camera->variationTilt(e.motion.yrel);
                }

                break;

            default:
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}
