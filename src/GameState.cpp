// GameState.cpp
#include "GameState.h"
#include "ConvexHull.h"

// конфигурация интерфейса: позиции, размеры, тексты кнопок
const sf::Vector2f GameConfig::BUTTON_POSITIONS[7] = {
    {20, 50}, {170, 50}, {320, 50}, {450, 50}, {650, 50}, {780, 50}, {910, 50}
};
const sf::Vector2f GameConfig::BUTTON_SIZES[7] = {
    {140, 40}, {140, 40}, {120, 40}, {190, 40}, {120, 40}, {120, 40}, {120, 40}
};
const std::wstring GameConfig::BUTTON_TEXTS[7] = {
    L"Случайные 20", L"Случайные 50", L"Очистить",
    L"Добавление: ВЫКЛ", L"Удалить", L"Изменить", L"Выход"
};
// действия кнопок — строковые ключи для обработчика
const std::string GameConfig::BUTTON_ACTIONS[7] = {
    "random20", "random50", "clear", "toggle_add", "remove_last", "edit", "exit"
};
const int GameConfig::BUTTON_COUNT = 7;

// позиции текстовых элементов интерфейса
const sf::Vector2f GameConfig::WINDOW_SIZE = { 1200, 800 };
const sf::Vector2f GameConfig::INSTRUCTION_POS = { 20, 10 };
const sf::Vector2f GameConfig::COUNTER_POS = { 20, 110 };
const sf::Vector2f GameConfig::BOUNDS_POS = { 908, 780 };
const sf::Vector2f GameConfig::MODE_TEXT_POS = { 300, 110 };

// конструктор: инициализация состояния и генерация стартовых точек
GameState::GameState()
    : addMode(false)
    , editMode(false)
    , selectedPointIndex(-1)
    , gen(std::random_device()())
    , distX(WORK_AREA_MIN_X, WORK_AREA_MAX_X)
    , distY(WORK_AREA_MIN_Y, WORK_AREA_MAX_Y)
    , pointShape(5.0f)
    , hullPointShape(6.0f)
    , selectedPointShape(7.0f)
    , tempPointShape(5.0f)
    , hullLines() {

    // настройка визуала точек: обычная, в оболочке, выбранная, превью
    pointShape.setFillColor(sf::Color::White);
    pointShape.setOrigin({ 5.0f, 5.0f });

    hullPointShape.setFillColor(sf::Color::Green);
    hullPointShape.setOrigin({ 6.0f, 6.0f });

    selectedPointShape.setFillColor(sf::Color::Red);
    selectedPointShape.setOrigin({ 7.0f, 7.0f });

    tempPointShape.setFillColor(sf::Color::Yellow);
    tempPointShape.setOrigin({ 5.0f, 5.0f });

    // 20 точек для демонстрации
    generateRandomPoints(20);
}

// генерация случайных точек в рабочей области
void GameState::generateRandomPoints(int count) {
    points.clear();
    for (int i = 0; i < count; i++) {
        points.emplace_back(distX(gen), distY(gen));
    }
    updateHull();  // пересчёт оболочки после изменения точек
}

// пересчёт выпуклой оболочки при изменении набора точек
void GameState::updateHull() {
    hull = convexHull(points);
}

// удаление последней добавленной точки
void GameState::removeLastPoint() {
    if (!points.empty()) {
        points.pop_back();
        updateHull();
    }
}

// полная очистка точек и оболочки
void GameState::clearAll() {
    points.clear();
    hull.clear();
}

// добавление точки по клику, если клик в рабочей области
void GameState::tryAddPoint(const sf::Vector2f& clickPos) {
    if (clickPos.y > WORK_AREA_MIN_Y && clickPos.y < WORK_AREA_MAX_Y &&
        clickPos.x > WORK_AREA_MIN_X && clickPos.x < WORK_AREA_MAX_X) {
        points.emplace_back(clickPos.x, clickPos.y);
        updateHull();
    }
}

// поиск индекса точки рядом с позицией (для редактирования)
// используется квадрат расстояния, чтобы не считать корень
int GameState::findPointNear(const sf::Vector2f& pos, float threshold) const {
    for (size_t i = 0; i < points.size(); i++) {
        float dx = points[i].x - pos.x;
        float dy = points[i].y - pos.y;
        float distSq = dx * dx + dy * dy;
        if (distSq < threshold * threshold) {
            return static_cast<int>(i);
        }
    }
    return -1;  // точка не найдена в радиусе threshold
}