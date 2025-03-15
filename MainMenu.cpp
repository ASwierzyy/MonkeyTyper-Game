
#include "MainMenu.h"

MainMenu::MainMenu(float width, float height) {
    if (!font.loadFromFile("../assets/fonts/CarterOne-Regular.ttf")) {
        std::cerr << "Error, font not found" << std::endl;
        return;
    }

    if (!backgroundTexture.loadFromFile("../assets/Images/EarthCiemne.jpg")) {
        std::cerr << "Error, image not found" << std::endl;
        return;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(255,0);

    if (!backgroundTexture2.loadFromFile("../assets/Images/stars.jpg")) {
        std::cerr << "Error, image not found" << std::endl;
        return;
    }
    backgroundSprite2.setTexture(backgroundTexture2);
    backgroundSprite2.setPosition(0,0);


    titleText.setFont(font);
    titleText.setString("Save the WORD");
    titleText.setCharacterSize(70);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(140,100);


    std::string items[] = {"Start", "Settings", "Scoreboard","Exit"};
    for (int i = 0; i < 4; i++) {
        sf::Text text;
        text.setFont(font);
        text.setFillColor(sf::Color::White);
        text.setString(items[i]);
        menuItems.push_back(text);
    }

    menuItems[0].setPosition(350,250);
    menuItems[1].setPosition(325,300);
    menuItems[2].setPosition(300,350);
    menuItems[3].setPosition(350, 400);


    selectedItemIndex = -1;
}

void MainMenu::draw(sf::RenderWindow &window) {
    window.draw(backgroundSprite);
    window.draw(backgroundSprite2);
    window.draw(titleText);
    for (const auto &item : menuItems) {
        window.draw(item);
    }
}

int MainMenu::getSelectedItemIndex() const {
    return selectedItemIndex;
}

bool MainMenu::isMouseOver(const sf::Vector2f &mousePos) {
    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (menuItems[i].getGlobalBounds().contains(mousePos)) {
            menuItems[i].setFillColor(sf::Color::Yellow);
            selectedItemIndex = i;
            return true;
        } else {
            menuItems[i].setFillColor(sf::Color::White);
        }
    }
    selectedItemIndex = -1;
    return false;
}