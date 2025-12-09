#include "GameMechanics.h"
#include "FileWriter.h"
#include <iostream>

GameMechanics::GameMechanics(GameConfig& config):
ruleBirth(config.getRuleBirth()),ruleSurvival(config.getRuleSurvival()),
aliveCells(config.getAliveCells()), fieldHeight(config.getHeight()), fieldWidth(config.getHeight()) {
    initializeField();
}

void GameMechanics::initializeField() {
    currentField.resize(fieldHeight, std::vector<bool>(fieldWidth, false));
    for (const auto& cell :aliveCells) {
        int x = cell.first;
        int y = cell.second;
        currentField[y][x] = true;
    }
    oldField = currentField;
}

size_t GameMechanics::countNeighbors(size_t x, size_t y) const {
    size_t count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            size_t newX = (x + dx + fieldWidth) % fieldWidth;
            size_t newY = (y + dy + fieldHeight) % fieldHeight;
            if (isAlive(newX, newY)) count++;
        }
    }
    return count;
}

size_t GameMechanics::getCurrentIteration() const {
    return currentIteration;
}

const std::vector<std::vector<bool>>& GameMechanics::getField() const {
    return currentField;
}

bool GameMechanics::isAlive(size_t x, size_t y) const {
    return oldField[y][x];
}

void GameMechanics::step() {
    ++currentIteration;
    for (size_t y = 0; y < fieldHeight; ++y) {
        for (size_t x = 0; x < fieldWidth; ++x) {
            size_t neighbors = countNeighbors(x, y);
            bool shouldBirth = false;
            bool shouldSurvival = false;
            if (isAlive(x,y)) {
                for (int rule : ruleSurvival) {
                    if (neighbors == rule) {
                        shouldSurvival = true;
                        break;
                    }
                }
                if (!shouldSurvival) {
                    currentField[y][x] = false;
                }
            }
            else {
                for (int rule : ruleBirth) {
                    if (neighbors == rule) {
                        shouldBirth = true;
                        break;
                    }
                }
                if (shouldBirth) {
                    currentField[y][x] = true;
                }
            }
        }
    }
    oldField = currentField;
}
