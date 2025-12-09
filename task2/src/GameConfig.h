#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <string>
#include <vector>

class GameConfig {
private:
    std::string universeName = "Unnamed Universe";

    std::vector<int> ruleBirth = {3};
    std::vector<int> ruleSurvival = {2, 3};

    int fieldWidth = 30;
    int fieldHeight = 30;

    std::vector<std::pair<int, int>> aliveCells;
public:

    const std::string& getUniverseName() const;
    void setUniverseName(const std::string& name);

    std::vector<std::pair<int, int>> getAliveCells() const;
    void setAliveCells(std::vector<std::pair<int, int>> c);

    const std::vector<int>& getRuleBirth() const;
    void setRuleBirth(const std::vector<int>& ruleB);

    const std::vector<int>& getRuleSurvival() const;
    void setRuleSurvival(const std::vector<int>& ruleS);

    int getWidth() const;
    void setFieldWidth(int width);

    int getHeight() const;
    void setFieldHeight(int height);

    void saveInFile(const std::string& fileName) const;
};

#endif
