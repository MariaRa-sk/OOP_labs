#include <filesystem>
#include <iostream>

#include "CommandHandler.h"
#include "Controller.h"
#include "FileWriter.h"
#include "Parser.h"


Controller::Controller(GameConfig config, ProgramOptions options):
    config(config),
    options(options),
    game(this->config),
    window(1500, 900, game.getField()){}

Controller::~Controller() {
    delete commandHandler;
}

void Controller::run() {
    if (options.getMode() == ProgramOptions::Mode::OFFLINE_MODE) {
        runOfflineMode();
    }
    else if (options.getMode() == ProgramOptions::Mode::FILE_MODE && std::filesystem::exists(options.getInputFile())) {
        runFileMode();
    }
    else {
        runDemoMode();
    }
}

void Controller::render(){
    window.clear();
    window.displayInfo(config.getUniverseName(),config.getRuleBirth(), config.getRuleSurvival(),game.getCurrentIteration());
    window.drawField(game.getField());
    window.displayCommand();
    window.display();
}

void Controller::runFileMode() {
    commandHandler = new CommandHandler(game, *this);
    std::cout << "Game started! Type 'help' for commands." << std::endl;
    isRunning = true;
    while (isRunning && window.isOpen() && !commandHandler->shouldGameExit()) {
        processEvents();
        render();
    }
}

void Controller::runOfflineMode() {
    size_t iterations = options.getIterations();
    render();
    sf::sleep(sf::milliseconds(500));
    isRunning = true;
    for (size_t i = 0; i < iterations; ++i) {
        game.step();
        render();
        sf::sleep(sf::milliseconds(500));
        processEvents();
        if (!isRunning || (!window.isOpen())) {
            break;
        }
    }
    render();
    sf::sleep(sf::seconds(2));
    saveInFile(options.getOutputFile());
    window.close();
}

void Controller::runDemoMode() {
    commandHandler = new CommandHandler(game, *this);
    std::cout << "Game started with random pattern! Type 'help' for commands." << std::endl;
    isRunning = true;
    while (isRunning && window.isOpen() && !commandHandler->shouldGameExit()) {
        processEvents();
        render();
    }
}

void Controller::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning = false;
            window.close();
        }
        window.handleKeyPress(event);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            std::string command = window.getInputString();
            if (!command.empty()) {
                std::cout << "> " << command << std::endl;
                commandHandler->handleCommand(command);
                window.clearInput();
            }
        }
    }
}

void Controller::saveInFile(const std::string& fileName) const {
    FileWriter writer(fileName);
    writer.open();
    if (!writer.isOpen()) {
        std::cout << "Error: Cannot open file " << fileName << " for writing" << std::endl;
        return;
    }
    writer.write("#Life 1.06");
    writer.write("#N " + config.getUniverseName());
    std::string birthStr, survivalStr;
    for (int r : config.getRuleBirth()) birthStr += std::to_string(r);
    for (int r : config.getRuleSurvival()) survivalStr += std::to_string(r);
    writer.write("#R B" + birthStr + "/S" + survivalStr);
    writer.write("#S C" + std::to_string(config.getWidth()) + "/R" + std::to_string(config.getHeight()));

    const std::vector<std::vector<bool>>& currentField = game.getField();

    for (int y = 0; y < currentField.size(); y++) {
        for (int x = 0; x < currentField[0].size(); x++) {
            if (currentField[y][x]) {
                writer.write(std::to_string(x) + " " + std::to_string(y));
            }
        }
    }
    writer.close();
    std::cout << "Universe saved to: " << fileName << std::endl;
}
