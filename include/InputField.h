// InputField.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class InputField {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::RectangleShape cursor;
    sf::String input;
    bool isSelected;
    bool isHovered;
    std::string label;
    float value;
    bool isX;
    bool showCursor;
    sf::Clock cursorClock;
    bool justSelected;

    void updateCursorPosition();

public:
    InputField() = delete;
    InputField(const sf::Font& font, const std::string& fieldLabel,
        const sf::Vector2f& position, const sf::Vector2f& size, bool xCoord = true);

    void handleEvent(const sf::Event& event);
    void update();
    void setValue(float val);
    float getValue() const;
    bool isValidValue() const;
    void draw(sf::RenderWindow& window, const sf::Font& font);
    void clear();
};
// Encoding fix check