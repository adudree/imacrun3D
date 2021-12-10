#include "Event.hpp"

void gestionEvent(bool &done, glimac::SDLWindowManager &windowManager, Camera &camera) 
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
                    camera.avance_droite();

                if (e.key.keysym.sym == SDLK_q)
                    // si on est sur une case "virage" : on tourne
                    // sinon : perso.posX --;  
                    camera.avance_gauche();

                if (e.key.keysym.sym == SDLK_z)
                    // le perso saute
                    camera.avance_tout_droit();

                if (e.key.keysym.sym == SDLK_s)
                    // le perso se baisse
                    camera.avance_en_arriere();

                if (e.key.keysym.sym == SDLK_e)
                    // le perso se baisse
                    camera.avance_haut();

                if (e.key.keysym.sym == SDLK_f)
                    // le perso se baisse
                    camera.avance_bas();


                // =========== CAMERA =========== //

                if (e.key.keysym.sym == SDLK_c)
                    // change vue caméra

                if (e.key.keysym.sym == SDLK_l)
                    // lock vue caméra

                if (e.key.keysym.sym == SDLK_r){
                    // Retour au centre de la map
                    camera.reinitialise_position();
                }
                
                    // Rotations
                if (e.key.keysym.sym == SDLK_LEFT){
                    camera.tourne_gauche();
                } 

                if (e.key.keysym.sym == SDLK_RIGHT){
                    camera.tourne_droite();
                } 

                if (e.key.keysym.sym == SDLK_UP){
                    camera.tourne_haut();
                } 

                if (e.key.keysym.sym == SDLK_DOWN){
                    camera.tourne_bas();
                } 


                // =========== MENU ============ //

                if (e.key.keysym.sym == SDLK_ESCAPE)
                    // le menu s'ouvre

                break;
            
            default:
                break;
        }

    }

}
