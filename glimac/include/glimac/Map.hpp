#pragma once

#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <glimac/glm.hpp>


namespace glimac {

std::vector<std::vector<char>> readMap(std::string &filename); 

class Map {
    private :
        std::vector<std::vector<char>> m_coords;
        int m_nbLines;
        int m_nbCols; 
    
    public :
        Map(std::string &filename);
        ~Map() = default;

        inline const glm::vec2 getDimensions() const {return glm::vec2(m_nbLines, m_nbCols);};
        inline char getTypeTile(const int &i, const int &j) const {return m_coords[i][j];};
        
};


}