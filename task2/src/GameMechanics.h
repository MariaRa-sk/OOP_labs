#ifndef GAMEMECHANICS_H
#define GAMEMECHANICS_H

#include "GameConfig.h"

class GameMechanics {
private:
    std::vector<std::vector<bool>> oldField;
    std::vector<std::vector<bool>> currentField;
    size_t currentIteration = 0;

    std::vector<int> ruleBirth;
    std::vector<int> ruleSurvival;
    int fieldWidth;
    int fieldHeight;
    std::vector<std::pair<int, int>> aliveCells;

    size_t countNeighbors(size_t x, size_t y) const;
    bool isAlive(size_t x, size_t y) const;
    void initializeField();
public:
    explicit GameMechanics(GameConfig& config);
    const std::vector<std::vector<bool>>& getField() const;
    size_t getCurrentIteration() const;
    void step();
};

#endif