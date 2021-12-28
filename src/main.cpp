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
#include "GameRendering.hpp"

using namespace glimac;

int main()
{
    // ============ INITIALIZATION =========== //

    // window

    GLint            WIDTH  = 800;
    GLint            HEIGHT = 800;
    SDLWindowManager windowManager(WIDTH, HEIGHT, "IMAC RUN 3D");

    glEnable(GL_DEPTH_TEST);
    
    // mouse & menu

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

    // Game & gameRenderer 

    Game game;
    GameRendering gameRenderer(game); 

    game.initGame();
    //Camera

    CameraThirdPerson cameraThirdPerson;
    CameraFirstPerson cameraFirstPerson;
    ICamera*          camera         = &cameraFirstPerson;
    bool              isCameraLocked = false;


    // ================= LOOP ================= //

    bool done = false;
    while (!done) {

        // ============ RENDERING CODE =========== //

        game.runGame();
        gameRenderer.mainRendering(game, camera);

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
