// Button.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color pressedColor;
    bool isPressed;
    bool isHovered;
    std::string action;

public:
    Button() = delete;
    Button(const sf::Font& font, const sf::String& buttonText,
        const sf::Vector2f& position, const sf::Vector2f& size,
        const std::string& buttonAction = "");



    void handleEvent(const sf::Event::MouseMoved& mouseMoved);
    bool handleEvent(const sf::Event::MouseButtonPressed& mousePressed);
    bool handleEvent(const sf::Event::MouseButtonReleased& mouseReleased);
    void draw(sf::RenderWindow& window) const;

    void setText(const sf::String& newText);

    const std::string& getAction() const;
};
// Encoding fix check