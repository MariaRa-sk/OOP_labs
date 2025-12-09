#include "Patterns.h"
#include <iostream>
#include <random>

Patterns::Patterns() : rng(std::random_device{}()) {
    initializePatterns();
}

void Patterns::initializePatterns() {
     patterns["Blinker"] = {
         {14, 14}, {15, 14}, {16, 14}
     };

     patterns["Toad"] = {
         {14, 14}, {15, 14}, {16, 14},
         {13, 15}, {14, 15}, {15, 15}
     };

     patterns["Glider"] = {
         {15, 14}, {16, 15}, {14, 16}, {15, 16}, {16, 16}
     };

     patterns["Lightweight Spaceship"] = {
         {13, 14}, {16, 14},
         {12, 15},
         {12, 16}, {16, 16},
         {12, 17}, {13, 17}, {14, 17}, {15, 17}
     };

     patterns["Beacon"] = {
         {14, 14}, {15, 14},
         {14, 15}, {15, 15},
         {16, 16}, {17, 16},
         {16, 17}, {17, 17}
     };

     patterns["Pulsar"] = {
         {12, 10}, {13, 10}, {14, 10}, {18, 10}, {19, 10}, {20, 10},
         {10, 12}, {10, 13}, {10, 14}, {10, 18}, {10, 19}, {10, 20},
         {20, 12}, {20, 13}, {20, 14}, {20, 18}, {20, 19}, {20, 20},
         {12, 20}, {13, 20}, {14, 20}, {18, 20}, {19, 20}, {20, 20}
     };

     patterns["Gosper Glider Gun"] = {
         {1, 5}, {2, 5}, {1, 6}, {2, 6},
         {11, 5}, {11, 6}, {11, 7},
         {12, 4}, {12, 8},
         {13, 3}, {13, 9}, {14, 3}, {14, 9},
         {15, 6}, {16, 4}, {16, 8},
         {17, 5}, {17, 6}, {17, 7}, {18, 6}
     };

     patterns["Beehive"] = {
         {14, 14}, {15, 13}, {15, 15},
         {16, 14}, {17, 13}, {17, 15}
     };

     patterns["Loaf"] = {
         {14, 14}, {15, 13}, {16, 13},
         {17, 14}, {16, 15}, {15, 15}
     };

    patterns["Ants"] = {
        {9,15}, {10, 15}, {9,12}, {10,12},
        {11,14},{11,13}, {12,14},{12,13},
        {14, 15}, {15, 15}, {16, 14}, {16, 13},
        {17, 14}, {17, 13}, {14, 12}, {15, 12},
        {19, 15}, {20, 15}, {19, 12}, {20, 12},
        {21, 14}, {21, 13}, {22, 14}, {22, 13}
    };

    patterns["Butterfly"]={
        {20,15}, {20,14}, {20,16}, {17,15}, {17,14}, {17,16},
        {19,17}, {20,17}, {21,17}, {18,17},
        {19,13}, {20,13}, {21,13}, {18,13},
        {17,19}, {17,21}, {17,11}, {17,9},
        {14, 19}, {14,11}, {13,20}, {13,21},
        {13,22}, {13,10}, {13,9}, {13,8},
        {14,22}, {15,22}, {16,22},
        {14,8}, {15,8}, {16,8}
    };
}

GameConfig Patterns::getPatternByName(const std::string& name) {
    GameConfig config;
    auto it = patterns.find(name);
    config.setUniverseName(name);
    config.setAliveCells(it->second);
    return config;
}

GameConfig Patterns::getRandomPattern() {
    std::vector<std::string> keys;
    for (const auto& pair : patterns) {
        keys.push_back(pair.first);
    }
    std::uniform_int_distribution<size_t> dist(0, keys.size() - 1);
    std::string randomKey = keys[dist(rng)];
    return getPatternByName(randomKey);
}
