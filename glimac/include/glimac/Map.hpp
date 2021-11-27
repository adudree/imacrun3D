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
        std::vector<std::vector<char>> coords;
        int nbLines;
        int nbCols; 
    
    public :
        Map(std::string &filename);
        ~Map() = default;

        inline glm::vec2 getDimensions() {return glm::vec2(nbLines, nbCols);};
        
};


}