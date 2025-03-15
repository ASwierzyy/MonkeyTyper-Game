
#ifndef GAME_H
#define GAME_H


#include <SFML/Graphics.hpp>
#include <deque>
#include "Word.h"
#include "MainMenu.h"
#include "Settings.h"
#include "Scoreboard.h"


class Game {
public:
    Game();
    void run();

private:
    enum GameState { MENU, PLAYING, SETTINGS, GAME_OVER, SCOREBOARD };
    GameState state;

    void eventsHandling();
    void update();
    void renderWindow();
    void handleTextInput(sf::Event::TextEvent textEvent);
    void checkWordMatch();
    void checkWordMissed();
    void loadWordsFromFile(const std::string &filename);
    void shuffleWords();
    void addNewWord();
    bool ifColliding(const Word &other) const;
    void saveScore();
    void updateWordSpeed();
    void loadWordsFromSettings();




    sf::RenderWindow window;
    sf::Font font;
    sf::Font currentFont;
    int currentCharacterSize;
    float wordsSpeed;
    std::deque<Word> words;
    std::vector<std::string> wordQueue;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text inputDisplayed;
    sf::Text overlay;
    sf::Text gameOverText;
    sf::Vector2f overlayPos;


    int scoreNum;
    int livesNum;
    std::string content;
    std::string letter;
    sf::Clock clock;
    float interval;
    int nextWord;
    bool isGameOver;


    MainMenu menu;
    sf::Texture backgroundTexture;
    sf::Texture backgroundTexture2;
    sf::Texture GameOverTexture;
    sf::Sprite backgroundSprite;
    sf::Sprite backgroundSprite2;
    sf::Sprite GameOverSprite;


    Settings settings;



    std::string nickname;
    sf::Text nicknamePrompt;
    sf::Text nicknameInput;
    sf::Text saveButtonText;
    sf::Text warningSign;

    Scoreboard scoreboard;
};



#endif //GAME_H
