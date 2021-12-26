#pragma once

#include <fstream>
#include <glimac/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

const float tilesW = 2;
const float tilesL = 4;

std::vector<std::vector<char>> readMap(const std::string& filename);

class Map {
private:
    std::vector<std::vector<char>> m_coords;
    int                            m_nbLines;
    int                            m_nbCols;
    std::string                    filename = "assets/maps/map1.imac";

public:
    Map();
    ~Map() = default;

    inline const glm::vec2 getDimensions() const { return glm::vec2(m_nbLines, m_nbCols); };
    inline char            getTypeTile(glm::vec2 coord) const { return m_coords[coord[0]][coord[1]]; };
};
