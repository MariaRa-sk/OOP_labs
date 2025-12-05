#ifndef PARSER_H
#define PARSER_H

#include "FileReader.h"
#include "GameConfig.h"

#include <string>
#include <vector>
class Parser {
private:
    size_t weight = 30;
    size_t height = 30;
    FileReader reader;
    std::vector<std::pair<int, int>> cells;
    static bool isDuplicateRule(int digit, const std::vector<int>& rules);
    bool isDuplicateCell(int x, int y);
    static bool parseFormat(const std::string& formatLine);
    static std::string parseUniverseName(const std::string& universeNameLine);
    static std::pair<std::vector<int>, std::vector<int>> parseRule(const std::string& ruleLine);
    std::pair<int, int> parseFieldSize(const std::string& fieldSizeLine);
    std::vector<std::pair<int, int>> parseCellField(const std::vector<std::string>& lines);
public:
    explicit Parser(const std::string& fileName): reader(fileName){}
    void parseFile(GameConfig& config);
};

class ArgumentParser {
private:
    static bool isOnlyDigits(const std::string& str);
public:
    static GameConfig parseArguments(int argc, char* argv[]);
};

#endif