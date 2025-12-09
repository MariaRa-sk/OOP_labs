#include <filesystem>
#include <iostream>

#include "Parser.h"
#include "Patterns.h"
#include "CommandHandler.h"
#include "Controller.h"

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
    config.saveInFile(options.getOutputFile());
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

GameConfig Controller::getGameConfig() const {
    return config;
}
