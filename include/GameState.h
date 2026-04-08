// GameState.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Point.h"
#include "Button.h"
#include "EditPointWindow.h"

constexpr float POINT_SELECTION_RADIUS = 20.0f;

struct GameState {
    // Данные
    std::vector<Point> points;
    std::vector<Point> hull;

    // Режимы
    bool addMode;
    bool editMode;
    int selectedPointIndex;
    sf::Vector2f mousePos;

    // Генераторы случайных чисел
    std::mt19937 gen;
    std::uniform_real_distribution<float> distX;
    std::uniform_real_distribution<float> distY;

    // Графические объекты
    sf::CircleShape pointShape;
    sf::CircleShape hullPointShape;
    sf::CircleShape selectedPointShape;
    sf::CircleShape tempPointShape;
    sf::VertexArray hullLines;

    GameState();
    void generateRandomPoints(int count);
    void updateHull();
    void removeLastPoint();
    void clearAll();
    void tryAddPoint(const sf::Vector2f& clickPos);
    int findPointNear(const sf::Vector2f& pos, float threshold) const;
};

// Конфигурация
struct GameConfig {
    static const sf::Vector2f BUTTON_POSITIONS[7];
    static const sf::Vector2f BUTTON_SIZES[7];
    static const std::wstring BUTTON_TEXTS[7];
    static const std::string BUTTON_ACTIONS[7];
    static const int BUTTON_COUNT;

    static const sf::Vector2f WINDOW_SIZE;
    static const sf::Vector2f INSTRUCTION_POS;
    static const sf::Vector2f COUNTER_POS;
    static const sf::Vector2f BOUNDS_POS;
    static const sf::Vector2f MODE_TEXT_POS;
};
// Encoding fix check