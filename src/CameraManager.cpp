#include "CameraManager.hpp"

void CameraManager::onEvent(const SDL_Event& e)
{
    // =========== CAMERA =========== //
    switch (e.type) {
    case SDL_KEYDOWN:
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
        if (!isCameraLocked) {
            camera->variationPan(e.motion.xrel);
            camera->variationTilt(e.motion.yrel);
        }

        break;
    default:
        break;
    }
}