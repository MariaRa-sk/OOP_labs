#include "Parser.h"
#include <iostream>
#include <sstream>

bool ArgumentParser::isOnlyDigits(const std::string &str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool Parser::isDuplicateCell(int x, int y) {
    for (const auto& cell : cells) {
        if (cell.first == x & cell.second == y) {
            return true;
        }
    }
    return false;
}

bool Parser::isDuplicateRule(int digit, const std::vector<int>& rules) {
    for (size_t i = 0; i < rules.size(); ++i) {
        if (rules[i] == digit) {
            return true;
        }
    }
    return false;
}

bool Parser::parseFormat(const std::string &formatLine) {
    return formatLine == "#Life 1.06";
}

std::string Parser::parseUniverseName(const std::string &universeNameLine) {
    size_t nPos = universeNameLine.find("#N");
    if (nPos == std::string::npos) {
        throw std::runtime_error("Invalid universe name format: missing #N");
    }
    size_t nameStart = nPos + 2;
    if (nameStart >= universeNameLine.length()) {
        return "Unnamed Universe";
    }
    std::string name = universeNameLine.substr(nameStart);
    size_t start = name.find_first_not_of(" \t");
    size_t end = name.find_last_not_of(" \t");
    if (start == std::string::npos) {
        return "Unnamed Universe";
    }
    return name.substr(start, end - start + 1);
}

std::pair<std::vector<int>, std::vector<int>> Parser::parseRule(const std::string& ruleLine) {
    size_t rPos = ruleLine.find("#R");
    if (rPos == std::string::npos) {
        throw std::runtime_error("Invalid rules format: missing #R");
    }
    size_t bPos = ruleLine.find('B');
    size_t sPos = ruleLine.find('S');
    size_t slashPos = ruleLine.find('/');
    if (bPos == std::string::npos || sPos == std::string::npos || slashPos == std::string::npos) {
        std::cout << "Invalid rule format: missing 'B', 'S' or '/'. Default rules B3/S23 will be used." << std::endl;
        return {{3}, {2, 3}};
    }
    if (bPos > slashPos || sPos < slashPos) {
        std::cout << "Invalid rule format: wrong order of 'B', '/' or 'S'. Default rules B3/S23 will be used." << std::endl;
        return {{3}, {2, 3}};
    }
    std::vector<int> birthRule, survivalRule;
    std::string birthStr = ruleLine.substr(bPos + 1, slashPos - bPos - 1);
    std::string survivalStr = ruleLine.substr(sPos + 1);
    for (char c : birthStr) {
        int digit = c - '0';
        if (!std::isdigit(c) || digit > 8) {
            std::cout << "Invalid character '" << c << "' in birth rule. Default rules B3/S23 will be used." << std::endl;
            return {{3}, {2, 3}};
        }
        if (isDuplicateRule(digit, birthRule)) {
            std::cout << "Warning: Duplicate digit " << digit << " in birth rule. Skipped." << std::endl;
            continue;
        }
        birthRule.push_back(digit);
    }
    for (char c : survivalStr) {
        int digit = c - '0';
        if (!std::isdigit(c) || digit > 8) {
            std::cout << "Invalid character '" << c << "' in survival rule. Default rules B3/S23 will be used." << std::endl;
            return {{3}, {2, 3}};
        }
        if (isDuplicateRule(digit, survivalRule)) {
            std::cout << "Warning: Duplicate digit " << digit << " in survival rule. Skipped." << std::endl;
            continue;
        }
        survivalRule.push_back(digit);
    }
    return {birthRule, survivalRule};
}

std::pair<int, int> Parser::parseFieldSize(const std::string& fieldSizeLine) {
    size_t sPos = fieldSizeLine.find("#S");
    if (sPos == std::string::npos) {
        throw std::runtime_error("Invalid size format: missing #S");
    }
    size_t cPos = fieldSizeLine.find('C');
    size_t rPos= fieldSizeLine.find('R');
    size_t slashPos = fieldSizeLine.find('/');
    if (cPos == std::string::npos || rPos == std::string::npos || slashPos == std::string::npos) {
        std::cout << "Invalid rule format: missing 'C', 'R' or '/'. Default size 30x30 will be used." << std::endl;
        return {30, 30};
    }
    if (cPos > slashPos || rPos < slashPos) {
        std::cout << "Invalid rule format: wrong order of 'C', '/' or 'R'. Default size 30x30 will be used." << std::endl;
        return {30, 30};
    }
    std::string colsStr = fieldSizeLine.substr(cPos + 1, slashPos - cPos - 1);
    std::string rowsStr = fieldSizeLine.substr(rPos + 1);
    if (colsStr.empty() || rowsStr.empty()) {
        std::cout << "Empty size value. Default size 30x30 will be used." << std::endl;
        return {30, 30};
    }
    for (char c:colsStr) {
        if (!isdigit(c)) {
            std::cout << "Invalid character in columns. Default size 30x30 will be used." << std::endl;
            return {30, 30};
        }
    }
    for (char c:rowsStr) {
        if (!isdigit(c)) {
            std::cout << "Invalid character in rows. Default size 30x30 will be used." << std::endl;
            return {30, 30};
        }
    }
    int columns = std::stoi(colsStr);
    int rows = std::stoi(rowsStr);
    if (columns == 0 || rows == 0) {
        std::cout << "Zero size value. Default size 30x30 will be used." << std::endl;
        return {30, 30};
    }
    if (columns > 70 || rows > 40) {
        std::cout << "Field size " << columns << "x" << rows << " is too large. Maximum allowed size is 70x40. Default size 30x30 will be used." << std::endl;
        return {30, 30};
    }
    weight = columns;
    height = rows;
    return {columns, rows};
}

std::vector<std::pair<int, int>> Parser::parseCellField(const std::vector<std::string>& lines) {
    cells.clear();
    for (size_t i = 0; i < lines.size(); ++i) {
        const std::string& line = lines[i];
        if (line.empty()) {
            std::cout << "Warning: Line" << (i + 1)<< " - empty - skipped."<< std::endl;
            continue;
        }
        std::istringstream stream(line);
        int x, y;
        if (stream >> x >> y) {
            std::string remaining;
            if (stream >> remaining) {
                std::cout << "Warning: Line " << (i + 1) << " - extra data after two numbers - skipped" << std::endl;
                continue;
            }
            if (isDuplicateCell(x, y)) {
                std::cout << "Warning: Line " << (i + 1) << " - duplicate (" << x << ", " << y << "). skipped."<< std::endl;
                continue;
            }
            if (x < 0 || y < 0) {
                std::cout << "Warning: coordinates cannot be negative" << std::endl;
                continue;
            }
            if (x > weight || y > height) {
                std::cout << "Warning: coordinates cannot be more then field size" << std::endl;
                continue;
            }
            cells.emplace_back(x, y);
        }
        else {
            std::cout << "Warning: Line " << (i + 1) << " - invalid format. Expected: 'x y'" << std::endl;
        }
    }
    return cells;
}

GameConfig ArgumentParser::parseArguments(int argc, char* argv[]) {
    GameConfig config;
    if (argc == 1) {
        config.setMode(GameConfig::Mode::DEMO_MODE);
        return config;
    }
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }
    if (args.size() == 1 && args[0][0] != '-') {
        config.setMode(GameConfig::Mode::FILE_MODE);
        config.setInputFile(args[0]);
        return config;
    }
    config.setMode(GameConfig::Mode::OFFLINE_MODE);
    config.setIterations(1);

    for (size_t i = 0; i < args.size(); ++i) {
        const std::string& arg = args[i];
        if (arg == "-i") {
            if (i + 1 < args.size()) {
                std::string value = args[i + 1];
                if (!isOnlyDigits(value)) {
                    throw std::invalid_argument("Invalid iterations value: " + value);
                }
                size_t iterations = static_cast<size_t>(std::stoi(value));
                config.setIterations(iterations);
                i++;
            }
            else {
                throw std::invalid_argument("Missing value for " + arg);
            }
        }
        else if (arg.find("--iterations=") == 0) {
            std::string value = arg.substr(std::string("--iterations=").length());
            if (!isOnlyDigits(value)) {
                throw std::invalid_argument("Invalid iterations value: " + value);
            }
            size_t iterations = static_cast<size_t>(std::stoi(value));
            config.setIterations(iterations);
        }
        else if (arg == "-o") {
            if (i + 1 < args.size()) {
                config.setOutputFile(args[i + 1]);
                i++;
            }
            else {
                throw std::invalid_argument("Missing value for " + arg);
            }
        }
        else if (arg.find("--output=") == 0) {
            config.setOutputFile(arg.substr(std::string("--output=").length()));
        }
        else if (arg[0] == '-') {
            throw std::invalid_argument("Unknown option: " + arg);
        }
        else {
            if (config.getInputFile().empty()) {
                config.setInputFile(arg);
            } else {
                throw std::invalid_argument("Unexpected argument: " + arg);
            }
        }
    }
    if (config.getInputFile().empty()) {
        throw std::invalid_argument("Input file is required for offline mode");
    }
    if (config.getOutputFile().empty()) {
        throw std::invalid_argument("Output file is required for offline mode");
    }
    return config;
}

void Parser::parseFile(GameConfig& config) {
    reader.open();
    if (!reader.isOpen()) {
        throw std::runtime_error("Cannot open file: " + reader.getFileName());
    }
    if (reader.isEOF()) {
        throw std::runtime_error("File is empty");
    }
    std::string formatLine = reader.getLine();
    if (!parseFormat(formatLine)) {
        throw std::runtime_error("Invalid file format: expected #Life 1.06");
    }
    std::string name = reader.getLine();
    config.setUniverseName(parseUniverseName(name));

    auto rules = reader.getLine();
    auto parseR = parseRule(rules);
    config.setRuleBirth(parseR.first);
    config.setRuleSurvival(parseR.second);

    auto sizes = reader.getLine();
    auto parseS = parseFieldSize(sizes);
    config.setFieldWidth(parseS.first);
    config.setFieldHeight(parseS.second);

    std::vector<std::string> cellLines;
    while (!reader.isEOF()) {
        std::string cellLine = reader.getLine();
        cellLines.emplace_back(cellLine);
    }
    if (cellLines.empty()) {
        throw std::runtime_error("No cell data found in file");
    }
    config.setCells(parseCellField(cellLines));
}

