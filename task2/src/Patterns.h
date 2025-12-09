#ifndef PATTERNS_H
#define PATTERNS_H

#include "GameConfig.h"
#include <string>
#include <vector>
#include <map>
#include <random>

class Patterns {
private:
    std::map<std::string, std::vector<std::pair<int, int>>> patterns;
    std::mt19937 rng;
    void initializePatterns();
public:
    Patterns();
    GameConfig getRandomPattern();
    GameConfig getPatternByName(const std::string& name);
};

#endif