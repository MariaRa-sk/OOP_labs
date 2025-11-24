#ifndef GAMEMECHANICS_H
#define GAMEMECHANICS_H

#include "GameConfig.h"

class GameMechanics {
private:
    GameConfig& config;
    std::vector<std::vector<bool>> oldField;
    std::vector<std::vector<bool>> currentField;
    size_t currentIteration = 0;

    size_t countNeighbors(size_t x, size_t y) const;
    bool isAlive(size_t x, size_t y) const;

public:
    explicit GameMechanics(GameConfig& config);
    void initializeField();

    const std::vector<std::vector<bool>>& getField() const;
    size_t getCurrentIteration() const;

    void step(); //одна итерация тип
};

#endif