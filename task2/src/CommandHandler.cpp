#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>

#include "CommandHandler.h"
#include "Controller.h"
#include "FileWriter.h"

CommandHandler::CommandHandler(GameMechanics& game, Controller& controller)
    : game(game), controller(controller),shouldExit(false) {}

void CommandHandler::handleDump(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Usage: dump <filename>" << std::endl;
        return;
    }
    const std::string& filename = args[1];
    game.getConfig().saveInFile(filename);
}

void CommandHandler::handleTick(const std::vector<std::string>& args) {
    int n = 1;
    if (args.size() >= 2) {
        try {
            n = std::stoi(args[1]);
            if (n < 1) {
                std::cout << "Number of iterations must be positive" << std::endl;
                return;
            }
        } catch (const std::exception& e) {
            std::cout << "Invalid number format: " << args[1] << std::endl;
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        game.step();
        controller.render();
        sf::sleep(sf::milliseconds(500));
    }
}

void CommandHandler::handleExit() {
    shouldExit = true;
    std::cout << "Exiting game..." << std::endl;
}

void CommandHandler::handleHelp() {
    std::cout << "Available commands:\n"
              << "  dump <filename>    - Save universe to file\n"
              << "  tick <n=1>         - Advance n iterations (default 1)\n"
              << "  t <n=1>            - Short for tick\n"
              << "  exit               - Quit the game\n"
              << "  help               - Show this help\n";
}

bool CommandHandler::handleCommand(const std::string& command) {
    if (command.empty()) return true;
    std::vector<std::string> commands = parseCommand(command);
    std::string cmd = commands[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd == "dump") handleDump(commands);
    else if (cmd == "tick" || cmd == "t") handleTick(commands);
    else if (cmd == "exit" || cmd == "quit") {
        handleExit();
        return false;
    }
    else if (cmd == "help") handleHelp();
    else {
        std::cout << "Unknown command: " << command << std::endl;
        std::cout << "Type 'help' for available commands" << std::endl;
    }
    return true;
}

std::vector<std::string> CommandHandler::parseCommand(const std::string &command) {
    std::vector<std::string> commands;
    std::stringstream stream(command);
    std::string i;
    while (stream >> i) {
        commands.push_back(i);
    }
    return commands;
}

bool CommandHandler::shouldGameExit() const {
    return shouldExit;
}
