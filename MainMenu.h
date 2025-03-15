

#ifndef MAINMENU_H
#define MAINMENU_H



#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class MainMenu {
public:
    MainMenu(float width, float height);
    void draw(sf::RenderWindow &window);
    int getSelectedItemIndex() const;
    bool isMouseOver(const sf::Vector2f &mousePos);

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    sf::Texture backgroundTexture;
    sf::Texture backgroundTexture2;
    sf::Sprite backgroundSprite;
    sf::Sprite backgroundSprite2;
    sf::Text titleText;
};




#endif //MAINMENU_H
