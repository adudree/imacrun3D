#include <iostream>
#include <string>
#include <SDL_ttf.h>
#include <SDL2/SDL.h>
#include <glimac/glm.hpp>
#include "VAO.hpp"
#include "VBO.hpp"
#include "IBO.hpp"
#include "Text.hpp"
#include "ShapeVertex.hpp"
#include "glimac/Program.hpp"

class Menu 
{
private: 
    glimac::Program m_program = glimac::loadProgram("assets/shaders/tex2D.vs.glsl", "assets/shaders/tex2D.fs.glsl");

    void pauseMenu();
    void header(); 
    void endMenu(bool victory);

    void initTexts();
    std::vector<std::unique_ptr<Text>> allTexts;

public: 
    Menu(const std::string &typeMenu);
    ~Menu() = default;

    void clickDetection(glm::vec2 mousePosition);
    void draw();
};