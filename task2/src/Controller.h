#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "FileWriter.h"
#include "GameConfig.h"
#include "GameMechanics.h"
#include "ProgramOptions.h"
#include "Window.h"

class CommandHandler;

class Controller {
private:
    GameConfig config;
    ProgramOptions options;
    GameMechanics game;            // Всегда существует
    Window window;                 // Всегда существует
    CommandHandler* commandHandler = nullptr; // Только этот указатель
    bool isRunning = false;

    void runFileMode();
    void runOfflineMode();
    void runDemoMode();
    void processEvents();
public:
    Controller(GameConfig config, ProgramOptions options);
    ~Controller();
    void run();
    void render();
    GameConfig getGameConfig() const;
};

#endif