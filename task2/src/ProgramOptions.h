#ifndef PROGRAMOPTIONS_H
#define PROGRAMOPTIONS_H

#include <string>

class ProgramOptions {
public:
    enum class Mode {
        DEMO_MODE,
        FILE_MODE,
        OFFLINE_MODE,
    };
private:
    Mode mode = Mode::DEMO_MODE;
    std::string inputFile;
    std::string outputFile;
    size_t iterations = 1;

public:
    Mode getMode() const;
    const std::string& getInputFile() const;
    const std::string& getOutputFile() const;
    size_t getIterations() const;

    void setMode(Mode m);
    void setInputFile(const std::string& file);
    void setOutputFile(const std::string& file);
    void setIterations(size_t iter);
};

#endif