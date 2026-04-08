// ConvexHull.cpp
#include "ConvexHull.h"
#include <algorithm>

// Вспомогательная функция сравнения принимает pivot явно как параметр
// Возвращает true, если точка a должна идти раньше точки b при сортировке
static bool compareWithPivot(const Point& pivot, const Point& a, const Point& b) {
    float orient = orientation(pivot, a, b);
    if (orient == 0) {
        // Если точки на одной линии ближе к pivot идёт первой
        return distSq(pivot, a) < distSq(pivot, b);
    }
    return orient > 0; // Против часовой стрелки = раньше
}

std::vector<Point> convexHull(std::vector<Point> points) {
    size_t n = points.size();

    if (n <= 3) return points;

    //ищем самую нижнюю левую точку 
    size_t minYIndex = 0;
    for (size_t i = 1; i < n; i++) {
        if (points[i].y < points[minYIndex].y ||
            (points[i].y == points[minYIndex].y && points[i].x < points[minYIndex].x)) {
            minYIndex = i;
        }
    }

    //pivot - самая нижняя левая точка
    std::swap(points[0], points[minYIndex]);
    Point pivot = points[0];

    //сортировка остальных точек по углу относительно pivot

    for (size_t i = 1; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (compareWithPivot(pivot, points[j], points[i])) {
                std::swap(points[i], points[j]);
            }
        }
    }

    //точки, лежащие на одном луче от pivot, убираются (оставляем самую дальнюю)
    std::vector<Point> uniquePoints;
    uniquePoints.push_back(points[0]); // pivot всегда входит

    for (size_t i = 1; i < n; i++) {
        //пропуск точек, коллинеарных с текущей
        while (i < n - 1 && orientation(pivot, points[i], points[i + 1]) == 0) {
            i++;
        }
        uniquePoints.push_back(points[i]);
    }

    // Если после фильтра осталось мало точек — возвращаем их
    if (uniquePoints.size() < 3) return uniquePoints;

    // оболочка методом Грэхема (стек)
    std::vector<Point> hull;
    hull.push_back(uniquePoints[0]);
    hull.push_back(uniquePoints[1]);
    hull.push_back(uniquePoints[2]);

    for (size_t i = 3; i < uniquePoints.size(); i++) {
        // Удаляем точки, которые делают правый поворот
        while (hull.size() >= 2 &&
            orientation(hull[hull.size() - 2], hull.back(), uniquePoints[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(uniquePoints[i]);
    }

    return hull;
}
// Encoding fix check