// Point.cpp
#include "Point.h"
#include <algorithm>

// границы рабочей области для валидации координат
const float WORK_AREA_MIN_X = 50.0f;
const float WORK_AREA_MAX_X = 1150.0f;
const float WORK_AREA_MIN_Y = 150.0f;
const float WORK_AREA_MAX_Y = 750.0f;

// конструктор точки с координатами
Point::Point(float x, float y) : x(x), y(y) {}

// сравнение точек на равенство (для поиска, удаления)
bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

// обратное сравнение через оператор ==
bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

// ограничение координат точки границами рабочей области
// используется при редактировании, чтобы точка не ушла за пределы
void clampPoint(Point& point) {
    if (point.x < WORK_AREA_MIN_X) point.x = WORK_AREA_MIN_X;
    if (point.x > WORK_AREA_MAX_X) point.x = WORK_AREA_MAX_X;
    if (point.y < WORK_AREA_MIN_Y) point.y = WORK_AREA_MIN_Y;
    if (point.y > WORK_AREA_MAX_Y) point.y = WORK_AREA_MAX_Y;
}

// ориентация трёх точек: знак векторного произведения
// >0 - левый поворот (против часовой), <0 — правый, =0 — коллинеарны
// используется в алгоритме Грэхема для построения оболочки
float orientation(const Point& pivot, const Point& p, const Point& q) {
    return (p.y - pivot.y) * (q.x - p.x) - (p.x - pivot.x) * (q.y - p.y);
}

// квадрат расстояния между точками — без извлечения корня
// используется для сравнения расстояний и поиска ближайшей точки
float distSq(const Point& pivot, const Point& p) {
    float dx = p.x - pivot.x;
    float dy = p.y - pivot.y;
    return dx * dx + dy * dy;
}