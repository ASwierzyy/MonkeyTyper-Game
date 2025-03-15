


#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <deque>
#include <random>
#include <string>

#include "Word.h"

Word::Word(std::string &wordContent, sf::Font &font, int charSize, float speed) :
        wordContent(wordContent), speed(speed) ,delay(0) {

    wordPrinted.setString(wordContent);
    wordPrinted.setFont(font);
    wordPrinted.setCharacterSize(charSize);

}

void Word::setPosition() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(20, 500);

    float x = -100.0f;
    float y = static_cast<float>(distr(gen));

    position = sf::Vector2f(x, y);

    wordPrinted.setPosition(position);
}

auto Word::setString(std::string& s) {
    wordPrinted.setString(s);
}

void Word::move() {
    position.x += speed;
    wordPrinted.setPosition(position);
}

void Word::drawWord(sf::RenderWindow &window) {
    window.draw(wordPrinted);
}


sf::Vector2f Word::getPosition() {
    return wordPrinted.getPosition();
}

float Word::getSpeed(){
    return speed;
}

int Word::getLength(){
    return wordPrinted.getString().getSize();
}

std::string Word::getString(){
    return wordPrinted.getString();
}

void Word::setSpeed(float newSpeed) {
    speed = newSpeed;
}

sf::FloatRect Word::getGlobalBounds() const {
    return wordPrinted.getGlobalBounds();
}

bool Word::ifColliding(const Word& other) const {
    return wordPrinted.getGlobalBounds().intersects(other.getGlobalBounds());
}

void Word::setColor(sf::Color color) {
    wordPrinted.setFillColor(color);
}
