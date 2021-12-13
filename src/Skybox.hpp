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
    unsigned int      m_cubemapTexture = loadCubemap({"bin/assets/CubeMap/bluecloud_ft.jpg",
                                                 "bin/assets/CubeMap/bluecloud_bk.jpg",
                                                 "bin/assets/CubeMap/bluecloud_up.jpg",
                                                 "bin/assets/CubeMap/bluecloud_dn.jpg",
                                                 "bin/assets/CubeMap/bluecloud_rt.jpg",
                                                 "bin/assets/CubeMap/bluecloud_lf.jpg"});
    glimac::Program   m_skyboxProgram  = glimac::loadProgram("bin/assets/shaders/skybox.vs.glsl", "bin/assets/shaders/skybox.fs.glsl");
    VAO<SkyboxVertex> m_skyboxVAO;
    VBO<SkyboxVertex> m_skyboxVBO;

    unsigned int loadCubemap(const std::array<const char*, 6>& texturesPaths);

public:
    Skybox();
    void render(const glm::mat4& ProjMatrix, const glm::mat4& MVMatrix);
};