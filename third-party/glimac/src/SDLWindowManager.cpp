#include "glimac/SDLWindowManager.hpp"
#include <GL/glew.h>
#include <iostream>

namespace glimac {

SDLWindowManager::SDLWindowManager(uint32_t width, uint32_t height, const char* title)
{
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Can't init SDL: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!m_window) {
        std::cerr << "SDL can't create window: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_CreateContext(m_window);

    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError) {
        std::cerr << "Can't init glew: " << glewGetErrorString(glewInitError) << std::endl;
        return;
    }
}

SDLWindowManager::~SDLWindowManager()
{
    SDL_Quit();
}

bool SDLWindowManager::pollEvent(SDL_Event& e)
{
    return SDL_PollEvent(&e);
}

bool SDLWindowManager::isKeyPressed(SDL_Scancode key) const
{
    return SDL_GetKeyboardState(nullptr)[key];
}

// button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
bool SDLWindowManager::isMouseButtonPressed(uint32_t button) const
{
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
}

glm::ivec2 SDLWindowManager::getMousePosition() const
{
    glm::ivec2 mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    return mousePos;
}

void SDLWindowManager::swapBuffers()
{
    SDL_GL_SwapWindow(m_window);
}

float SDLWindowManager::getTime() const
{
    return 0.001f * SDL_GetTicks();
}

} // namespace glimac
