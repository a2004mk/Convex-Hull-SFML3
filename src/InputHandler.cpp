// InputHandler.cpp
#include "InputHandler.h"
#include "ConvexHull.h"

// конструктор: сохранение ссылок на компоненты для обработки ввода
InputHandler::InputHandler(std::vector<Button>& btns, GameState& state,
    EditPointWindow& editWnd, sf::Font& fnt)
    : buttons(btns), gameState(state), editWindow(editWnd), font(fnt) {
}

// обработка нажатия клавиш (глобальные хоткеи)
void InputHandler::handleKeyPressed(const sf::Event::KeyPressed& keyPressed) {
    if (keyPressed.scancode == sf::Keyboard::Scancode::Escape) {
        // выход обрабатывается в main.cpp
    }
    else if (keyPressed.scancode == sf::Keyboard::Scancode::Space) {
        gameState.generateRandomPoints(20);  // быстрая генерация по пробелу
    }
}

// обновление позиции мыши и передача события кнопкам
void InputHandler::handleMouseMoved(const sf::Event::MouseMoved& mouseMoved) {
    gameState.mousePos = sf::Vector2f(static_cast<float>(mouseMoved.position.x),
        static_cast<float>(mouseMoved.position.y));

    for (Button& btn : buttons) {
        btn.handleEvent(mouseMoved);  // подсветка кнопок при наведении
    }
}

// обработка нажатия левой кнопки мыши
void InputHandler::handleMousePressed(const sf::Event::MouseButtonPressed& mousePressed) {
    if (mousePressed.button != sf::Mouse::Button::Left) return;

    // сначала проверяем клик по кнопкам интерфейса
    bool buttonPressed = false;
    for (Button& btn : buttons) {
        if (btn.handleEvent(mousePressed)) {
            buttonPressed = true;
            break;
        }
    }

    // если не кнопка — обрабатываем клик по рабочей области
    if (!buttonPressed) {
        sf::Vector2f clickPos(static_cast<float>(mousePressed.position.x),
            static_cast<float>(mousePressed.position.y));

        if (gameState.addMode) {
            gameState.tryAddPoint(clickPos);  // добавление новой точки
        }
        else if (gameState.editMode && !editWindow.isShown()) {
            // поиск точки для редактирования в радиусе 20 пикселей
            int index = gameState.findPointNear(clickPos, 20.0f);
            if (index >= 0) {
                gameState.selectedPointIndex = index;
                editWindow.show(gameState.points[index]);  // открытие редактора
            }
        }
    }
}

// выполнение действия по строковому ключу кнопки
void InputHandler::handleButtonAction(const std::string& action) {
    if (action == "random20") {
        gameState.generateRandomPoints(20);
    }
    else if (action == "random50") {
        gameState.generateRandomPoints(50);
    }
    else if (action == "clear") {
        gameState.clearAll();
    }
    else if (action == "toggle_add") {
        // переключение режима добавления точек
        gameState.addMode = !gameState.addMode;
        gameState.editMode = false;  // взаимное исключение режимов
        buttons[3].setText(gameState.addMode ? L"Добавление: ВКЛ" : L"Добавление: ВЫКЛ");
    }
    else if (action == "edit") {
        // переключение режима редактирования
        gameState.editMode = !gameState.editMode;
        gameState.addMode = false;
        gameState.selectedPointIndex = -1;  // сброс выбора при смене режима
    }
    else if (action == "remove_last") {
        gameState.removeLastPoint();
    }
    else if (action == "exit") {
        // выход обрабатывается в main.cpp через Escape
    }
}

// обработка отпускания кнопки мыши — завершение клика по кнопке
void InputHandler::handleMouseReleased(const sf::Event::MouseButtonReleased& mouseReleased) {
    if (mouseReleased.button != sf::Mouse::Button::Left) return;

    for (Button& btn : buttons) {
        if (btn.handleEvent(mouseReleased)) {
            handleButtonAction(btn.getAction());  // запуск действия по ключу
            break;
        }
    }
}

// главный диспетчер событий: маршрутизация по типу события
void InputHandler::handleEvent(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>();
        if (keyPressed) handleKeyPressed(*keyPressed);
    }
    else if (event.is<sf::Event::MouseMoved>()) {
        const sf::Event::MouseMoved* mouseMoved = event.getIf<sf::Event::MouseMoved>();
        if (mouseMoved) handleMouseMoved(*mouseMoved);
    }
    else if (event.is<sf::Event::MouseButtonPressed>()) {
        const sf::Event::MouseButtonPressed* mousePressed = event.getIf<sf::Event::MouseButtonPressed>();
        if (mousePressed) handleMousePressed(*mousePressed);
    }
    else if (event.is<sf::Event::MouseButtonReleased>()) {
        const sf::Event::MouseButtonReleased* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>();
        if (mouseReleased) handleMouseReleased(*mouseReleased);
    }
}