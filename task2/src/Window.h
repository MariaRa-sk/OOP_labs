#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "GameMechanics.h"
#include <string>

class Window {
private:
    const int cellSize = 20;
    size_t rows = 0;
    size_t columns = 0;
    sf::RenderWindow window;
    sf::Font font;
    std::string inputString;
    std::string formatRule(const std::vector<int>& rule);
public:
    Window(size_t width, size_t height, const std::vector<std::vector<bool>>& field);
    bool isOpen();
    void close();
    void displayInfo(const std::string& name, const std::vector<int>& ruleB,const std::vector<int>& ruleS, size_t iteration);
    void displayCommand();
    void drawField(const std::vector<std::vector<bool>>& field);
    bool pollEvent(sf::Event& event);
    void handleKeyPress(const sf::Event& event);
    void clear();
    void display();
    std::string getInputString();
    void clearInput();
};

#endif