// InputField.cpp
#include "InputField.h"
#include "Point.h"
#include <sstream>

// конструктор: создание поля ввода с лейблом и настройками
InputField::InputField(const sf::Font& font, const std::string& fieldLabel,
    const sf::Vector2f& position, const sf::Vector2f& size, bool xCoord)
    : text(font), isSelected(false), isHovered(false), label(fieldLabel), value(0),
    isX(xCoord), showCursor(false), justSelected(false) {

    // фон поля ввода
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(50, 50, 50));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color(100, 100, 100));

    // текст значения внутри поля
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setPosition({ position.x + 5, position.y + 5 });
    text.setString("0");
    input = "0";

    // курсор ввода (мигающая вертикальная черта)
    cursor.setSize({ 2, 20 });
    cursor.setFillColor(sf::Color::White);
    updateCursorPosition();
}

// обновление позиции курсора после изменения текста
void InputField::updateCursorPosition() {
    float textWidth = text.getGlobalBounds().size.x;
    cursor.setPosition({ shape.getPosition().x + 7 + textWidth, shape.getPosition().y + 5 });
}

// обработка событий: ввод текста, клик, наведение
void InputField::handleEvent(const sf::Event& event) {
    // ввод символа с клавиатуры
    if (event.is<sf::Event::TextEntered>()) {
        const sf::Event::TextEntered* textEntered = event.getIf<sf::Event::TextEntered>();
        if (isSelected && textEntered) {
            // backspace — удаление последнего символа
            if (textEntered->unicode == '\b') {
                if (!input.isEmpty()) {
                    input.erase(input.getSize() - 1);
                    if (input.isEmpty()) input = "0";
                }
            }
            // допустимые символы: цифры, точка, минус
            else if (textEntered->unicode < 128) {
                char c = static_cast<char>(textEntered->unicode);
                if (isdigit(c) || c == '.' || c == '-') {
                    // первый символ после фокуса — заменяем "0"
                    if (justSelected) {
                        input.clear();
                        justSelected = false;
                    }
                    if (input == "0") input.clear();
                    input += c;
                }
            }
            text.setString(input);
            updateCursorPosition();
            cursorClock.restart();  // сброс таймера мигания
            showCursor = true;
        }
    }
    // клик мыши — выбор поля для ввода
    else if (event.is<sf::Event::MouseButtonPressed>()) {
        const sf::Event::MouseButtonPressed* mousePressed = event.getIf<sf::Event::MouseButtonPressed>();
        if (mousePressed) {
            sf::Vector2f mousePos(static_cast<float>(mousePressed->position.x),
                static_cast<float>(mousePressed->position.y));
            bool wasSelected = isSelected;
            isSelected = shape.getGlobalBounds().contains(mousePos);

            if (isSelected) {
                shape.setOutlineColor(sf::Color::Green);  // визуальный фокус
                cursorClock.restart();
                showCursor = true;
                if (!wasSelected) {
                    justSelected = true;  // следующий символ заменит "0"
                }
            }
            else {
                shape.setOutlineColor(sf::Color(100, 100, 100));
                showCursor = false;
                justSelected = false;
            }
        }
    }
    // наведение мыши — подсветка рамки
    else if (event.is<sf::Event::MouseMoved>()) {
        const sf::Event::MouseMoved* mouseMoved = event.getIf<sf::Event::MouseMoved>();
        if (mouseMoved) {
            sf::Vector2f mousePos(static_cast<float>(mouseMoved->position.x),
                static_cast<float>(mouseMoved->position.y));
            bool contains = shape.getGlobalBounds().contains(mousePos);

            if (contains && !isHovered) {
                isHovered = true;
                if (!isSelected) {
                    shape.setOutlineColor(sf::Color(150, 150, 150));
                }
            }
            else if (!contains && isHovered && !isSelected) {
                isHovered = false;
                shape.setOutlineColor(sf::Color(100, 100, 100));
            }
        }
    }
}

// обновление анимации курсора (мигание каждые 500 мс)
void InputField::update() {
    if (isSelected) {
        if (cursorClock.getElapsedTime().asMilliseconds() > 500) {
            showCursor = !showCursor;
            cursorClock.restart();
        }
    }
    else {
        showCursor = false;
    }
}

// установка значения из кода (например, при открытии редактора)
void InputField::setValue(float val) {
    value = val;
    std::stringstream ss;
    ss << val;
    input = ss.str();
    text.setString(input);
    updateCursorPosition();
}

// получение числового значения из строки ввода
float InputField::getValue() const {
    if (input.isEmpty()) return 0;
    try {
        return std::stof(input.toAnsiString());
    }
    catch (...) {
        return 0;  // невалидный ввод — возвращаем 0
    }
}

// проверка, что значение в допустимых границах рабочей области
bool InputField::isValidValue() const {
    float val = getValue();
    if (isX) {
        return val >= WORK_AREA_MIN_X && val <= WORK_AREA_MAX_X;
    }
    else {
        return val >= WORK_AREA_MIN_Y && val <= WORK_AREA_MAX_Y;
    }
}

// отрисовка поля: фон, лейбл, значение, курсор
void InputField::draw(sf::RenderWindow& window, const sf::Font& font) {
    window.draw(shape);

    sf::Text labelText(font, label, 14);
    labelText.setFillColor(sf::Color(180, 180, 180));
    labelText.setPosition({ shape.getPosition().x, shape.getPosition().y - 18 });
    window.draw(labelText);

    window.draw(text);

    // курсор рисуем только если поле активно и сейчас его "видимая" фаза
    if (showCursor && isSelected) {
        window.draw(cursor);
    }
}

// сброс поля к начальному значению "0"
void InputField::clear() {
    input = "0";
    text.setString("0");
    updateCursorPosition();
}