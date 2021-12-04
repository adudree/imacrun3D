#include "glimac/Surcouche.hpp"

// IMPORTANT : les fonctions dans ce fichier sont à trier //


namespace glimac {

void createTiles(const Map &map, std::vector<Tile> &tiles, const GLfloat &w, const GLfloat &h)
{
    std::vector<GLuint> texturesMap(2); // 2 = nb textures 

    std::unique_ptr<Image> simple = loadImage("./src/assets/textures/cardinale.jpg");
    std::unique_ptr<Image> hole = loadImage("./src/assets/textures/hole.png");

    createTexture(texturesMap[0], simple);
    createTexture(texturesMap[1], hole);

    for (int i = 0; i < map.getDimensions()[0] ; i++)
    {
        for (int j = 0; j < map.getDimensions()[1]; j++)
        {
            switch (map.getTypeTile(i, j))
            {
            case 'P':
                // initial player position on simple tile
                tiles.push_back(Tile(i*w, j*h, w, h, texturesMap[0]));
                break;

            case 'S':
                tiles.push_back(Tile(i*w, j*h, w, h, texturesMap[0]));
                break;

            case 'H':
                tiles.push_back(Hole(i*w, j*h, w, h, texturesMap[1]));
                break;

            case 'W':
                // créer une tuile "wall" [A FAIRE]
                break;

            case 'A':
                // créer une tuile "arch" [A FAIRE]
                break;

            case 'L':
                // créer une tuile "leftHole" [A FAIRE]
                break;

            case 'R':
                // créer une tuile "rightHole" [A FAIRE]
                break;

            default:
                break;
            }
        }
    }


}

}