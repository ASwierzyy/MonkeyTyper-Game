


#include "Scoreboard.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Scoreboard::Scoreboard() {
    if (!font.loadFromFile("../assets/fonts/CarterOne-Regular.ttf")) {
        std::cerr << "Error, font not found" << std::endl;
        return;
    }


    title.setFont(font);
    title.setString("Scoreboard");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(100, 50);
}




void Scoreboard::addScore(const std::string& nickname, int score) {
    scores.push_back({nickname, score});
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });

    if (scores.size() > 5) {
        scores.resize(5);
    }

    updateScoreTexts();
}

void Scoreboard::saveScores(const std::string& filename) {
    std::ofstream scoreFile(filename, std::ios::trunc);
    if (scoreFile.is_open()) {
        for (const auto& score : scores) {
            scoreFile << score.nickname << " " << score.score << std::endl;
        }
        scoreFile.close();
    } else {
        std::cerr << "Unable to open score file" << std::endl;
    }
}

void Scoreboard::loadScores(const std::string& filename) {
    scores.clear();
    std::ifstream scoreFile(filename);
    if (scoreFile.is_open()) {
        std::string nickname;
        int score;
        while (scoreFile >> nickname >> score) {
            scores.push_back({nickname, score});
        }
        scoreFile.close();
    } else {
        std::cerr << "Unable to open score file" << std::endl;
    }

    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });

    if (scores.size() > 5) {
        scores.resize(5);
    }

    updateScoreTexts();
}

void Scoreboard::updateScoreTexts() {
    scoreTexts.clear();
    for (size_t i = 0; i < scores.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(i + 1) + ". " + scores[i].nickname + " [ " + std::to_string(scores[i].score) + " ]" );
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setPosition(150, 150 + i * 60);
        scoreTexts.push_back(text);
    }
}

void Scoreboard::draw(sf::RenderWindow& window) {
    window.draw(title);
    for (const auto& text : scoreTexts) {
        window.draw(text);
    }
}