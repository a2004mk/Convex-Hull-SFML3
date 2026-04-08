// Renderer.h
#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "EditPointWindow.h"

class Renderer {
private:
    sf::RenderWindow& window;
    sf::Font& font;
    GameState& gameState;  // Убрали const
    const std::vector<Button>& buttons;

    void drawWorkArea();
    void drawPoints();
    void drawHull();
    void drawPreview();
    void drawUI();
    void drawEditWindow(EditPointWindow& editWindow);  // Убрали const

public:
    Renderer(sf::RenderWindow& wnd, sf::Font& fnt,
        GameState& state, const std::vector<Button>& btns);  // Убрали const у state

    void render(EditPointWindow& editWindow);  // Убрали const
};
// Encoding fix check