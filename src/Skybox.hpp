#pragma once

#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <vector>
#include "VAO.hpp"

struct SkyboxVertex {
    glm::vec3 position;
};

class Skybox {
private:
    unsigned int      m_cubemapTexture = loadCubemap({"assets/CubeMap/right.png",
                                                 "assets/CubeMap/left.png",
                                                 "assets/CubeMap/top.png",
                                                 "assets/CubeMap/bot.png",
                                                 "assets/CubeMap/front.png",
                                                 "assets/CubeMap/back.png"});
    glimac::Program   m_skyboxProgram  = glimac::loadProgram("assets/shaders/skybox.vs.glsl", "assets/shaders/skybox.fs.glsl");
    VAO<SkyboxVertex> m_skyboxVAO;
    VBO<SkyboxVertex> m_skyboxVBO;

    unsigned int loadCubemap(const std::array<const char*, 6>& texturesPaths);

public:
    Skybox();
    void render(const glm::mat4& ProjMatrix, const glm::mat4& MVMatrix);
};