#include "ProgramOptions.h"

ProgramOptions::Mode ProgramOptions::getMode() const {
    return mode;
}

const std::string& ProgramOptions::getInputFile() const {
    return inputFile;
}

const std::string& ProgramOptions::getOutputFile() const{
    return outputFile;
}

size_t ProgramOptions::getIterations() const {
    return iterations;
}

void ProgramOptions::setMode(Mode m) {
    mode = m;
}

void ProgramOptions::setInputFile(const std::string& input) {
    inputFile = input;
}
void ProgramOptions::setOutputFile(const std::string& output) {
    outputFile = output;
}
void ProgramOptions::setIterations(size_t i) {
    iterations = i;
}