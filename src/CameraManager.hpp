#include <SDL2/SDL.h>
#include "CameraFirstPerson.hpp"
#include "CameraThirdPerson.hpp"

class CameraManager {
private:
    CameraThirdPerson cameraThirdPerson;
    CameraFirstPerson cameraFirstPerson;
    ICamera*          camera         = &cameraThirdPerson;
    bool              isCameraLocked = false;

public:
    CameraFirstPerson& getCameraFirstPerson() { return cameraFirstPerson; };
    ICamera&           getCamera() { return *camera; };
    void               onEvent(const SDL_Event& e);
    void               turnCameras(float variation);
};
