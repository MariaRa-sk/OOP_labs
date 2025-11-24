#include "GameMechanics.h"

GameMechanics::GameMechanics(GameConfig &config): config(config) {}

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
    size_t leftX =  (x - 1 + width) % width;
    size_t rightX = (x + 1 + width) % width;
    size_t lowY = (y - 1 + height) % height;
    size_t topY = (y + 1 + height) % height;
    size_t count = 0;

    for (size_t i = lowY; i <= topY; ++i) {
        for (size_t j = leftX; j <= rightX; ++j) {
            if (!(i == y && j==x) & isAlive(j, i)) {
                count++;
            }
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
