//
// Created by PC COMPUTER on 14.05.2024.
//

#ifndef WORD_H
#define WORD_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <deque>
#include <random>
#include <string>

class Word {
public:
    Word(std::string &wordContent, sf::Font &font, int charSize, float speed);

    void setPosition();
    auto setString(std::string &s);
    void move();
    void drawWord(sf::RenderWindow &window);
    sf::Vector2f getPosition();
    float getSpeed();
    int getLength();
    std::string getString();
    sf::FloatRect getGlobalBounds() const;
    bool ifColliding(const Word &other) const;
    void setSpeed(float newSpeed);
    void setColor(sf::Color);

private:
    sf::Text wordPrinted;
    std::string wordContent;
    sf::Font font;
    int charSize;
    float speed;
    sf::Color color = sf::Color::White;
    float delay;

    sf::Vector2f position;


};

#endif //WORD_H