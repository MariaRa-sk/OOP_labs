#include <filesystem>
#include <iostream>

#include "Parser.h"
#include "Patterns.h"
#include "CommandHandler.h"
#include "Controller.h"


Controller::Controller(int argc, char* argv[]) : game(nullptr), window(nullptr), commandHandler(nullptr), isRunning(false) {
    config = ArgumentParser::parseArguments(argc, argv);
}

Controller::~Controller() {
    delete commandHandler;
    delete window;
    delete game;
}

void Controller::run() {
    if (config.getMode() == GameConfig::Mode::OFFLINE_MODE) {
        runOfflineMode();
    }
    else if (config.getMode() == GameConfig::Mode::FILE_MODE && std::filesystem::exists(config.getInputFile())) {
        runFileMode();
    }
    else {
        runDemoMode();
    }
}

void Controller::render() {
    window->clear();
    window->displayInfo(config.getUniverseName(),config.getRuleBirth(), config.getRuleSurvival(),game->getCurrentIteration());
    window->drawField(game->getField());
    window->displayCommand();
    window->display();
}

void Controller::runFileMode() {
    Parser parser(config.getInputFile());
    parser.parseFile(config);
    game = new GameMechanics(config);
    game->initializeField();
    window = new Window(1500, 900, game->getField());
    commandHandler = new CommandHandler(*game, *this);
    std::cout << "Game started! Type 'help' for commands." << std::endl;
    isRunning = true;
    while (isRunning && window->isOpen() && !commandHandler->shouldGameExit()) {
        processEvents();
        render();
    }
}

void Controller::runOfflineMode() {
    if (!std::filesystem::exists(config.getInputFile())) {
        std::cout << "Error: Input file '" << config.getInputFile() << "' not found!" << std::endl;
        return;
    }
    Parser parser(config.getInputFile());
    parser.parseFile(config);
    game = new GameMechanics(config);
    game->initializeField();
    size_t iterations = config.getIterations();
    window = new Window(1500, 900, game->getField());
    std::cout << "DEBUG: Window created, isOpen = " << window->isOpen() << std::endl;

    render();
    sf::sleep(sf::milliseconds(500));
    isRunning = true;
    for (size_t i = 0; i < iterations; ++i) {
        game->step();
        render();
        sf::sleep(sf::milliseconds(500));
        processEvents();
        if (!isRunning || (window && !window->isOpen())) {
            break;
        }
    }
    render();
    sf::sleep(sf::seconds(2));
    game->getConfig().saveInFile(config.getOutputFile());
    if (window) {
        window->close();
    }
}

void Controller::runDemoMode() {
    Patterns patterns;
    config = patterns.getRandomPattern();
    game = new GameMechanics(config);
    game->initializeField();
    window = new Window(1500, 900, game->getField());
    commandHandler = new CommandHandler(*game, *this);
    std::cout << "Game started with random pattern! Type 'help' for commands." << std::endl;
    isRunning = true;
    while (isRunning && window->isOpen() && !commandHandler->shouldGameExit()) {
        processEvents();
        render();
    }
}

void Controller::processEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning = false;
            window->close();
        }
        window->handleKeyPress(event);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            std::string command = window->getInputString();
            if (!command.empty()) {
                std::cout << "> " << command << std::endl;
                commandHandler->handleCommand(command);
                window->clearInput();
            }
        }
    }
}

