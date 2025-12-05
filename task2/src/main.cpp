#include "Parser.h"
#include "Controller.h"

int main(int argc, char* argv[]) {
    ArgumentParser parser;
    GameConfig config = parser.parseArguments(argc, argv);
    Controller controller(argc, argv);
    controller.run();
    return 0;
}