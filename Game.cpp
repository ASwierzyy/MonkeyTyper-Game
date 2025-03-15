#include "Game.h"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

#define DELETE_KEY 8

Game::Game()
        : window(sf::VideoMode(800, 600), "Test", sf::Style::Default, sf::ContextSettings(0, 0, 8)),
          scoreNum(0), livesNum(3), interval(1.5f), nextWord(0),wordsSpeed(0.01f), isGameOver(false),
          menu(window.getSize().x, window.getSize().y),settings(window.getSize().x, window.getSize().y), state(MENU), scoreboard() {

    if (!font.loadFromFile("../assets/fonts/CarterOne-Regular.ttf")) {
        std::cerr << "Error, font not found" << std::endl;
        return;
    }


    currentFont = font;
    currentCharacterSize = 20;

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

    if (!GameOverTexture.loadFromFile("../assets/Images/GameOver.jpg")) {
        std::cerr << "Error, image not found" << std::endl;
        return;
    }
    GameOverSprite.setTexture(GameOverTexture);
    GameOverSprite.setPosition(-200,0);


    scoreText.setFont(font);
    scoreText.setPosition(650, 550);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setString("Score: " + std::to_string(scoreNum));


    livesText.setFont(font);
    livesText.setPosition(500, 550);
    livesText.setFillColor(sf::Color::Red);
    livesText.setString("Lives: " +std::to_string(livesNum));

    inputDisplayed.setFont(font);
    inputDisplayed.setFillColor(sf::Color::White);
    inputDisplayed.setPosition(50.f, 550.f);

    overlay.setFont(currentFont);
    overlay.setFillColor(sf::Color::Green);
    overlay.setCharacterSize(currentCharacterSize);


    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(250, 100);

    nicknamePrompt.setFont(font);
    nicknamePrompt.setString("Enter your nickname:");
    nicknamePrompt.setCharacterSize(30);
    nicknamePrompt.setFillColor(sf::Color::White);
    nicknamePrompt.setPosition(250, 250);

    nicknameInput.setFont(font);
    nicknameInput.setCharacterSize(30);
    nicknameInput.setFillColor(sf::Color::White);
    nicknameInput.setPosition(350, 300);

    saveButtonText.setFont(font);
    saveButtonText.setString("Save");
    saveButtonText.setCharacterSize(30);
    saveButtonText.setFillColor(sf::Color::White);
    saveButtonText.setPosition(375, 410);


    warningSign.setFont(font);
    warningSign.setString("Please enter your nickname");
    warningSign.setCharacterSize(30);
    warningSign.setFillColor(sf::Color::Red);
    warningSign.setPosition(200, 450);


    scoreboard.loadScores("../assets/TextFiles/scores.txt");


}

void Game::run() {
    while (window.isOpen()) {
        eventsHandling();
        update();
        renderWindow();
    }
}

void Game::eventsHandling() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P && event.key.shift) {
                state = PLAYING;
            }
            if (event.key.code == sf::Keyboard::S && event.key.shift) {
                state = SETTINGS;
            }
            if (event.key.code == sf::Keyboard::B && event.key.shift) {
                state = SCOREBOARD;
            }
            if (event.key.code == sf::Keyboard::E && event.key.shift) {
                window.close();
            }
        }
        if (state == MENU) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (menu.isMouseOver(mousePos)) {
                        int selectedItem = menu.getSelectedItemIndex();
                        if (selectedItem == 0) {
                            state = PLAYING;
                            loadWordsFromSettings();
                            shuffleWords();
                            clock.restart();
                            isGameOver = false;
                            scoreNum = 0;
                            livesNum = 3;
                            livesText.setString("Lives: "+std::to_string(livesNum));
                            scoreText.setString("Score: "+std::to_string(scoreNum));
                            content = "";
                            letter = "";
                            overlay.setString(letter);
                            inputDisplayed.setString(content);
                            words.clear();
                            nextWord = 0;
                            scoreText.setPosition(650, 550);
                            nicknameInput.setString("");
                            wordsSpeed = 0.01f;
                            interval = 1.5f;
                        } else if (selectedItem == 1) {
                            state = SETTINGS;
                        }else if (selectedItem == 2) {
                            state = SCOREBOARD;
                        }else if (selectedItem == 3) {
                            window.close();
                        }
                    }
                }
            } else if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                menu.isMouseOver(mousePos);
            }
        }
        else if (state == SETTINGS) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    settings.handleArrowClick(mousePos);
                    if (settings.isMouseOverOption(mousePos)) {
                        int selectedItem = settings.getSelectedItemIndex();
                        if (selectedItem == 2) {
                            currentFont = settings.getCurrentFont();
                            currentCharacterSize = settings.getCurrentCharacterSize();
                            state = MENU;
                        }
                    }
                }
            } else if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                settings.handleMouseMove(mousePos);
            }
        }
        else if (state == PLAYING) {
            if (!isGameOver && event.type == sf::Event::TextEntered && event.text.unicode < 128) {
                handleTextInput(event.text);
            }
        }else if (state == GAME_OVER) {
            if (event.type == sf::Event::TextEntered && event.text.unicode < 128) {
                char typedChar = static_cast<char>(event.text.unicode);
                if (typedChar != DELETE_KEY) {
                    nickname += typedChar;
                    nicknameInput.setString(nickname);
                } else {
                    if (!nickname.empty()) {
                        nickname.pop_back();
                        nicknameInput.setString(nickname);
                    }
                }
            }
            else if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                if (saveButtonText.getGlobalBounds().contains(mousePos)) {
                    saveButtonText.setFillColor(sf::Color::Red);
                } else {
                    saveButtonText.setFillColor(sf::Color::White);
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (saveButtonText.getGlobalBounds().contains(mousePos)) {
                        if (!nickname.empty()){
                            saveScore();
                            state = MENU;
                        }
                    }
                }
            }
        }else if (state == SCOREBOARD) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                state = MENU;
            }
        }
    }
}

void Game::update() {
    if (state == PLAYING && !isGameOver) {
        if (clock.getElapsedTime().asSeconds() >= interval && !wordQueue.empty() ) {
            addNewWord();
            clock.restart();
        }
        checkWordMissed();
        if (!words.empty()) {
            words.front().setColor(sf::Color::Yellow);
        }
    }
}

void Game::renderWindow() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(backgroundSprite2);
    if (state == MENU) {
        menu.draw(window);
    }else if (state == SETTINGS) {
        settings.draw(window);
    }else if (state == PLAYING) {
        if (isGameOver) {
            state = GAME_OVER;
        } else {
            window.draw(backgroundSprite);
            window.draw(backgroundSprite2);
            for (auto& word : words) {
                word.setSpeed(wordsSpeed);
                word.move();
                word.drawWord(window);
            }
            if (!words.empty()) {
                auto overlayPos = words.front().getPosition();
                overlayPos.x += words.front().getSpeed();
                overlay.setPosition(overlayPos);
            }
            overlay.setFont(currentFont);
            overlay.setCharacterSize(currentCharacterSize);
            window.draw(inputDisplayed);
            window.draw(overlay);
            window.draw(scoreText);
            window.draw(livesText);
        }
    } else if (state == GAME_OVER) {
        window.draw(GameOverSprite);
        window.draw(gameOverText);
        scoreText.setPosition(350, 200);
        window.draw(scoreText);
        window.draw(gameOverText);
        window.draw(scoreText);
        window.draw(nicknamePrompt);
        window.draw(nicknameInput);
        window.draw(saveButtonText);
        if(nickname.empty()) {
            window.draw(warningSign);
        }
    }else if (state == SCOREBOARD) {
        scoreboard.draw(window);
    }
    window.display();
}

void Game::handleTextInput(sf::Event::TextEvent textEvent) {
    char typedChar = static_cast<char>(textEvent.unicode);
    if (typedChar != DELETE_KEY) {
        content += typedChar;
        inputDisplayed.setString(content);
        checkWordMatch();
    } else {
        if (!content.empty() && !letter.empty()) {
            content.pop_back();
            letter.pop_back();
            inputDisplayed.setString(content);
            overlay.setString(letter);
        }
    }
}

void Game::checkWordMatch() {
    if (letter.length() <= content.length()) {
        for (int i = content.length() - 1; i < words.front().getLength(); i++) {
            if (content[i] == words.front().getString()[i]) {
                letter = content;
                overlay.setString(letter);
                if (letter == words.front().getString()) {
                    content = "";
                    letter = "";
                    overlay.setString(letter);
                    inputDisplayed.setString(content);
                    words.pop_front();
                    scoreNum++;
                    scoreText.setString("Score: " + std::to_string(scoreNum));
                    updateWordSpeed();
                }
                break;
            } else if (content[i] != words.front().getString()[i]) {
                content = "";
                letter = "";
                overlay.setString(letter);
                inputDisplayed.setString(content);
            }
        }
    }
}

void Game::checkWordMissed() {
    if (!words.empty() && words.front().getPosition().x > window.getSize().x) {
        words.pop_front();
        content = "";
        letter = "";
        overlay.setString(letter);
        inputDisplayed.setString(content);
        if (livesNum > 0) {
            livesNum--;
            livesText.setString("Lives: " +std::to_string(livesNum));
            if (livesNum == 0) {
                isGameOver = true;
            }
        }
    }
}

void Game::loadWordsFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error, file not found" << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
        wordQueue.push_back(word);
    }
    file.close();
}

void Game::shuffleWords() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(wordQueue.begin(), wordQueue.end(),g);
}

bool Game::ifColliding(const Word& newWord) const {
    for (const auto& word : words) {
        if (word.getGlobalBounds().intersects(newWord.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}


void Game::addNewWord() {
    if (nextWord < wordQueue.size()) {
        Word newWord(wordQueue[nextWord], currentFont, currentCharacterSize, wordsSpeed);
        do {
            newWord.setPosition();
        } while (ifColliding(newWord));
        words.push_back(newWord);
        nextWord++;
    }
}

void Game::updateWordSpeed() {
    if (scoreNum >= 5 && wordsSpeed == 0.01f) {
        interval = 1.25f;
        wordsSpeed = 0.012f;
        for (auto& word : words) {
            word.setSpeed(wordsSpeed);
        }
    } else if (scoreNum >= 10 && wordsSpeed == 0.012f) {
        wordsSpeed = 0.014f;
        interval = 1.0f;
        for (auto& word : words) {
            word.setSpeed(wordsSpeed);
        }
    } else if (scoreNum >= 15 && wordsSpeed == 0.014f) {
        wordsSpeed = 0.016f;
        for (auto& word : words) {
            word.setSpeed(wordsSpeed);
        }
    }
}

void Game::saveScore() {
    scoreboard.addScore(nickname, scoreNum);
    scoreboard.saveScores("../assets/TextFiles/scores.txt");
    nickname = "";
}

void Game::loadWordsFromSettings() {
    std::string filename;
    std::string selectedRange = settings.getSelectedWordRange();

    if (selectedRange == "Short") {
        filename = "../assets/TextFiles/short.txt";
    } else if (selectedRange == "Long") {
        filename = "../assets/TextFiles/long.txt";
    } else filename = "../assets/TextFiles/medium.txt";
    wordQueue.clear();
    loadWordsFromFile(filename);

}