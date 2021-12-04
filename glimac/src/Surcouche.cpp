#include "glimac/Surcouche.hpp"

// IMPORTANT : les fonctions dans ce fichier sont à trier //


namespace glimac {

void createTexture(GLuint &texture, std::unique_ptr<Image> &imagePointer)
{
    glGenTextures(1, &texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 
                0,
                GL_RGBA,
                imagePointer->getWidth(),
                imagePointer->getHeight(),
                0,
                GL_RGBA,
                GL_FLOAT,
                imagePointer->getPixels()
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}



void createTiles(const Map &map, std::vector<Tile> &tiles, const GLfloat &w, const GLfloat &h)
{
    std::cout << map.getDimensions()[1] << std::endl;
    for (int i = 0; i < map.getDimensions()[0] ; i++)
    {
        for (int j = 0; j < map.getDimensions()[1]; j++)
        {
            switch (map.getTypeTile(i, j))
            {
            case 'P':
                // position initiale du player on simple tile
                tiles.push_back(Tile(i*w, j*h, w, h));
                break;

            case 'W':
                // créer une tuile "wall" [A FAIRE]
                break;

            case 'S':
                // simple tile
                tiles.push_back(Tile(i*w, j*h, w, h));
                break;

            case 'A':
                // créer une tuile "arch" [A FAIRE]
                break;

            case 'H':
                // créer une tuile "hole" [A FAIRE]
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