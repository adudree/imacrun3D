#include "Tiles.hpp"

void createTiles(Game& game, std::vector<std::unique_ptr<Tile>>& tiles, std::vector<std::unique_ptr<Wall>>& walls, std::vector<std::unique_ptr<Arch>>& arch)
{
    std::vector<GLuint> texturesMap(2);

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
            case 'V':
            case 'S':
                tiles.push_back(std::make_unique<Tile>(i * tilesW, j * tilesL, texturesMap[0]));
                break;

            case 'H':
                tiles.push_back(std::make_unique<Hole>(i * tilesW, j * tilesL, texturesMap[1]));
                break;

            case 'W':
                if ((j + i) % 2 == 0) {
                    walls.push_back(std::make_unique<Wall>(i * tilesW, j * tilesL, "assets/models/wall/asteroide.obj"));
                }
                else {
                    walls.push_back(std::make_unique<Wall>(i * tilesW, j * tilesL, "assets/models/wall/asteroide2.obj"));
                }
                break;

            case 'A':
                tiles.push_back(std::make_unique<Tile>(i * tilesW, j * tilesL, texturesMap[0]));
                arch.push_back(std::make_unique<Arch>(i * tilesW, j * tilesL, "assets/models/wall/asteroideArch.obj"));
                break;

            default:
                break;
            }
        }
    }
}
