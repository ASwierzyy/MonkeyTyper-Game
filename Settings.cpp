
#include "Settings.h"
#include <iostream>

Settings::Settings(float width, float height)
        : selectedItemIndex(0), currentFontIndex(0),currentWordRangeIndex(1) {
    if (!font.loadFromFile("../assets/fonts/CarterOne-Regular.ttf")) {
        std::cerr << "Error, font not found" << std::endl;
        return;
    }

    if (!loadFonts()) {
        std::cerr << "Error loading fonts" << std::endl;
        return;
    }

    sizeOptions = {16, 18, 20, 24, 26,};
    wordRangeOptions = {"Short", "Medium", "Long"};

    initializeMenuItems();
}

bool Settings::loadFonts() {
    std::vector<std::string> fontFiles = {"../assets/fonts/CarterOne-Regular.ttf", "../assets/fonts/arial.ttf", "../assets/fonts/Danfo-Regular-VariableFont_ELSH.ttf","../assets/fonts/EduTASBeginner-VariableFont_wght.ttf","../assets/fonts/Jacquard12-Regular.ttf","../assets/fonts/Jaro-Regular-VariableFont_opsz.ttf","../assets/fonts/Lato-Regular.ttf"};
    fontOptions = {"Font", "Font", "Font","Font","Font","Font","Font"};

    for (const auto &file : fontFiles) {
        sf::Font font;
        if (!font.loadFromFile(file)) {
            std::cerr << "Error loading font: " << file << std::endl;
            return false;
        }
        fontsVec.push_back(font);
    }
    return true;
}

void Settings::initializeMenuItems() {
    sf::Text fontOption;
    fontOption.setFont(font);
    fontOption.setFillColor(sf::Color::White);
    fontOption.setString("Font");
    fontOption.setPosition(sf::Vector2f(350, 150));
    menuItems.push_back(fontOption);

    currentSizeIndex = 4;
    sf::Text sizeOption;
    sizeOption.setFont(font);
    sizeOption.setFillColor(sf::Color::White);
    sizeOption.setString("Size");
    sizeOption.setCharacterSize(sizeOptions[currentSizeIndex]);
    sizeOption.setPosition(sf::Vector2f(350, 250));
    menuItems.push_back(sizeOption);


    sf::Text wordRangeOption;
    wordRangeOption.setFont(font);
    wordRangeOption.setFillColor(sf::Color::White);
    wordRangeOption.setString("Word Range");
    wordRangeOption.setPosition(sf::Vector2f(250, 350));
    menuItems.push_back(wordRangeOption);


    sf::Text backOption;
    backOption.setFont(font);
    backOption.setFillColor(sf::Color::White);
    backOption.setString("Save & Back");
    backOption.setPosition(sf::Vector2f(300, 450));
    menuItems.push_back(backOption);

    sf::Text leftArrow;
    leftArrow.setFont(font);
    leftArrow.setFillColor(sf::Color::White);
    leftArrow.setString("<");
    leftArrow.setPosition(sf::Vector2f(300, 150));
    arrows.push_back(leftArrow);

    sf::Text rightArrow;
    rightArrow.setFont(font);
    rightArrow.setFillColor(sf::Color::White);
    rightArrow.setString(">");
    rightArrow.setPosition(sf::Vector2f(450, 150));
    arrows.push_back(rightArrow);

    sf::Text leftArrowSize;
    leftArrowSize.setFont(font);
    leftArrowSize.setFillColor(sf::Color::White);
    leftArrowSize.setString("<");
    leftArrowSize.setPosition(sf::Vector2f(300, 250));
    arrows.push_back(leftArrowSize);

    sf::Text rightArrowSize;
    rightArrowSize.setFont(font);
    rightArrowSize.setFillColor(sf::Color::White);
    rightArrowSize.setString(">");
    rightArrowSize.setPosition(sf::Vector2f(450, 250));
    arrows.push_back(rightArrowSize);


    sf::Text leftArrowWordRange;
    leftArrowWordRange.setFont(font);
    leftArrowWordRange.setFillColor(sf::Color::White);
    leftArrowWordRange.setString("<");
    leftArrowWordRange.setPosition(sf::Vector2f(225, 350));
    arrows.push_back(leftArrowWordRange);

    sf::Text rightArrowWordRange;
    rightArrowWordRange.setFont(font);
    rightArrowWordRange.setFillColor(sf::Color::White);
    rightArrowWordRange.setString(">");
    rightArrowWordRange.setPosition(sf::Vector2f(575, 350));
    arrows.push_back(rightArrowWordRange);
}

void Settings::draw(sf::RenderWindow &window) {
    for (const auto &item : menuItems) {
        window.draw(item);
    }
    for (const auto &arrow : arrows) {
        window.draw(arrow);
    }
}


int Settings::getSelectedItemIndex() const {
    return selectedItemIndex;
}

bool Settings::isMouseOverOption(const sf::Vector2f &mousePos) const {
    for (const auto &item : menuItems) {
        if (item.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}

void Settings::handleArrowClick(const sf::Vector2f &mousePos) {
    if (arrows[0].getGlobalBounds().contains(mousePos)) {
        // Left arrow clicked
        currentFontIndex = (currentFontIndex - 1 + fontOptions.size()) % fontOptions.size();
        updateFontDisplay();
    } else if (arrows[1].getGlobalBounds().contains(mousePos)) {
        // Right arrow clicked
        currentFontIndex = (currentFontIndex + 1) % fontOptions.size();
        updateFontDisplay();
    }else if (arrows[2].getGlobalBounds().contains(mousePos)) {
        // Left arrow for size clicked
        currentSizeIndex = (currentSizeIndex - 1 + sizeOptions.size()) % sizeOptions.size();
        updateSizeDisplay();
    } else if (arrows[3].getGlobalBounds().contains(mousePos)) {
        // Right arrow for size clicked
        currentSizeIndex = (currentSizeIndex + 1) % sizeOptions.size();
        updateSizeDisplay();
    }else if (arrows[4].getGlobalBounds().contains(mousePos)) {
        // Left arrow for word range clicked
        currentWordRangeIndex = (currentWordRangeIndex - 1 + wordRangeOptions.size()) % wordRangeOptions.size();
        updateWordRangeDisplay();
    } else if (arrows[5].getGlobalBounds().contains(mousePos)) {
        // Right arrow for word range clicked
        currentWordRangeIndex = (currentWordRangeIndex + 1) % wordRangeOptions.size();
        updateWordRangeDisplay();
    }
}


void Settings::handleMouseMove(const sf::Vector2f &mousePos) {
    for (auto &arrow : arrows) {
        if (arrow.getGlobalBounds().contains(mousePos)) {
            arrow.setFillColor(sf::Color::Red);
        } else {
            arrow.setFillColor(sf::Color::White);
        }
    }

    if (menuItems.back().getGlobalBounds().contains(mousePos)) {
        menuItems.back().setFillColor(sf::Color::Red);
        selectedItemIndex = 2;
    } else {
        menuItems.back().setFillColor(sf::Color::White);
        selectedItemIndex = 0;
    }
}


void Settings::updateFontDisplay() {
    menuItems[0].setFont(fontsVec[currentFontIndex]);
    menuItems[0].setString(fontOptions[currentFontIndex]);
}

void Settings::updateSizeDisplay() {
    menuItems[1].setCharacterSize(sizeOptions[currentSizeIndex]);
}
void Settings::updateWordRangeDisplay() {
    menuItems[2].setString("Word Range: " + wordRangeOptions[currentWordRangeIndex]);
}

const sf::Font& Settings::getCurrentFont() const {
    return fontsVec[currentFontIndex];
}

int Settings::getCurrentCharacterSize() const {
    return sizeOptions[currentSizeIndex];
}

std::string Settings::getSelectedWordRange() const {
    return wordRangeOptions[currentWordRangeIndex];
}