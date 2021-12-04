#include "glimac/Event.hpp"

namespace glimac {
void gestionEvent(bool &done, SDLWindowManager &windowManager) 
{
    SDL_Event e;
    while(windowManager.pollEvent(e)) {
        if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_x) {
            done = true;
        }
    }

}

}