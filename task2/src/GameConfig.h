#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <string>
#include <vector>

class GameConfig {
public:
    enum class Mode {
        DEMO_MODE,
        FILE_MODE,
        OFFLINE_MODE,
    };
private:
    std::string universeName = "Unnamed Universe";

    std::vector<int> ruleBirth = {3};
    std::vector<int> ruleSurvival = {2, 3};

    int fieldWidth = 30;
    int fieldHeight = 30;

    std::vector<std::pair<int, int>> cells;
    Mode mode = Mode::DEMO_MODE;

    std::string inputFile;
    size_t iterations = 1;
    std::string outputFile;

public:
    Mode getMode() const;
    void setMode(Mode m);

    const std::string& getUniverseName() const;
    void setUniverseName(const std::string& name);

    std::vector<std::pair<int, int>> getCells() const; //?? что с ссылкой и конст
    void setCells(std::vector<std::pair<int, int>> c);

    size_t getIterations() const;
    void setIterations(size_t i);

    const std::string& getInputFile() const;
    void setInputFile(const std::string& input);

    const std::string& getOutputFile() const;
    void setOutputFile(const std::string& input);

    const std::vector<int>& getRuleBirth() const;
    void setRuleBirth(const std::vector<int>& ruleB);

    const std::vector<int>& getRuleSurvival() const;
    void setRuleSurvival(const std::vector<int>& ruleS);

    int getWidth() const;
    void setFieldWidth(int width);

    int getHeight() const;
    void setFieldHeight(int height);
};

#endif
