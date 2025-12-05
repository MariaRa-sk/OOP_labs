#include "Window.h"
#include <stdexcept>
#include <iostream>

Window::Window(size_t width, size_t height, const std::vector<std::vector<bool>>& field): rows(field.size()), columns(field[0].size()){
    window.create(sf::VideoMode(width, height), "Game Window");
    if (!font.loadFromFile("C:/Windows/Fonts/calibri.ttf")) {
        std::cout << "Warning: Could not load font, text will not be displayed" << std::endl;
    }
}

bool Window::isOpen() {
    return window.isOpen();
}

std::string Window::formatRule(const std::vector<int>& rule) {
    std::string result;
    for (int num : rule) {
        result += std::to_string(num);
    }
    return result;
}

void Window::displayInfo(const std::string& name, const std::vector<int>& ruleB, const std::vector<int>& ruleS, size_t iteration) {
    sf::Text text;
    if (font.getInfo().family.empty()) {
        bool isPrintInfo = false;
        if (!isPrintInfo) {
            std::cout << "Info: Universe: " << name << ", Rule B" << formatRule(ruleB) << "/S" << formatRule(ruleS)<< ", Iteration: " << iteration << std::endl;
            isPrintInfo = true;
        }
        return;
    }
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);

    text.setString("Universe: " + name);
    text.setPosition(5, 5);
    window.draw(text);
    text.setString("Rule: B" + formatRule(ruleB) + "/S" + formatRule(ruleS));
    text.setPosition(5, 25);
    window.draw(text);
    text.setString("Iteration: " + std::to_string(iteration));
    text.setPosition(5, 45);
    window.draw(text);
}

void Window::displayCommand() {
    if (font.getInfo().family.empty()) return;
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);

    int commandY = 70 + rows * cellSize + 10;

    if (!inputString.empty()) {
        text.setString("> " + inputString );
        text.setPosition(5, commandY);
        window.draw(text);
    }
    else {
        text.setString(">");
        text.setPosition(5, commandY);
        text.setFillColor(sf::Color(180, 180, 180));
        window.draw(text);
    }
}

void Window::drawField(const std::vector<std::vector<bool>>& field) {
    int startY = 70;
    int startX = 5;
    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < columns; x++) {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
            size_t invertedY = rows - 1 - y;
            cell.setPosition(x * cellSize + startX, invertedY * cellSize + startY);
            if (field[y][x]) {
                cell.setFillColor(sf::Color::Green);
            }
            else {
                cell.setFillColor(sf::Color::Black);
            }
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color(200, 200, 200));
            window.draw(cell);
        }
    }
}

bool Window::pollEvent(sf::Event& event) {
    return window.pollEvent(event);
}

void Window::close() {
    window.close();
}

void Window::clear() {
    window.clear(sf::Color::Black);
}

void Window::display() {
    window.display();
}

void Window::handleKeyPress(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8) {
            if (!inputString.empty()) {
                inputString.pop_back();
            }
        }
        else if (event.text.unicode < 128) {
            inputString += static_cast<char>(event.text.unicode);
        }
    }
}

std::string Window::getInputString() {
    return inputString;
}

void Window::clearInput() {
    inputString.clear();
}
