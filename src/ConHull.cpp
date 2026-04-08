// main.cpp
//fix
#include <SFML/Graphics.hpp> //Графика и окна
#include <iostream> 
#include <optional> //pollEvent()
#include "Point.h" //класс точки (координаты, вспомогательные функции)
#include "GameState.h" //состояние 
#include "Button.h"
#include "EditPointWindow.h"
#include "InputHandler.h"
#include "Renderer.h"

//загрузка шрифта
bool loadFont(sf::Font& font) {
    const std::vector<std::string> paths = {
        "resources/arial.ttf",
        "../resources/arial.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };
    for (const std::string& path : paths) {
        if (font.openFromFile(path)) {
            std::cout << "Font loaded from: " << path << std::endl;
            return true;
        }
    }
    std::cerr << "Failed to load font from any path!" << std::endl;
    return false;
}

int main() {
    //создание окна 1200х800 с заголовком
    sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), L"Convex Hull Visualization");
    window.setFramerateLimit(60);

    //загрузка шрифта
    sf::Font font;
    if (!loadFont(font)) {
        return -1;
    }
    //состояние (точки, оболочка, флаги режимов)
    GameState gameState;
    
    //кнопки интерфейса из конфигурации GameConfig (GameState.cpp)
    std::vector<Button> buttons;
    for (int i = 0; i < GameConfig::BUTTON_COUNT; i++) {
        buttons.emplace_back(font, GameConfig::BUTTON_TEXTS[i],
            GameConfig::BUTTON_POSITIONS[i], GameConfig::BUTTON_SIZES[i],
            GameConfig::BUTTON_ACTIONS[i]);
    }

    EditPointWindow editWindow(font); //окно редактор точки
    InputHandler inputHandler(buttons, gameState, editWindow, font); //обработчик ввода
    Renderer renderer(window, font, gameState, buttons); //отрисовка всего
  
    //главный цикл
    while (window.isOpen()) {
        std::optional<sf::Event> event;
        while (true) {
            std::optional<sf::Event> event = window.pollEvent(); //если событие есть true, иначе false
            if (!event.has_value()) break; //событий больше нет, выход

            if (event->is<sf::Event::Closed>()) {
                window.close(); //нажали крестик окна
            }
            //event->is<Т>() проверка является ли событие типом Т
            //event->getIf<T>() возвращает указатель на данные события, если тип совпадает, иначе nullptr
            
            else if (event->is<sf::Event::KeyPressed>()) { //проверка какая клавиша нажата
                const sf::Event::KeyPressed* keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent != nullptr && keyEvent->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close(); //esc выход
                }
            }
            //передача события в обработчики
            inputHandler.handleEvent(event.value()); //.value извлекает событие из optional
            if (editWindow.isShown()) {
                editWindow.handleEvent(event.value(), gameState.points, gameState.hull);
            }
        }

        editWindow.update(); //анимация курсора в полях ввода
        renderer.render(editWindow); //отрисовка: фон-точки-оболочка-интерфейс-окно редактирования
    }
    return 0;
}