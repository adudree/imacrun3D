#include "glimac/Event.hpp"

namespace glimac {

void gestionEvent(bool &done, SDLWindowManager &windowManager) 
{
    SDL_Event e;
    
    while(windowManager.pollEvent(e)) {
        switch (e.type)
        {
            case SDL_QUIT:
                done = true;
                break;
            
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_x)
                    done = true;
                
                // ========= MOUVEMENT ========== //

                if (e.key.keysym.sym == SDLK_d)
                    // si on est sur une case "virage" : on tourne
                    // sinon : perso.posX ++;  

                if (e.key.keysym.sym == SDLK_q)
                    // si on est sur une case "virage" : on tourne
                    // sinon : perso.posX --;  

                if (e.key.keysym.sym == SDLK_z)
                    // le perso saute

                if (e.key.keysym.sym == SDLK_x)
                    // le perso se baisse


                // =========== CAMERA =========== //

                if (e.key.keysym.sym == SDLK_c)
                    // change vue caméra

                if (e.key.keysym.sym == SDLK_l)
                    // lock vue caméra


                // =========== MENU ============ //

                if (e.key.keysym.sym == SDLK_ESCAPE)
                    // le menu s'ouvre

                break;
            
            default:
                break;
        }

    }

}

}