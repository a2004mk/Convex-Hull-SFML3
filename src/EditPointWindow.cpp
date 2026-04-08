// EditPointWindow.cpp
#include "EditPointWindow.h"
#include "ConvexHull.h"

// конструктор: инициализаци€ окна редактора (пол€, кнопки, текст)
EditPointWindow::EditPointWindow(const sf::Font& font)
    : title(font, L"–едактор точки", 20)
    , inputX(font, "X (50-1150):", { 520, 350 }, { 150, 30 }, true)
    , inputY(font, "Y (150-750):", { 520, 410 }, { 150, 30 }, false)
    , saveButton(font, L"—охранить", { 480, 465 }, { 100, 30 }, "save")
    , cancelButton(font, L"ќтмена", { 600, 465 }, { 100, 30 }, "cancel")
    , errorText(font, L"", 14)
    , isVisible(false)
    , currentPoint(nullptr)
    , hasError(false) {

    // фон окна редактора
    background.setSize({ 260, 220 });
    background.setPosition({ 460, 290 });
    background.setFillColor(sf::Color(30, 30, 40));
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color(220, 230, 240));

    // заголовок окна
    title.setFillColor(sf::Color(220, 230, 240));
    title.setPosition({ 515, 300 });

    // текст ошибки (красный, внизу)
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition({ 500, 445 });
}

// показать окно дл€ редактировани€ точки
void EditPointWindow::show(Point& point) {
    currentPoint = &point;
    originalPoint = point;  // запомнить исходные значени€ дл€ отмены
    inputX.setValue(point.x);
    inputY.setValue(point.y);
    hasError = false;
    errorText.setString(L"");
    isVisible = true;
}

// скрыть окно редактора
void EditPointWindow::hide() {
    isVisible = false;
    currentPoint = nullptr;
}

// проверка видимости окна
bool EditPointWindow::isShown() const { return isVisible; }

// обработка событий мыши и клавиатуры
void EditPointWindow::handleEvent(const sf::Event& event, std::vector<Point>& points, std::vector<Point>& hull) {
    if (!isVisible) return;

    // передача событи€ пол€м ввода
    inputX.handleEvent(event);
    inputY.handleEvent(event);

    // отпускание кнопки мыши (клик по кнопкам)
    if (event.is<sf::Event::MouseButtonReleased>()) {
        const sf::Event::MouseButtonReleased* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>();
        if (mouseReleased) {
            // нажата "—охранить"
            if (saveButton.handleEvent(*mouseReleased)) {
                bool xValid = inputX.isValidValue();
                bool yValid = inputY.isValidValue();

                // координаты валидны Ч обновл€ем точку
                if (xValid && yValid) {
                    if (currentPoint) {
                        currentPoint->x = inputX.getValue();
                        currentPoint->y = inputY.getValue();
                        hull = convexHull(points);  // пересчЄт оболочки
                    }
                    hide();
                }
                // ошибка валидации Ч показываем сообщение
                else {
                    hasError = true;
                    if (!xValid && !yValid) {
                        errorText.setString(L"X и Y вне допустимых пределов!");
                    }
                    else if (!xValid) {
                        errorText.setString(L"X должен быть от 50 до 1150!");
                    }
                    else {
                        errorText.setString(L"Y должен быть от 150 до 750!");
                    }
                }
            }
            // нажата "ќтмена" Ч закрываем без изменений
            else if (cancelButton.handleEvent(*mouseReleased)) {
                hide();
            }
        }
    }
    // движение мыши Ч обновление состо€ни€ кнопок
    else if (event.is<sf::Event::MouseMoved>()) {
        const sf::Event::MouseMoved* mouseMoved = event.getIf<sf::Event::MouseMoved>();
        if (mouseMoved) {
            saveButton.handleEvent(*mouseMoved);
            cancelButton.handleEvent(*mouseMoved);
        }
    }
    // нажатие мыши Ч дл€ визуального эффекта кнопок
    else if (event.is<sf::Event::MouseButtonPressed>()) {
        const sf::Event::MouseButtonPressed* mousePressed = event.getIf<sf::Event::MouseButtonPressed>();
        if (mousePressed) {
            saveButton.handleEvent(*mousePressed);
            cancelButton.handleEvent(*mousePressed);
        }
    }
}

// обновление анимации курсора в пол€х ввода
void EditPointWindow::update() {
    if (!isVisible) return;
    inputX.update();
    inputY.update();
}

// отрисовка окна редактора (фон, текст, пол€, кнопки, ошибки)
void EditPointWindow::draw(sf::RenderWindow& window, const sf::Font& font) {
    if (!isVisible) return;

    window.draw(background);
    window.draw(title);
    inputX.draw(window, font);
    inputY.draw(window, font);
    saveButton.draw(window);
    cancelButton.draw(window);

    // показ текста ошибки если есть
    if (hasError) {
        window.draw(errorText);
    }
}