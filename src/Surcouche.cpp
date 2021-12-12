#include "Surcouche.hpp"
#include "Hole.hpp"

// IMPORTANT : les fonctions dans ce fichier sont à trier //

void createTiles(const Map& map, std::vector<Tile>& tiles, Player& p, const GLfloat& w, const GLfloat& h)
{
    std::vector<GLuint> texturesMap(2); // 2 = nb textures

    std::unique_ptr<glimac::Image> simple = glimac::loadImage("assets/textures/cardinale.jpg");
    std::unique_ptr<glimac::Image> hole   = glimac::loadImage("assets/textures/hole.png");

    createTexture(texturesMap[0], simple);
    createTexture(texturesMap[1], hole);

    for (int i = 0; i < map.getDimensions()[0]; i++) {
        for (int j = 0; j < map.getDimensions()[1]; j++) {
            switch (map.getTypeTile(i, j)) {
            case 'P':
                p.setPosition(glm::vec3(i * w, 0, j * h));
                tiles.push_back(Tile(i * w, j * h, w, h, texturesMap[0]));
                break;

            case 'S':
                tiles.push_back(Tile(i * w, j * h, w, h, texturesMap[0]));
                break;

            case 'H':
                tiles.push_back(Hole(i * w, j * h, w, h, texturesMap[1]));
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
