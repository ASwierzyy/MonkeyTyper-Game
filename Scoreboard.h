

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Scoreboard {
public:
    struct ScoreEntry {
        std::string nickname;
        int score;
    };
    Scoreboard();

    void addScore(const std::string& nickname, int score);
    void saveScores(const std::string& filename);
    void loadScores(const std::string& filename);
    void draw(sf::RenderWindow& window);

private:

    sf::Font font;
    std::vector<ScoreEntry> scores;
    sf::Text title;
    std::vector<sf::Text> scoreTexts;
    void updateScoreTexts();
};

#endif // SCOREBOARD_H
