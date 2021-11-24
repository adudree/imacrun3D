#include "glimac/Map.hpp"

namespace glimac {

std::vector<std::vector<char>> readMap(std::string filename)
{ 
    std::ifstream fichier (filename,  std::ios::in); 
    std::string ligne;

    std::vector<std::vector<char>> tab; 

    int j = 0;
    while (!fichier.eof())
    { 
        getline(fichier,ligne); 

        if (ligne.find("#")) {
                std::vector<char> v; 
            for(int i = 0; i < ligne.length();i++) 
            { 
                v.push_back(ligne[i]);
                
            } 
            tab.push_back(v);
            j++;
        }
    } 
    return tab;
}
}