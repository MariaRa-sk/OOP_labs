#include <iostream>
#include "GameConfig.h"
#include "FileWriter.h"

GameConfig::Mode GameConfig::getMode() const {
   return mode;
}

void GameConfig::setMode(Mode m) {
   mode = m;
}

const std::string& GameConfig::getUniverseName() const {
   return universeName;
}

void GameConfig::setUniverseName(const std::string& name) {
   universeName = name;
}

std::vector<std::pair<int, int>> GameConfig::getCells() const {
   return cells;
}

void GameConfig::setCells(std::vector<std::pair<int, int>> c) {
   cells = c;
}

size_t GameConfig::getIterations() const {
   return iterations;
}

void GameConfig::setIterations(size_t i) {
   iterations = i;
}

const std::string& GameConfig::getInputFile() const {
   return inputFile;
}

void GameConfig::setInputFile(const std::string& input) {
   inputFile = input;
}

const std::string& GameConfig::getOutputFile() const {
   return outputFile;
}

void GameConfig::setOutputFile(const std::string& output) {
   outputFile = output;
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

void GameConfig::saveInFile(const std::string& fileName) const {
   FileWriter writer(fileName);
   writer.open();
   if (!writer.isOpen()) {
      std::cout << "Error: Cannot open file " << fileName << " for writing" << std::endl;
      return;
   }
   writer.write("#Life 1.06");
   writer.write("#N " + getUniverseName());
   std::string birthStr, survivalStr;
   for (int r : getRuleBirth()) birthStr += std::to_string(r);
   for (int r : getRuleSurvival()) survivalStr += std::to_string(r);
   writer.write("#R B" + birthStr + "/S" + survivalStr);
   writer.write("#S C" + std::to_string(getWidth()) + "/R" + std::to_string(getHeight()));
   for (const auto& cell : getCells()) {
      writer.write({std::to_string(cell.first) + " " + std::to_string(cell.second)});
   }
   writer.close();
   std::cout << "Universe saved to: " << fileName << std::endl;
}
