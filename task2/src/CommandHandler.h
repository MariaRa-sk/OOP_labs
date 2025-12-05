#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string>
#include <vector>
#include "GameMechanics.h"

class Controller;

class CommandHandler {
private:
    GameMechanics& game;
    Controller& controller;
    bool shouldExit;
    void handleDump(const std::vector<std::string>& args);
    void handleTick(const std::vector<std::string>& args);
    void handleExit(const std::vector<std::string>& args);
    void handleHelp(const std::vector<std::string>& args);
    std::vector<std::string> parseCommand(const std::string &command);
public:
    CommandHandler(GameMechanics& game, Controller& controller);
    bool handleCommand(const std::string& command);
    bool shouldGameExit() const;
};

#endif
