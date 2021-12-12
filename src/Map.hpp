#pragma once

#include <fstream>
#include <glimac/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<char>> readMap(const std::string& filename);

class Map {
private:
    std::vector<std::vector<char>> m_coords;
    int                            m_nbLines;
    int                            m_nbCols;

public:
    Map(const std::string& filename);
    ~Map() = default;

    inline const glm::vec2 getDimensions() const { return glm::vec2(m_nbLines, m_nbCols); };
    inline char            getTypeTile(const int& i, const int& j) const { return m_coords[i][j]; };
};
