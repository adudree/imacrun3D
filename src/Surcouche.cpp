#include "Surcouche.hpp"

// IMPORTANT : les fonctions dans ce fichier sont à trier //

void createTiles(Game& game, std::vector<std::unique_ptr<Tile>>& tiles, std::vector<std::unique_ptr<Wall>>& walls)
{
    std::vector<GLuint> texturesMap(2); // 2 = nb textures

    std::unique_ptr<glimac::Image> simple = glimac::loadImage("assets/textures/cardinale.jpg");
    std::unique_ptr<glimac::Image> hole   = glimac::loadImage("assets/textures/hole.png");

    Map map = game.getMap();

    createTexture(texturesMap[0], simple);
    createTexture(texturesMap[1], hole);

    for (int i = 0; i < map.getDimensions()[0]; i++) {
        for (int j = 0; j < map.getDimensions()[1]; j++) {
            switch (map.getTypeTile(glm::vec2(i, j))) {
            case 'P':
                game.setPlayerPosition(glm::vec2(i * tilesW, j * tilesL));
                tiles.push_back(std::make_unique<Tile>(i * tilesW, j * tilesL, texturesMap[0]));
                break;

            case 'E':
            case 'S':
                tiles.push_back(std::make_unique<Tile>(i * tilesW, j * tilesL, texturesMap[0]));
                break;

            case 'H':
                tiles.push_back(std::make_unique<Hole>(i * tilesW, j * tilesL, texturesMap[1]));
                break;

            case 'W':
                if ((j+i) % 2 == 0) {
                    walls.push_back(std::make_unique<Wall>(i * tilesW, j * tilesL, "assets/models/wall/asteroide.obj"));
                }
                else {
                    walls.push_back(std::make_unique<Wall>(i * tilesW, j * tilesL, "assets/models/wall/asteroide2.obj"));
                }
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