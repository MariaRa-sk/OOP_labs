#include "Parser.h"
#include "Controller.h"
#include "Patterns.h"

int main(int argc, char* argv[]) {
    ArgumentParser parserArg;
    ProgramOptions options = parserArg.parseArguments(argc, argv);
    GameConfig config;
    if (!options.getInputFile().empty()) {
        Parser parser(options.getInputFile());
        config = parser.parseFile();
    }
    else {
        Patterns patterns;
        config = patterns.getRandomPattern();
    }
    Controller controller(config, options);
    controller.run();
    return 0;
}
