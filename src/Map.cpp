#include "Map.hpp"

Map::Map(const std::string &filename)
{ 
    std::ifstream fichier (filename,  std::ios::in); 
    std::string ligne;

    std::vector<std::vector<char>> tab; 

    int j = 0;

    while (getline(fichier,ligne))
    { 
        if (ligne.find("#")) {
            std::vector<char> v; 

            for(size_t i = 0; i < ligne.length();i++) 
            { 
                v.push_back(ligne[i]);
            } 

            tab.push_back(v);
            j++;
        }
    } 

    m_coords = tab;
    m_nbCols = ligne.length(); 
    m_nbLines = m_coords.size();
    fichier.close();


}
