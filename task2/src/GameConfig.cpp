#include <iostream>
#include "GameConfig.h"
#include "FileWriter.h"

const std::string& GameConfig::getUniverseName() const {
   return universeName;
}

void GameConfig::setUniverseName(const std::string& name) {
   universeName = name;
}

std::vector<std::pair<int, int>> GameConfig::getAliveCells() const {
   return aliveCells;
}

void GameConfig::setAliveCells(std::vector<std::pair<int, int>> c) {
   aliveCells = c;
}

const std::vector<int>& GameConfig::getRuleBirth() const{
   return ruleBirth;
}

void GameConfig:: setRuleBirth(const std::vector<int>& ruleB) {
   ruleBirth = ruleB;
}

const std::vector<int> &GameConfig::getRuleSurvival() const{
   return ruleSurvival;
}

void GameConfig:: setRuleSurvival(const std::vector<int>& ruleS) {
   ruleSurvival = ruleS;
}

int GameConfig::getWidth() const{
   return fieldWidth;
}

void GameConfig::setFieldWidth(int width) {
   fieldWidth = width;
}

int GameConfig::getHeight() const{
   return fieldHeight;
}

void GameConfig::setFieldHeight(int height) {
   fieldHeight = height;
}
