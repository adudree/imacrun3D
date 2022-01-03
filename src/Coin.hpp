#pragma once

#include <glimac/glm.hpp>
#include <vector>
#include "Map.hpp"
#include "Model.hpp"

class Coin {
private:
    int       m_point;
    bool      m_isCollected = false;
    glm::vec3 m_position    = glm::vec3(0);

    float           m_rotateFloat = 0;
    Model           m_model;
    glimac::Program m_program = glimac::loadProgram("assets/shaders/Model.vs.glsl", "assets/shaders/Model.fs.glsl");

public:
    explicit Coin(const glm::vec3& pos, const int point)
        : m_point(point), m_position(pos), m_model("assets/models/coin/coin.obj") {}
    Coin(const Coin&) = default;
    Coin& operator=(const Coin&) = default;
    ~Coin()                      = default;

    // Setter
    inline void setIsCollected(const bool& isCollected) { m_isCollected = isCollected; }

    // Getter
    inline bool      getIsCollected() const { return m_isCollected; }
    inline glm::vec3 getPosition() const { return m_position; }
    inline int       getNbPoint() const { return m_point; }

    bool isCollision(const glm::vec3& posPlayer);

    void        draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix);
    inline void resetRotateFloat() { m_rotateFloat = 0.; };
};

void createCoins(const Map& map, std::vector<std::unique_ptr<Coin>>& coins);
void updateCoins(const glm::vec3& pos, std::vector<std::unique_ptr<Coin>>& coins);
