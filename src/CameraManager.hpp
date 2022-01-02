#include <SDL2/SDL.h>
#include "CameraFirstPerson.hpp"
#include "CameraThirdPerson.hpp"

class CameraManager {
private:
    CameraThirdPerson cameraThirdPerson;
    CameraFirstPerson cameraFirstPerson;
    ICamera*          camera         = &cameraFirstPerson;
    bool              isCameraLocked = false;

public:
    void               onEvent(const SDL_Event& e);
    ICamera&           getCamera() { return *camera; };
    CameraFirstPerson& getCameraFirstPerson() { return cameraFirstPerson; };
    void               turnCameras(float variation);
};
