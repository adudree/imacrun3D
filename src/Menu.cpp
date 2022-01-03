#include "Menu.hpp"

Menu::Menu(const std::string &typeMenu)
{
    if (typeMenu == "pause") pauseMenu();
    if (typeMenu == "win") endMenu(true);
    if (typeMenu == "lose") endMenu(false);
}

void Menu::pauseMenu() 
{
    allTexts.clear();

    allTexts.push_back(std::make_unique<Text>("menu/reprendre", glm::vec2(0, 0.5)));
    allTexts.push_back(std::make_unique<Text>("menu/rejouer", glm::vec2(0, 0)));
    allTexts.push_back(std::make_unique<Text>("menu/quitter", glm::vec2(0, -0.5)));

    initTexts();
}


void Menu::endMenu(bool victory)
{
    if (victory)
        allTexts.push_back(std::make_unique<Text>("menu/victory", glm::vec2(0, 0.5)));
    else 
        allTexts.push_back(std::make_unique<Text>("menu/defeat", glm::vec2(0, 0.5)));
    
    allTexts.push_back(std::make_unique<Text>("menu/rejouer", glm::vec2(0, 0.5)));
    allTexts.push_back(std::make_unique<Text>("menu/quitter", glm::vec2(0, 0.5)));

    initTexts();

}

void Menu::initTexts()
{
    for (size_t i = 0; i < allTexts.size(); i++)
    {
        allTexts[i]->init();
    }
}

void Menu::draw()
{
    for (size_t i = 0; i < allTexts.size(); i++)
    {
        allTexts[i]->draw();
    }   
}

void Menu::clickDetection(glm::vec2 mousePosition)
{
    for (size_t i = 0; i < allTexts.size(); i++)
    {
        if (mousePosition.x >= allTexts[i]->getPosition().x - allTexts[i]->getDimensions().x/2 &&
            mousePosition.x <= allTexts[i]->getPosition().x + allTexts[i]->getDimensions().x/2 &&
            mousePosition.y >= allTexts[i]->getPosition().y - allTexts[i]->getDimensions().y/2 &&
            mousePosition.x <= allTexts[i]->getPosition().y + allTexts[i]->getDimensions().y/2)
            
            allTexts[i]->clickOnText();
    }
}