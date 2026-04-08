// InputHandler.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameState.h"
#include "Button.h"
#include "EditPointWindow.h"

class InputHandler {
private:
    std::vector<Button>& buttons;
    GameState& gameState;
    EditPointWindow& editWindow;
    sf::Font& font;

    void handleKeyPressed(const sf::Event::KeyPressed& keyPressed);
    void handleMouseMoved(const sf::Event::MouseMoved& mouseMoved);
    void handleMousePressed(const sf::Event::MouseButtonPressed& mousePressed);
    void handleMouseReleased(const sf::Event::MouseButtonReleased& mouseReleased);
    void handleButtonAction(const std::string& action);

public:
    InputHandler(std::vector<Button>& btns, GameState& state,
        EditPointWindow& editWnd, sf::Font& fnt);

    void handleEvent(const sf::Event& event);
};
// Encoding fix check