//
// Created by PC COMPUTER on 28.05.2024.
//

#ifndef SETTINGS_H
#define SETTINGS_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Settings {
public:
    Settings(float width, float height);
    void draw(sf::RenderWindow &window);
    int getSelectedItemIndex() const;
    bool isMouseOverOption(const sf::Vector2f &mousePos) const;
    void handleArrowClick(const sf::Vector2f &mousePos);
    void handleMouseMove(const sf::Vector2f &mousePos);
    const sf::Font& getCurrentFont() const;
    int getCurrentCharacterSize() const;
    std::string getSelectedWordRange() const;

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    std::vector<std::string> fontOptions;
    std::vector<int> sizeOptions;
    std::vector<sf::Text> arrows;
    std::vector<sf::Font> fontsVec;
    int currentFontIndex;
    int currentSizeIndex;
    int currentWordRangeIndex;
    std::vector<std::string> wordRangeOptions;


    void initializeMenuItems();
    void updateFontDisplay();
    void updateSizeDisplay();
    void updateWordRangeDisplay();
    bool loadFonts();
};
















#endif //SETTINGS_H
