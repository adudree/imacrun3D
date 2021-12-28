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
#include "Coin.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "Model.hpp"
#include "Player.hpp"
#include "Skybox.hpp"
#include "Sphere.hpp"
#include "Surcouche.hpp"
#include "Tile.hpp"
#include "VAO.hpp"

using namespace glimac;

int main()
{
    // ============ INITIALIZATION =========== //

    // window

    GLint            WIDTH  = 800;
    GLint            HEIGHT = 800;
    SDLWindowManager windowManager(WIDTH, HEIGHT, "IMAC RUN 3D");

    glEnable(GL_DEPTH_TEST);
    
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

    // POUR LES TILES = GAMERENDERING
    Program program = loadProgram("assets/shaders/3D.vs.glsl", "assets/shaders/tex3D.fs.glsl");


    Game game;

    // ================ MATRIX ================ //

    // POUR LES TILES = GAMERENDERING
    program.use();
    GLint locMVPMatrix    = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint locMVMatrix     = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint locNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint locTexture      = glGetUniformLocation(program.getGLId(), "uTexture");

    glm::mat4 ProjMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;

    ProjMatrix = glm::perspective(70.f, float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);

    // ================ SKYBOX ================ //

    // POUR GAMERENDERING.CPP
    Skybox skybox;

    // ================= MAP ================== //

    Map map = game.getMap();

    // POUR GAMERENDERING.CPP
    std::vector<std::unique_ptr<Tile>> tiles;
    createTiles(game, tiles);

    // ================ CAMERA ================ //

    //POUR GAMERENDERING.CPP
    CameraThirdPerson cameraThirdPerson;
    CameraFirstPerson cameraFirstPerson;
    ICamera*          camera         = &cameraFirstPerson;
    bool              isCameraLocked = false;

    game.initGame();

    // ================= LOOP ================= //

    bool done = false;
    while (!done) {

        // ============ RENDERING CODE =========== //

        // matrices et compagnie

        //GAMERENDERING.CPP
        MVMatrix     = camera->computeMatrix(game.getPlayerPosition());
        MVMatrix     = glm::translate(MVMatrix, glm::vec3(0, 0.2f, 0));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        skybox.render(ProjMatrix, MVMatrix);
        game.draw(ProjMatrix, MVMatrix);

        /**************************************************************
         * ****** Test de coin pour Clémence ;) 
         * ************
         * *********************
        **************************************** * *******************/

        // valeurs uniformes
        // GAMERENDERING.CPP
        program.use();
        glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniform1i(locTexture, 0);

        // draw tiles

        for (size_t i = 0; i < tiles.size(); i++) {
            tiles[i]->drawTile();
        }


        game.runGame();

        // coin.draw();

        windowManager.swapBuffers();

        // events : SELON SI AFFICHAGE OU NON 

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

                if (game.m_isRunning) {
                    game.playerMoves(e);
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
                if (e.key.keysym.sym == SDLK_SPACE) {
                    // temporaire : reset la partie
                    game.initGame();
                }

                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    isMenuOpen      = !isMenuOpen;
                    game.m_isPaused = !game.m_isPaused;

                    game.pauseGame();

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
