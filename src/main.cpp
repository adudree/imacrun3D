#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>
#include "Game.hpp"
#include "GameRendering.hpp"
#include "SDL2/SDL_ttf.h"

using namespace glimac;

int main()
{
    // ============ INITIALIZATION =========== //

    // Window

    GLint            WIDTH  = 800;
    GLint            HEIGHT = 800;
    SDLWindowManager windowManager(WIDTH, HEIGHT, "SPACE RUN 3D");

    glEnable(GL_DEPTH_TEST);

    // Menu

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

    // Game & CameRenderer

    Game          game;
    GameRendering gameRenderer(game);

    game.initGame();

    // ================= LOOP ================= //

    bool done = false;
    while (!done) {
        // ============ RENDERING CODE =========== //

        game.runGame();
        gameRenderer.mainRendering(game);

        windowManager.swapBuffers();

        SDL_Event e;
        while (windowManager.pollEvent(e)) {
            // ========= MOUVEMENT ========== //

            if (game.m_isRunning && !isMenuOpen) {
                game.onEvent(e);
            }

            switch (e.type) {
            case SDL_QUIT:
                done = true;
                break;

            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_x)
                    done = true;

                if (e.key.keysym.sym == SDLK_SPACE)
                    game.initGame();

                // ============= MENU ============== //
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
                break;

            default:
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}
