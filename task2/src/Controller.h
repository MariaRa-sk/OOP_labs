#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "GameConfig.h"
#include "GameMechanics.h"
#include "Window.h"
class CommandHandler;

class Controller {
private:
    GameConfig config;
    GameMechanics* game;
    Window* window;
    CommandHandler* commandHandler;
    bool isRunning;
    void runFileMode();
    void runOfflineMode();
    void runDemoMode();
    void processEvents();
public:
    Controller(int argc, char* argv[]);
    ~Controller();
    void run();
    void render();
};

#endif