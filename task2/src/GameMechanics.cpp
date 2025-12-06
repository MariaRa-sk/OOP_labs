#include "GameMechanics.h"
#include "FileWriter.h"
#include <iostream>

GameMechanics::GameMechanics(GameConfig& config): config(config) {}

void GameMechanics::initializeField() {
    size_t width = config.getWidth();
    size_t height = config.getHeight();
    currentField.resize(height, std::vector<bool>(width, false));
    for (const auto& cell : config.getCells()) {
        int x = cell.first;
        int y = cell.second;
        currentField[y][x] = true;
    }
    oldField = currentField;
}

size_t GameMechanics::countNeighbors(size_t x, size_t y) const {
    size_t width = config.getWidth();
    size_t height = config.getHeight();
    size_t count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            size_t newX = (x + dx + width) % width;
            size_t newY = (y + dy + height) % height;
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
    size_t width = config.getWidth();
    size_t height = config.getHeight();
    std::vector<int> birth = config.getRuleBirth();
    std::vector<int> survival = config.getRuleSurvival();
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            size_t neighbors = countNeighbors(x, y);
            bool shouldBirth = false;
            bool shouldSurvival = false;
            if (isAlive(x,y)) {
                for (int rule : survival) {
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
                for (int rule : birth) {
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

void GameMechanics::updateConfigCells() {
    std::vector<std::pair<int, int>> aliveCells;
    for (size_t y = 0; y < currentField.size(); ++y) {
        for (size_t x = 0; x < currentField[y].size(); ++x) {
            if (isAlive(x,y)) {
                aliveCells.emplace_back(x, y);
            }
        }
    }
    config.setCells(aliveCells);
}

const GameConfig& GameMechanics::getConfig() const {
    return config;
}
