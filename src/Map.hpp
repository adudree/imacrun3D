#pragma once

#include <fstream>
#include <glimac/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

const float tilesW = 3;
const float tilesL = 3;

std::vector<std::vector<char>> readMap(const std::string& filename);

class Map {
private:
    int                            m_nbLines;
    int                            m_nbCols;
    std::vector<std::vector<char>> m_coords;
    std::string                    filename = "assets/maps/map3.imac";

public:
    Map();
    ~Map() = default;

    inline glm::vec2 getDimensions() const { return glm::vec2(m_nbLines, m_nbCols); };
    inline char      getTypeTile(glm::vec2 coord) const { return m_coords[coord[0]][coord[1]]; };
};
