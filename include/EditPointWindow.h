// EditPointWindow.h
#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Button.h"
#include "InputField.h"

class EditPointWindow {
private:
    sf::RectangleShape background;
    sf::Text title;
    InputField inputX;
    InputField inputY;
    Button saveButton;
    Button cancelButton;
    sf::Text errorText;
    bool isVisible;
    Point* currentPoint;
    Point originalPoint;
    bool hasError;

public:
    EditPointWindow() = delete;
    EditPointWindow(const sf::Font& font);

    void show(Point& point);
    void hide();
    bool isShown() const;
    void handleEvent(const sf::Event& event, std::vector<Point>& points, std::vector<Point>& hull);
    void update();
    void draw(sf::RenderWindow& window, const sf::Font& font);
};
// Encoding fix check