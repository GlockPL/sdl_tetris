#pragma once

#include <fstream>
#include <string>
#include <filesystem>


class Score
{
private:
    std::string save_file_path = "./score.dat";
    int highScore = 0;
    int currentScore = 0;
    int level = 1;
public:   
    Score(/* args */);   
    ~Score();
    int getHighScore();
    int getCurrentScore();
    void setHighScore(int score);
    int calculateScore(int linesCleared);

};

Score::Score(/* args */)
{
    if(std::filesystem::exists(save_file_path)) {
        std::ifstream rf(save_file_path, std::ios::out | std::ios::binary);
        rf.read((char *) &highScore, sizeof(int));
    }
}


Score::~Score()
{
    std::ofstream wf(save_file_path, std::ios::out | std::ios::binary);
    wf.write((char *) &highScore, sizeof(int));
}

void Score::setHighScore(int score) {
    highScore = score > highScore ? score : highScore;
}

int Score::getHighScore() {
    return highScore;
}

int Score::getCurrentScore() {
    return currentScore;
}

int Score::calculateScore(int linesCleared) {
    switch (linesCleared)
    {
    case 1:
        currentScore += 100 * level;
        break;
    case 2:
        currentScore += 300 * level;
        break;
    case 3:
        currentScore += 500 * level;
        break;
    case 4:
        currentScore += 800 * level;
        break;
    
    default:
        break;
    }

    setHighScore(currentScore);

    return currentScore;
}